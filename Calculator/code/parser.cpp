#include "scanner.h"
#include "symtab.h"
// globals
Token_stream ts;
Symbol_table st; 
//map<string, int> names;

int statement()
{
	Token t = ts.get();        // get the next token from token stream
	switch (t.kind) {
    	case INT:
    		return declaration();
    	case IF:
    	    return ifExpr();
    	default:
    		ts.putback(t);     // put t back into the token stream
    		return orExpr();
	}
}

int declaration()
{
	Token t = ts.get();
	if (t.kind != ID) throw runtime_error("name expected in declaration");
	string name = t.name;
        st.declare(name, 0);
	return 0;
}

int ifExpr()
{
    // check condition starts with "("
    Token t = ts.get();
    if (t.kind != '(') throw runtime_error("'(' expected");
    ts.putback(t);
    
    // evaluate condition and true statement
    int cond = orExpr();
    int stmt1 = statement();
    
    // check for "else" in the if statement
    t = ts.get();
    if (t.kind != ELSE) throw runtime_error("'else' expected");
    
    // evaluate if statement
    int stmt2 = statement();
    if (cond == 1) 
        return stmt1;
    else
        return stmt2;
}

int orExpr()
{
    int left = andExpr();      // read and evaluate a orExpr
    int right = 0; 
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
            case '|':
                right = andExpr();
                if (left==0 && right==0)
                    left = 0;
                else
                    left = 1;
                t = ts.get();
                break;
            default:
                ts.putback(t);     // put t back into the token stream
                return left;       // finally: no more '|''  return the answer
        }
    }
}

int andExpr()
{
    int left = relExpr();      // read and evaluate a andExpr
    int right = 0; 
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
            case '&':
                right = relExpr();
                if (left==0 || right==0)
                    left = 0;
                else
                    left = 1;
                t = ts.get();
                break;
            default:
                ts.putback(t);     // put t back into the token stream
                return left;       // finally: no more '|''  return the answer
        }
    } 
}

int relExpr()
{
    int left = expression();      
    int right = 0; 
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
            case '>':
                right = expression();
                if (left > right)
                    left = 1;
                else
                    left = 0;
                t = ts.get();
                break;
            case '<':
                right = expression();
                if (left < right)
                    left = 1;
                else
                    left = 0;
                t = ts.get();
                break;
            default:
                ts.putback(t);     // put t back into the token stream
                return left;       // finally: no more '>','<' return the answer
        }
    } 
}

// + and -
int expression()
{
    int left = term();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
            case '+':
                left += term();    // evaluate Term and add
                t = ts.get();
                break;
            case '-':
                left -= term();    // evaluate Term and subtract
                t = ts.get();
                break;
            default:
                ts.putback(t);     // put t back into the token stream
                return left;       // finally: no more + or -: return the answer
        }
    }
}

// * and /
int term()
{
    int left = primary();
    Token t = ts.get();

    while (true) {
        switch (t.kind) {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
        {
            int d = primary();
            if (d == 0) throw runtime_error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
}

int primary()
{
    Token t = ts.get();
    int result;
    switch (t.kind) {
        case '(':    // handle '(' expression ')'
        {
            int d = orExpr();
            t = ts.get();
            if (t.kind != ')') throw runtime_error("')' expected");
            return d;
        }
        case '-':
        	return - primary();
        case '+':
        	return primary();
        case '!':
        {
            int d = primary();
            if (d == 0)
                return 1;
            else
                return 0;
        }
        case NUM:
            return t.value;  // return the number value
        case ID:
        {
        	string n = t.name;
        	Token next = ts.get();
        	if (next.kind == '=') {	// name = expression
                int d = relExpr();
        	    st.set(n, d);
                return d; // return the assignment value
        	}
        	else {
                ts.putback(next);		// not an assignment
                return st.get(t.name).value;  // return the id value
        	}
        }
        default:
            throw runtime_error("primary expected");
    }
}
