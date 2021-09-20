#include <algorithm>
#include <regex>
#include "symtab.h"

class Scanner {
	ifstream& inputFile;
	SymbolTable& symTab;
	int lineno = 1;
    char ch;
public:
	Scanner(ifstream& file, SymbolTable& tab) : inputFile(file), symTab(tab) {}
	shared_ptr<Token> nextToken();
	bool nextChar() {
	    inputFile.get(ch);
	    if (ch == '\n') 
	    	++lineno;
	    if (inputFile.eof()) 
	    	return false;
	    return true;
	}
};
