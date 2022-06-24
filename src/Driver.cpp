#include "include/Driver.hpp"

string Driver::nuevaEtiqueta(){
    stringstream label;
    label<< "L"<<etiqueta++;
    return label.str();
}

string nuevaTemporal(){
    stringstream label;
    label<< "T"<<etiqueta++;
    return label.str();
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

void Parser::gen_fin(string label){
    code.push_back(Quadrupla("fin", "", "", label));
}

int Driver::reducir(int dir, int t1, int t2){
    
    string temp;
    if(t1==t2) return dir;
    else if(t1==1 && t2==0){
        temp = nuevaTemporal();
        code.push_back(Quadrupla("(int)",dir, "", temp));
        TS.agregar(Symbol(temp, 0, "temporal"));        
        return temp;
    }else return "";

}

int Driver::maximo(int t1, int t2)
{
    if(t1==t2) return t1;
    else if(t1==0 && t2==1) return 1;
    else if(t1==1 && t2==0) return 1;
    else return -1;
}





