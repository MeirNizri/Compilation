#include "symbol.h"
#include "strings.h"
using namespace std;

Type Symbol::getType() {
    return type;
}

int Symbol::getSymbol() {
    return symbol;
}

void Symbol::printSymbol() {
    if (type == static_cast<Type>(TERM)) 
        cout << terminalStrings[symbol] << endl;
    else 
        cout << tokenStrings[symbol] << endl;
}