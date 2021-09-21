#include "parser.h"
#include "strings.h"
using namespace std;

void Parser::parse() {
    terminal nextTerm = nextToken();
    stack.emplace(stack.begin(), Symbol(0, NONTERM));
    printLM();
    
    while (!stack.empty()) {
        Symbol symbol = stack[0];
        
        if(symbol.getType()==static_cast<Type>(TERM) && symbol.getSymbol()==nextTerm) {
            stack.erase(stack.begin());
            accepted.push_back(Symbol(nextTerm, TERM));
            printLM();
            nextTerm = nextToken();
        }
        else if (symbol.getType()==static_cast<Type>(TERM) || table[symbol.getSymbol()][nextTerm]==-1) {
            cout << "syntax error" << endl;
            break;
        }
        else if(table[symbol.getSymbol()][nextTerm] != -1) {
            int ruleNum = table[symbol.getSymbol()][nextTerm];
            
            stack.erase(stack.begin());
            vector<Symbol>::iterator it;
            for (it = rules[ruleNum].begin(); it != rules[ruleNum].end(); it++) {
                if(it->getSymbol() != static_cast<terminal>(EPSILON))
                    stack.emplace(stack.begin(), *it);
            }
            printLM();
        }
    }
}

terminal Parser::nextToken () {
    string word;
    if(inputFile >> word) {
        if(word == "id") return static_cast<terminal>(ID);
        else if(word == "+") return static_cast<terminal>(PLUS);
        else if(word == "*") return static_cast<terminal>(ASTERISK);
        else if(word == "(") return static_cast<terminal>(LPAREN);
        else if(word == ")") return static_cast<terminal>(RPAREN);
        else if(word == "e") return static_cast<terminal>(EPSILON);
    }
    else
        return static_cast<terminal>(END);
}

void Parser::printLM() {
    vector<Symbol>::iterator it;
    for (it = accepted.begin(); it != accepted.end(); it++) {
        cout << terminalStrings[it->getSymbol()] << " ";
    }
    
    cout << "| ";
    
    for (it = stack.begin(); it != stack.end(); it++) {
        if(it->getType() == static_cast<Type>(TERM))
            cout << terminalStrings[it->getSymbol()] << " ";
        else
            cout << tokenStrings[it->getSymbol()] << " ";
    }
    cout << endl;
}