#ifndef __DRIVER_HPP__
#define __DRIVER_HPP__
#include "Quadrupla.hpp"
#include "SymTab.hpp"
#include "TypeTab.hpp"
#include <sstream>

class Driver{

    private:
        SymTab TS;
        TypeTab TT;
        vector<Quadrupla> code;
        int etiqueta=0;

    public:
        Driver()= default;
        ~Driver()= default;
        int reducir(int dir, int tipo1, int tipo2 );
        void gen_if(string dir, string etiqueta);
        void gen_goto(string etiqueta);        
        void gen_label(string label);
        Quadrupla nuevaEtiqueta();
        int nuevaTemporal();
        string generaCodigo(string codigo);
        


}


#endif // !__DRIVER_HPP__