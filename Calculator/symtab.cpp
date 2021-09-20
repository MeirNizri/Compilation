#include "symtab.h"
#include "scanner.h"

Attributes& Symbol_table::get(string name)
{
    auto it = sym_tab.find(name);
    if(it != sym_tab.end())
    {
        return it->second;
    } else {
	throw runtime_error("undefined variable");
    }
}

void Symbol_table::set(string name, int nv)
{
    Attributes& attr =  get(name);
    attr.value = nv;
    return;
}

bool Symbol_table::is_declared(string name)
{
    if(sym_tab.find(name) != sym_tab.end())
        return true;
    return false;
}

void Symbol_table::declare(string name, int nv)
{
    if (is_declared(name)) throw runtime_error("declared twice");
    sym_tab.insert(make_pair(name,Attributes(nv)));
//    sym_tab[name] = Attributes(nv, ic);
}

