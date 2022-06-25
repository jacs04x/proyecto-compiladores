#ifndef __SYM_TAB_HPP__
#define __SYM_TAB_HPP__

#include <map>
#include <stack>
#include <list>
#include "Symbol.hpp"

class SymTab{
private:
    map<string, Symbol> table;
    stack<list<Symbol>> pila;
public:
    SymTab();
    ~SymTab();
    int getDir(string id);
    int getTipo(string id);
    string getCat(string id);
    vector<int> getArgs(string id);
    void agregar(string id, int dir, int tipo, string cat);
    void agregar(string id, int dir, int tipo, string cat, vector<int> args);
    bool existe(string id);
    int getTamanoTabla();
    void getTabla();
};

#endif // !__SYM_TAB_HPP__