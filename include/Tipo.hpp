#ifndef __TIPO_HPP__
#define __TIPO_HPP__

#include <string>
#include "iostream"
using namespace std;

class Tipo{

private: 
    string nombre;
    int tamano;
    int numElementos;
    int tipoBase;

public:
    Tipo()=default;
    Tipo(string nombre, int tamano, int numElementos, int tipoBase);
    string getNombre();
    int getTamano();
    int getNumElementos();
    int getTipoBase();
    void imprime();
    
};



#endif // !__TIPO_HPP__