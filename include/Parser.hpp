#ifndef __PARSER_HPP__
#define __PARSER_HPP__
#include "Atributos.hpp"
#include "Tokens.hpp"
#include "Lexer.hpp"
#include "SymTab.hpp"
#include "TypeTab.hpp"
#include "Quadrupla.hpp"
#include "Driver.hpp"


class Parser
{
private:
    Lexer *lexer;
    TOKEN token;
    SymTab TS;
    TypeTab TT;
    int dir= 0;
    vector<Quadrupla> code;
    int etiqueta=0;
    int temp= 0;
    int index=0;
    
private:
    void eat(TOKEN tok);
    void error(string msg);
    void p();
    void d();
    void n();
    int t();
    int b();
    int a(int base);
    void l(int tipo);
    void l_(int tipo);
    void n();
    void n_();
    void s();
    void s_(int tipo);
    void y();
    void s1();
    void y_(int dir, int tipo, int tam);
    Expresion e();
    Expresion e_(Expresion h);    
    Expresion g();

    int reducir(int dir, int t1, int t2);
        void gen_if(string dir, string etiqueta);
        void gen_goto(string etiqueta);        
        void gen_label(string label);
        void gen_fin(string label);
    string nuevaTemporal();
    string nuevaEtiqueta();
    int maximo(int t1, int t2);


public:
    ~Parser() = default;
    Parser(Lexer *lexer);
    
};

#endif // !__PARSER_HPP__