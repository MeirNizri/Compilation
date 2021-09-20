/**
 * Class for token
 * 
 * Author: Meir Nizri
 * Second assignment in advanced programming course
 * Date: 2021-05
 */
 
#include "token.h"
#include "tokenstrings.h"
using namespace std;

tokenType Token::getType() {
    return type;
}

string Token::getText() {
    return text;
}

void Token::printToken() {
    if (type >= 258) cout << tokenStrings[type - 258] << '\t' << text << endl;
    else cout << static_cast<char>(type) << '\t' << text << endl;
}

void varToken::add_line(int l) {
    lines->insert(l);
}

shared_ptr<set<int>> varToken::getLines() {
    return lines;
}