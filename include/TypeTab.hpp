#ifndef __TYPE_TAB_HPP__
#define __TYPE_TAB_HPP__

#include <map>
#include "Symbol.hpp"
#include "Tipo.hpp"
#include "iostream"
#include <sstream>
#include <string>
using namespace std;

class TypeTab{
private:
    map<int, Tipo> tableTT;
public:
    TypeTab();
    ~TypeTab();

    int agregar(Tipo tipo);
    int getTam(int id);
    string getNombre(int tipo);
    int getTipoBase(int tipo);
    int getTamanoTabla();
    void getTabla();



};


#endif // !__TYPE_TAB_HPP__