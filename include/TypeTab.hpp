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

    int agregar(Type tipo);
    int getTam(int id);
    string getNombre(int tipo);
    int getTipoBase(int tipo);
    int getTam(int tipo);
    


};


#endif // !__TYPE_TAB_HPP__