#include "include/Driver.hpp"


int Driver::reducir(int dir, int tipo1, int tipo2){

}

string Driver::nuevaEtiqueta(){
    return "labelnueva";
}

int nuevaTemporal(){
    return 0;
}

void Driver::gen_label(string label){
    code.push_back(Quadrupla("label", "","",label));
}

void Driver::gen_if(int dir, string label){
    code.push_back(Quadrupla("if", dir, "goto", label));
}

void Driver::gen_goto(string label){
    code.push_back(Quadrupla("goto", "", "", label));
}






