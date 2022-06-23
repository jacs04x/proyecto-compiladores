#include "include/Type.hpp";

Type::Type(int tipoBase){
    this-> nombre = "";
    this-> tamano = -1;
    this-> numElementos = -1;
    this->tipoBase = tipoBase ;
}

Type::Type(string nombre, int tipoBase){
    this-> nombre = nombre ;
    this-> tipoBase = tipoBase ;
}

Type::Type(string nombre, int tamano, int numElementos, int tipoBase){
    this->nombre = nombre ;
    this->tamano = tamano;
    this->numElementos = numElementos ;
    this->tipoBase = tipoBase ;

};


string Type::getNombre(){
    return nombre;
}

int Type::getTamano(){
    return tamano;
}

int Type::getNumElementos(){
    return numElementos;
}

int Type::getTipoBase(){
    return tipoBase;
}


