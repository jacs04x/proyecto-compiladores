#ifndef __SYMBOL_HPP__
#define __SYMBOL_HPP__

#include <string>
#include <vector>

using namespace std;

class Symbol
{
private:
    int dir;
    int tipo;
    string cat;
    vector<int> args;

public:
    Symbol()=default;
    Symbol(int dir, int tipo, string cat);
    Symbol(int dir, int tipo, string cat, vector<int> args);

    string getCat();
    int getTipo();
    int getDir();
    vector<int> getArgs();
};

#endif // !__SYMBOL_HPP__