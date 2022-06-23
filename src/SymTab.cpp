#include "SymTab.hpp"


int SymTab::getDir(string id)
{
    return table[id].getDir();
}

int SymTab::getTipo(string id)
{
    return table[id].getTipo();
}

string SymTab::getCat(string id)
{
    return table[id].getCat();
}

vector<int> SymTab::getArgs(string id)
{
    return table[id].getArgs();
}

void SymTab::agregar(string id, int dir, int tipo, string cat)
{    
    table[id] = Symbol(dir, tipo, cat);
}

void SymTab::agregar(string id, int dir, int tipo, string cat, vector<int> args)
{
    table[id] = Symbol(dir, tipo, cat, args);
}

bool SymTab::existe(string id)
{
    map<string,Symbol>::iterator it = table.find(id);
    return it != table.end();
}