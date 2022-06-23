#ifndef __TYPE_HPP__
#define __TYPE_HPP__


class Type{

private: 
    string nombre;
    int tamano;
    int numElementos;
    int tipoBase;

public:
    Type()=default;
    Type(int val, int tipo);
    Type(string nombre, int tamano, int numElementos, int tipoBase);
    string getNombre();
    int getTamano();
    int getNumElementos();
    int getTipoBase();

    
};



#endif // !__TYPE_HPP__