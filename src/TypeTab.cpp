#include "include/TypeTab.hpp"
#include "Type.hpp"




int TypeTab::agregar(int numval, int numTipo){

     tableTT[numval] = Type(numTipo);
     return tableTT[numval].getTipoBase();


}

int TypeTab::getTam(int id){
     return tableTT[id].getTamano();
}

string TypeTab::getNombre(int tipo){
     map<string, Type> :: iterator it = tableTT.find(tipo);
     if (it != tableTT.end()){
          return it.nombre;
     }
}

int getTipoBase(int tipo){

     map<string, Type> :: iterator it = tableTT.find(tipo);
     if(it != tableTT.end()){
          return tipo.tipo;
     }

}

