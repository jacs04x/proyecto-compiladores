#ifndef __TYPE_HPP__
#define __TYPE_HPP__

#include <string>
using namespace std;

class Type{

private: 
    string nombre;
    int tamano;
    int numElementos;
    int tipoBase;

public:
    Type(int val, int tipo);
    Type(string nombre, int tamano, int numElementos, int tipoBase);
    string getNombre();
    int getTamano();
    int getNumElementos();
    int getTipoBase();

    
};



#endif // !__TYPE_HPP__