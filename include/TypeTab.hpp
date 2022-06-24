#ifndef __TYPE_TAB_HPP__
#define __TYPE_TAB_HPP__

#include <map>
#include "Symbol.hpp"
#include "Type.hpp"

class TypeTab{
private:
    map<int, Type> tableTT;
public:
    TypeTab()=default;
    ~TypeTab() = default;
    int agregar(int numval, int numtipo);
    int getTam(int tipo);
    string getNombre(int tipo);
    int getTipoBase(int tipo);
    int getTam(int tipo);
    


};


#endif // !__TYPE_TAB_HPP__