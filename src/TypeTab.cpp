#include "include/TypeTab.hpp"
#include "Type.hpp"

TypeTab::TypeTab(){
     tableTT[0] = Type("int",4, -1, 0 );
     tableTT[1] = Type("float", 4, -1,1);
}


int TypeTab::agregar(Type tipo){
     int id = tableTT.size()+1; 
     tableTT[id] = tipo;
     return id;
}

int TypeTab::getTam(int id){
     return tableTT[id].getTamano();
}

string TypeTab::getNombre(int tipo){
     return tableTT[tipo].getNombre();
}

int TypeTab::getTipoBase(int tipo){
     return tableTT[tipo].getTipoBase();
}

