#ifndef __QUADRUPLA_HPP__
#define __QUADRUPLA_HPP__

#include <string>
using namespace std;

class Quadrupla
{

private:
    string op;
    string arg1;
    string arg2;
    string res;
    
public:        
    Quadrupla(string op, string arg1, string arg2, string res);
    string getOp();
    string getArg1();
    string getArg2();
    string getRes();
    
};



#endif // !__QUADRUPLA_HPP__