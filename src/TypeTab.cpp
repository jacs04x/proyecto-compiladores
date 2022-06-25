#include "TypeTab.hpp"
#include "Tipo.hpp"



TypeTab::TypeTab(){
     this->tableTT = map<int, Tipo>();
     this->tableTT[0] = Tipo("int",4, -1, 0 );
     this->tableTT[1] = Tipo("float", 4, -1,1);
}


int TypeTab::agregar(Tipo tipo){
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

