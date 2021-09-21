#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "enums.h"
using namespace std;

class Symbol {
    int symbol;
    Type type; // TERM or NONTERM
public:
    Symbol(int s, Type t) : symbol(s), type(t) {}
    Type getType();
    int getSymbol();
    void printSymbol();
};
