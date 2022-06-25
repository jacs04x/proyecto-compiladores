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

int Symbol::getTamArgs(){
    return args.size();
}

void Symbol::imprime(){
    string a;
    for (int i = 0; i < getTamArgs(); i++)
    {
        a = a + " " + to_string(this->args[i])+" ";

    }

    cout << to_string(getDir()) + " "+ to_string(getTipo()) + " " + getCat() +""+ a<<endl; 

}