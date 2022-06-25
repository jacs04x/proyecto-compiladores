#ifndef __TYPE_TAB_HPP__
#define __TYPE_TAB_HPP__

#include <map>
#include "Symbol.hpp"
#include "Tipo.hpp"

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
    


};


#endif // !__TYPE_TAB_HPP__