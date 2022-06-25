#include "SymTab.hpp"

SymTab::SymTab(){

}

SymTab::~SymTab(){

}

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


void SymTab::agregar(string id, int dir, int tipo, string cat){
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

int SymTab::getTamanoTabla(){
    return table.size();
}

void SymTab::getTabla(){

    cout << "Tabla de Simbolos" << endl; 
    vector<Symbol> simbolos;
    
    for(const auto &tabla : table){
        Symbol s = tabla.second;
        s.imprime();
    }
/*
    for(int j = 0; j < s; j++){
        simbolos[i].imprime() ;
    }
*/

}