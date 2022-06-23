#include "Symbol.hpp"


Symbol::Symbol(int dir, int tipo, string cat)
{
    this->dir = dir;
    this->tipo = tipo;
    this->cat = cat;
}

Symbol::Symbol(int dir, int tipo, string cat, vector<int> args)
{
    this->dir = dir;
    this->tipo = tipo;
    this->cat = cat;
    this->args = args;
}   

string Symbol::getCat()
{
    return cat;
}

int Symbol::getTipo()
{
    return tipo;
}

int Symbol::getDir()
{
    return dir;
}

vector<int> Symbol::getArgs()
{
    return args;
}