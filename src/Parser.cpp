#include "Parser.hpp"

Parser::Parser(Lexer *lexer, Driver *driver){
    this->lexer= lexer;
    this->driver = driver;
}

/**
 * Produccion P → D N
 * 
 */

void Parser::p()
{
    d();
    n();
}

/**
 * @brief D → T L ; D 
 *        Ltipo= T.tipo
 * 
 */

void Parser::d()
{
    if(token == TOK_INT || token == TOK_FLOAT)
    {
        int Ttipo = t();
        l(Ttipo);
        eat(TOK_PYC);
        d();
    }
}

/**
 * @brief T → B A
 * 
 * Abase = B.base
 * T.tipo = A.tipo
 * 
 * @return int 
 */

int Parser::t()
{
    int Bbase = b();
    int Ttipo = a(Bbase);
    return Ttipo;
}

/**
 * @brief B → int | float
 * B.base = 0 
 * B.base = 1
 * 
 * @return int 
 */

int Parser::b()
{
    if(token == TOK_INT)
    {
        eat(TOK_INT);
        return 0;
    }else if(token == TOK_FLOAT)
    {
        eat(TOK_FLOAT);
        return 1;
    }else
        error("Se esperaba int o float");
}

/**
 * @brief A  → [num] A1 
 * 
 * @param base 
 * @return int 
 */

int Parser::a(int base){
    int numTipo;
    string numVal;
    if(token == TOK_LCOR)
    {
        eat(TOK_LCOR);
        numTipo = lexer->getTipo();
        numVal =  lexer->YYText();
        eat(TOK_NUM);
        eat(TOK_RCOR);
        int A1tipo = a(base);
        if(numTipo !=0)
        {
            error("Se esperaba un tipo entero");
        }
        int Atipo = TT.agregar(stoi(numVal), A1tipo);
        return Atipo;
    }else{
        return base;
    }
}

/**
 * @brief  L → id L_I
 * 
 * @param tipo 
 */

void Parser::l(int tipo)
{
    string idVal = lexer->YYText();
    if(!TS.existe(idVal))
    {
        TS.agregar(idVal, dir, tipo, "var");
        dir += TT.getTam(tipo);
    }else{
        error("La variabe "+idVal+" ya fue declarada");
    }
    eat(TOK_ID);
    l_(tipo);
}

/**
 * @brief  L_I → , id L_I1 | ε
 * 
 * @param tipo 
 */

void Parser::l_(int tipo)
{
    if(token == TOK_COMA){
        eat(TOK_COMA);
        string idVal = lexer->YYText();
        if(!TS.existe(idVal))
        {
            TS.agregar(idVal, dir, tipo, "var");
            dir += TT.getTam(tipo);
        }else{
            error("La variabe "+idVal+" ya fue declarada");
        }
        eat(TOK_ID);
        l_(tipo);
    }
}


/**
 * @brief N → S N_I 
 * 
 */

void Parser::n(){
    s();
    n_();
}

/**
 * @brief N_I → , S N_I | ε
 * 
 */

void Parser::n_()
{
    if(token == TOK_ID || token == TOK_IF || token == TOK_WHILE || token == TOK_DO){
        s();
        n_();
    }
}

/**
 * @brief S →id S_I |S → if (E) S1 | S → if(E) S1 else S2 | S → if (E) S1_I
 *          |S → while(E) S1 | S → do S1 while(E);
 *          
 * 
 */

void Parser::s(){
    
    string idval = lexer->YYText();
    int s_dir = TS.getDir(idval);

    if(token == TOK_ID){    
        if(TS.existe(idval)){
            s_(TS.getTipo(idval),stoi(idval));            
            eat(token);
        }else{
            error("La variable "+ idval +"no ha sido declarada");
        }

    }else if(token == TOK_IF){
        string ltrue = driver->nuevaEtiqueta();
        string lfalse = driver->nuevaEtiqueta();
        Expresion E = e();
        driver->gen_if(E.dir, ltrue);
        driver->gen_goto(lfalse);
        driver->gen_label(ltrue)
        // S1.codigo
        driver->gen_label(lfalse);
        eat(token);

    }else if(token == TOK_WHILE){
        
        string linicio = driver->nuevaEtiqueta();
        string ltrue = driver->nuevaEtiqueta();
        string lfalse = driver->nuevaEtiqueta();
        eat(token);
        s1();
        eat(TOK_WHILE);
        eat(TOK_LPAR);
        Expresion E = e();
        eat(TOK_RPAR);

        driver->gen_label(linicio);
        driver->gen_if(E.dir, ltrue);
        driver->gen_goto(lfalse);
        driver->gen_label(ltrue);
        //S1.codigo
        driver->gen_goto(linicio);
        driver->gen_label(lfalse);
        


    }else if(token == TOK_DO){
        string ltrue = driver->nuevaEtiqueta();
        string lfalse = driver->nuevaEtiqueta();
        Expresion E = e();
        driver->gen_label(ltrue);
        //S1.codigo
        driver->gen_if(E.dir, ltrue);
        driver->gen_label(lfalse);
        eat(token);
    }

}

/**
 * @brief S_I → Y = E;
 * 
 * @param tipo 
 * @param dir 
 */

void Parser::s_(int tipo, int dir){
    y(tipo, dir);
    eat(TOK_ASIG);
    Expresion E = e();
    if (tipo == E.tipo){
        string op1 = driver->reducir(E.dir, E.tipo, tipo);
        string yID= lexer->YYText();
        string toGen += yID;
               toGen += "[";
               toGen += dir ;
               toGen += "]";
               toGen += "=";
               toGen += op1;

    }else{
        error("Incopatibilidad de tipos");
    }
    eat(TOK_PYC);
    


}

void Parser::y(int tipo, int dir){
    int Ytipo;
    int Ytam;
    int Ydir;
    if (token ==  TOK_ID){
        string idval= lexer->YYText();
        eat(token);
        eat(TOK_LCOR);
        Expresion E = e();
        if(TS.existe(idval)){
            int tipo = TS.getTipo(idval);
            if(TT.getNombre(tipo) == "array"){
                Ytipo = TT.getTipoBase(tipo);
                Ytam = TT.getTam(Ytipo);
                Ydir = driver->nuevaTemporal()
                if(E.tipo != 0){
                    error("El indice para un arreglo debe ser entero");
                }
                //genCod( Y.dir ‘=’ E.dir ‘*’ Y.tam)
                string id = idaval;
            }
        }
        eat(TOK_RCOR);
    }else if (token == TOK_LCOR){
        int y_tipo;
        int y_tam;
        int y_dir;
        eat(token);
        Expresion E = e();
        if( TT.getNombre(tipo) == "array"){
            y_tipo = TT.getTipoBase(tipo) ;
            y_tam = TT.getTam(Ytipo)
            y_dir = driver->nuevaTemporal();
            if(E.tipo != 0){
                error("El indice para un arreglo debe ser entero");
            }
            //genCod( Y_I.dirH ‘=’ E.dir ‘*’ Y_I.tamH)
            /*
                Y.dir = Y_I.dirS
                Y.tipo = Y_I.tipoS
                Y.tam = Y_I.tamS
            */            
            Ydir = y_dir;
            Ytipo = y_tipo;
            Ytam = y_tam;
            y_(Ydir, Ytipo, Ytam);
            eat(TOK_RCOR);
        }
    }
    
}

void Parser::y_(int dir, int tipo, int tam){
    int y_1tipoH ;
    int y_1tamH;
    int y_1dir;
    int y_dirS;
    int y_tamS;
    int y_tipoS;
    int t;
    if(token == TOK_LCOR){
        eat(TOK_LCOR);
        Expresion E = e();
        if(TT.getNombre(tipo) == "array"){
            y_1tipoH = TT.getTipoBase(tipo);
            y_1tamH = TT.getTam(tipo);
            t = driver->nuevaTemporal();
            y_1dir = driver ->nuevaTemporal();
            if (E.tipo != 0){
                error("El indice para un arreglo debe ser entero");
            }
            //genCod( t ‘=’ E.dir ‘*’ Y_I1.tamH)
            //genCod( Y_I1.dirH ‘=’ Y_I.dirH ‘+’ t )
            /*
            Y_I.dirS = Y_I1.dirS
            Y_I.tamS = Y_I1.tamS
            Y_I.tipoS = Y_I1.tipoS
            */
        }
    }
    /*
    Y_I.dirS = Y_I.dirH
    Y_I.tamS = Y_I.tamH
    Y_I.tipoS = Y_I.tipoH
    */

}


Expresion Parser::e(){
    Expresion E_h = g();
    Expresion E = e_(E_h);
    return E;
}


Expresion Parser::e_(Expresion h){
    string op1, op2;
    if(token == TOK_MAS){
        eat(TOK_MAS);
        Expresion G = g(); 
        Expresion E_1h;
    }
}

Expresion Parser::g(){
    Expresion G_h = f();
    Expresion G = g_(G_h); 
    return G;
}

Expresion Parser::f(){
    Expresion F;
    if(token == TOK_LPAR){
        eat(TOK_LPAR);
        F = e();
        return F;
    }else if (token == TOK_ID){
        eat(token);
    }else if(token == TOK_NUM){
        eat(token);
    }


}

Expresion Parser::g_(Expresion h){
    string op 1, op2 ;
    if(token == TOK_MUL){
        eat(token);
        Expresion F = f();
        Expresion G_1h;
    }
}

void Parser::eat(Token t){
    if(t == token){
        token = lexer->yylex();    
    }else{
          error("Se esperaba el token "+ lexer->TOKEN[token]);
    }

}

void Parser::error(string msg){
    cout << "ERROR: " << msg <<endl;
}   


void Parser::parse(){
    token = lexer->yylex();
    p();
    if (token == TOK_FIN){
        cout << "ACEPTADA" << endl;
    }else {
        cout << "RECHAZADA" << endl;
    }
}