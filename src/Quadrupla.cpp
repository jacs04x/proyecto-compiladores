#include "include/Quadrupla.hpp"

Quadrupla::Quadrupla(string op, string arg1, string arg2, string res){
    this-> op = op;
    this-> arg1 = arg1;
    this-> arg2 = arg2;
    this-> res = res;
}

string getOp(){
    return op;
}

string getArg1(){
    return arg1;
}

string getArg2(){
    return arg2;
}

string getRes(){
    return res;
}