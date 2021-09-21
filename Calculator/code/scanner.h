#include<iostream>
#include<string>
#include<map>
#include<algorithm>
#include <regex>
#include<stdexcept>
using namespace std;

enum Tokens {
    NUM = 20,
    ID = 21,
    INT = 22,
    IF = 24,
    ELSE = 25,
    EOL = 23,
};

class Token{
public:
    char kind;        	    // what kind of token
    int value;     	    // for numbers a value 
    string name;     	    // for variables a name 
    Token(char ch) :kind(ch), value(0) { }
    Token(char ch, int val) :kind(ch), value(val) { }
    Token(char ch, string n) :kind{ch}, name{n} { }
};

class Token_stream {
public:
    Token_stream() :full(false), buffer(0) {}
    Token get();            // get a Token
    void putback(Token t);  // put a Token back
private:
    bool full;              // is there a Token in the buffer?
    Token buffer;           // keep a Token when using putback()
};

// declarations so that functions can call each other
int statement();
int declaration();
int ifExpr();
int orExpr();
int andExpr();
int relExpr();
int expression();
int term();
int primary();
