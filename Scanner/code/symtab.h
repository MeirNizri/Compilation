#include <map>
#include "token.h"

class SymbolTable {
	map<string, shared_ptr<Token>> symMap;
	void initReserved();
public:
	SymbolTable () { initReserved(); }
	shared_ptr<Token> lookupToken(string text);
	void insertToken(string text, shared_ptr<Token> tokenp);
	void xref();
};

