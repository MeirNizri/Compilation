/**
 * Class for symtab
 * 
 * Author: Meir Nizri
 * Second assignment in advanced programming course
 * Date: 2021-05
 */
 
#include "symtab.h"
using namespace std;


void SymbolTable::initReserved() {
    ifstream file("reserved.txt");
    string newLine;
    int delPos;
    string text;
    tokenType type;
    
    while (getline(file, newLine)) {
        if (!newLine.empty()) {
            delPos = newLine.find('\t');
            text = newLine.substr(0,delPos);
            tokenType type = static_cast<tokenType>(stoi(newLine.substr(delPos+1,-1)));
            Token token(type, text);
            symMap.insert( {text, make_shared<Token>(token)} );
        }
    }
    file.close();
}

shared_ptr<Token> SymbolTable::lookupToken(string text) {
    if (symMap.find(text) != symMap.end()) 
        return symMap[text];
    else 
        return nullptr;
}

void SymbolTable::insertToken(string text, shared_ptr<Token> tokenp) {
    symMap[text] = tokenp;
}

void SymbolTable::xref() {
    map<string, shared_ptr<Token>>::iterator it;
    for (it = symMap.begin(); it != symMap.end(); it++) {
        string text = it->first;
        shared_ptr<Token> token = it->second;
        
        if (token->getType() == static_cast<tokenType>(IDENTIFIER))  {
            cout << text << '\t';
            shared_ptr<set<int>> lines = token->getLines();
            set<int>::iterator it2;
            for (it2 = lines->begin(); it2 != lines->end(); it2++) {
                cout << *it2 <<" ";
            }
        cout << endl;
        }
    }
}