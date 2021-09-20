#include "scanner.h"
#include <ctype.h>
#include <regex>
using namespace std;

shared_ptr<Token> Scanner::nextToken() {
    while (nextChar()) {
        
        // check for comment
        if(ch == '/') {
            if(nextChar() && ch=='/') {
                while(nextChar() && ch!='\n') {} 
                nextChar();
            }
            else if(ch=='*') {
                char prev = 0;
                while(nextChar()) {
                    if (prev=='*' && ch=='/') break;
                    prev = ch;
                }
                nextChar();
            }
            else {
                inputFile.unget();
                ch = '/';
            }
        }
        
        // check for single letter operator
        switch (ch) { 
            case ' ': case '\t': case '\n': case '\r': 
                break;
            case ';' : case '{' : case '}' : case ',' : case ':' : \
            case '(' : case ')' : case '[' : case ']' : case '~' : \
            case '*' : case '%' : case '^' : case '?' : case '/': 
                return shared_ptr<Token> (new Token(static_cast<tokenType>(ch),string(1,ch)));
        }
        
        // check for number
        if(isdigit(ch) || ch=='.') {
            string num = "";
            do { 
                num += ch;
            } while (nextChar() && (isdigit(ch) || ch=='.' || ch=='e' || ch=='E'));
            inputFile.unget();
            
            regex n1 (R"([1-9]\d*)");
            regex n2 (R"(\d+[Ee][\+\-]?\d+)");
            regex n3 (R"(\d*\.\d+([Ee][\+\-]?\d+)?)");
            regex n4 (R"(\d+\.\d*([Ee][\+\-]?\d+)?)");

            if (regex_match (num, n1)
                || regex_match (num, n2)
                || regex_match (num, n3)
                || regex_match (num, n4)
                || num == "0")
                return shared_ptr<Token> (new Token(static_cast<tokenType>(CONSTANT), num));
            else if (num == ".")
                return shared_ptr<Token> (new Token(static_cast<tokenType>('.'), "."));
            else
                return shared_ptr<Token> (new Token(static_cast<tokenType>(ERROR), num));
        }
        
        // check for identifier or key word
        if(isalpha(ch)) {
            string word = "";
            do {
                word += ch;
            } while (nextChar() && (isalpha(ch) || isdigit(ch) || ch=='_'));
            inputFile.unget();
            
            shared_ptr<Token> token = symTab.lookupToken(word);
            if (token != nullptr) {
                if (token->getType() == static_cast<tokenType>(IDENTIFIER)) {
                    token->add_line(lineno);
                }
                return token;
            }
            else {
                varToken vt (word);
                vt.add_line(lineno);
                token = make_shared<varToken>(vt);
                symTab.insertToken(word, token);
                return token;
            }
        }
        
        // check for char
        if(ch == '\'') {
            char c = ch;
            if(nextChar()) {
                c = ch;
                if (nextChar() && ch=='\'')
                    return shared_ptr<Token> (new Token(static_cast<tokenType>(CONSTANT), string(1,c)));
            }
            return shared_ptr<Token> (new Token(static_cast<tokenType>(ERROR), string(1,c)));   
        }
        
        // check for string
        if(ch == '\"') {
            string str = "";
            while (nextChar() && ch!='\"') {
                str += ch;
            }
            return shared_ptr<Token> (new Token(static_cast<tokenType>(STRING_LITERAL), str));
        }
        
        //check for operators
        else if (ch=='+' || ch=='-' || ch=='&' || ch=='|' 
              || ch=='<' || ch=='>' || ch=='=' || ch=='!') {
            int state = 0;
            char op = ch;
            switch (state) {
                case 0:
                    if (ch=='+') state = 1;
                    else if (ch=='-') state = 2;
                    else if (ch=='&') state = 3;
                    else if (ch=='|') state = 4;
                    else if (ch=='<') state = 5;
                    else if (ch=='>') state = 6;
                    else if (ch=='=') state = 7;
                    else if (ch=='!') state = 8;
                    if(!nextChar())
                        return shared_ptr<Token> (new Token(static_cast<tokenType>(ch),string(1,ch)));
                case 1:
                    if(ch=='+') 
                        return shared_ptr<Token> (new Token(static_cast<tokenType>(INC_OP), "++"));
                case 2:
                    if(ch=='-') 
                        return shared_ptr<Token> (new Token(static_cast<tokenType>(DEC_OP), "--"));
                    else if(ch=='>') 
                        return shared_ptr<Token> (new Token(static_cast<tokenType>(PTR_OP), "->"));
                case 3:
                    if(ch=='&') 
                        return shared_ptr<Token> (new Token(static_cast<tokenType>(AND_OP), "&&"));
                case 4:
                    if(ch=='|') 
                        return shared_ptr<Token> (new Token(static_cast<tokenType>(OR_OP), "||"));
                case 5:
                    if(ch=='=') 
                        return shared_ptr<Token> (new Token(static_cast<tokenType>(LE_OP), "<="));
                case 6:
                    if(ch=='=') 
                        return shared_ptr<Token> (new Token(static_cast<tokenType>(GE_OP), ">="));
                case 7:
                    if(ch=='=') 
                        return shared_ptr<Token> (new Token(static_cast<tokenType>(EQ_OP), "=="));
                case 8:
                    if(ch=='=') 
                        return shared_ptr<Token> (new Token(static_cast<tokenType>(NE_OP), "!="));    
            }
            inputFile.unget();
            return shared_ptr<Token> (new Token(static_cast<tokenType>(op), string(1,op)));
        }
    }
}