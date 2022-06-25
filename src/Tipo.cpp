#include "Tipo.hpp"


Tipo::Tipo(string nombre, int tamano, int numElementos, int tipoBase){
    this->nombre = nombre ;
    this->tamano = tamano;
    this->numElementos = numElementos ;
    this->tipoBase = tipoBase ;

};


string Tipo::getNombre(){
    return nombre;
}

int Tipo::getTamano(){
    return tamano;
}

int Tipo::getNumElementos(){
    return numElementos;
}

int Tipo::getTipoBase(){
    return tipoBase;
}


