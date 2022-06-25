#include "Parser.hpp"

Parser::Parser(Lexer *lexer){
    this->lexer=lexer;
}

Parser::~Parser()
{
    
}

/**
 * Produccion P → D N
 * 
 */

void Parser::p()
{
    cout << "p" << endl;
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
    cout << "d" << endl;
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
    cout << "t" << endl;
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
    cout << "b"+ to_string(token) << endl;
    int base;
    
    if(token == TOK_INT)
    {
        eat(TOK_INT);
        base = 0;
    }else if(token == TOK_FLOAT)
    {
        eat(TOK_FLOAT);
        base = 1;
    }else{
        error("Se esperaba int o float");
    }
    return base;
}

/**
 * @brief A  → [num] A1 
 * 
 * @param base 
 * @return int 
 */

int Parser::a(int base){
    cout << "a" << endl;
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
        Tipo t = Tipo("array", stoi(numVal) * TT.getTam(numTipo), stoi(numVal), A1tipo );
        int Atipo = TT.agregar(t);
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
    cout << "l" << endl;
    string idVal = lexer->YYText();
    if(!TS.existe(idVal))
    {
        TS.agregar(idVal, this->dir, tipo, "var");
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
    cout << "l_" << endl;
    if(token == TOK_COMA){
        eat(TOK_COMA);
        string idVal = lexer->YYText();
        if(!TS.existe(idVal))
        {
            TS.agregar(idVal, this->dir, tipo, "var");
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
    cout << "n" << endl;
    s();
    n_();
}

/**
 * @brief N_I → , S N_I | ε
 * 
 */

void Parser::n_()
{
    cout << "n_" << endl;
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
    cout << "s" << endl;
    string idval = lexer->YYText();
    if(token == TOK_ID){    
        if(TS.existe(idval)){
            s_(TS.getTipo(idval),TS.getDir(idval));            
            eat(token);
        }else{
            error("La variable "+ idval +"no ha sido declarada");
        }

    }else if(token == TOK_IF){
        eat(TOK_IF);
        eat(TOK_LPAR);
        string ltrue = nuevaEtiqueta();
        string lfalse = nuevaEtiqueta();
        Expresion E = e();
        eat(TOK_RPAR);

        gen_if(E.dir, ltrue);
        gen_goto(lfalse);
        gen_label(ltrue);
        s();
        gen_label(lfalse);
        eat(token);


    }else if(token == TOK_ELSE){
        string ltrue = nuevaEtiqueta();
        string lfalse = nuevaEtiqueta();
        string lfin = nuevaEtiqueta();
        gen_goto(lfin);
        gen_label(lfalse);
        s();
        gen_label(lfin);

    }else if(token == TOK_WHILE){
        
        eat(TOK_WHILE);
        eat(TOK_LPAR);
        Expresion E =e();
        string linicio = nuevaEtiqueta();
        string ltrue = nuevaEtiqueta();
        string lfalse = nuevaEtiqueta();
        gen_label(linicio);
        gen_if(E.dir, ltrue);
        gen_goto(lfalse);
        gen_label(ltrue);
        eat(TOK_RPAR);
        s();
        gen_goto(linicio);
        gen_label(lfalse);        


    }else if(token == TOK_DO){
        eat(TOK_DO);
        string ltrue = nuevaEtiqueta();
        string lfalse = nuevaEtiqueta();
        gen_label(ltrue);
        s();
        eat(TOK_WHILE);
        eat(TOK_RPAR);
        Expresion E = e();
        gen_if(E.dir, ltrue);
        gen_label(lfalse);
        eat(TOK_RPAR);
        eat(TOK_PYC);
    }

}

/**
 * @brief S_I → Y = E;
 * 
 * @param tipo 
 * @param dir 
 */

void Parser::s_(int tipo, int dir){
    map<string, int> mapS_ = y(tipo, dir);
    if(token == TOK_LCOR){
    eat(TOK_LCOR);
    eat(TOK_RCOR);

    eat(TOK_ASIG);
    Expresion E = e();
    
    if (mapS_["tipo"] == E.tipo){
        string op1 = reducir(E.dir, E.tipo, mapS_["tipo"]);
        string yID= lexer->YYText();
        genCode(Quadrupla(yID, "["+to_string(mapS_["dir"])+"]", "=", op1));
    }else{
        error("Incopatibilidad de tipos");
    }
    
    eat(TOK_PYC);
    } else if(token == TOK_ASIG){
        eat(TOK_ASIG);
        Expresion E = e();
        if(E.tipo == tipo){
            string dirn = reducir(E.dir, E.tipo, mapS_["tipo"]);
            genCode(Quadrupla("=",to_string(dir), " ", dirn));
        }
        eat(TOK_PYC);
    }
}


map<string, int> Parser::y(int tipo, int dir){
    dir++;
    map<string, int> mapY;
    if (token == TOK_ID){
        string idval= lexer->YYText();
        eat(TOK_ID);
        eat(TOK_LCOR);
        Expresion E = e();
        if(TS.existe(idval)){
            int tipo = TS.getTipo(idval);
            if(TT.getNombre(tipo) == "array"){
                this->temp++;
                mapY["Ytipo"] = TT.getTipoBase(tipo);
                mapY["Ytam"] = TT.getTam(tipo);
                mapY["Ydir"] = this->temp;
                if(E.tipo != 0){
                    error("El indice para un arreglo debe ser entero");
                }
                genCode(Quadrupla("=", to_string(mapY["Ydir"]), " ", E.dir+ " * " +to_string(mapY["Ytam"])));
                mapY["Yid"] = stoi(idval);
            }
        }
        eat(TOK_RCOR);
    }else if (token == TOK_LCOR){
        eat(TOK_LCOR);
        if( TT.getNombre(tipo) == "array"){
            Expresion E = e();
            eat(TOK_RCOR);
            this->temp++;
            map<string, int> mapY_ = y_(this->temp, TT.getTipoBase(tipo), TT.getTam(tipo));
            mapY_["y_tipoH"] = TT.getTipoBase(tipo);
            mapY_["y_tamH"] = TT.getTam(tipo);
            mapY_["y_dirH"] = this->temp;
            if(E.tipo != 0){
                error("El indice para un arreglo debe ser entero");
            }
            //genCod( Y_I.dirH ‘=’ E.dir ‘*’ Y_I.tamH)
            genCode(Quadrupla("=", "T "+ to_string(mapY_["y_dirH"]),"",  to_string(mapY_["y_tamH"])));

            /*
                Y.dir = Y_I.dirS
                Y.tipo = Y_I.tipoS
                Y.tam = Y_I.tamS
            */            
            mapY["Ydir"] = mapY_["y_dirH"];
            mapY["Ytam"] = mapY_["y_tamH"];
            mapY["Ytipo"] = mapY_["y_tipoH"];
        }
    }
    return mapY;
}

map<string, int> Parser::y_(int dir, int tipo, int tam){
    map<string, int> mapY_ ;
    if(token == TOK_LCOR){
        eat(TOK_LCOR);
        Expresion E = e();
        eat(TOK_RCOR);

        if(TT.getNombre(tipo) == "array"){
            map<string, int> mapY_1 = y_(this->temp, TT.getTipoBase(tipo), TT.getTam(tipo));
            this->temp++;
            mapY_1["y1_tipoH"] = TT.getTipoBase(tipo);
            mapY_1["y1_tamH"] = TT.getTam(tipo);
            string t = nuevaTemporal();
            mapY_1["y1_dirH"] = this->temp++;
            if (E.tipo != 0){
                error("El indice para un arreglo debe ser entero");
            }
            genCode(Quadrupla("=", t, " ", E.dir + "*" + to_string(mapY_["y1_tamH"])));
            genCode(Quadrupla("=", to_string(this->temp), " ", "T" + to_string(mapY_["t1_dirH"]) + "+" + t));
            /*
            Y_I.dirS = Y_I1.dirS
            Y_I.tamS = Y_I1.tamS
            Y_I.tipoS = Y_I1.tipoS
            */
           mapY_["Y_dirS"] = mapY_1["y1_dirH"];
           mapY_["Y_tamS"] = mapY_1["y1_tamH"];
           mapY_["Y_tipoS"] = mapY_1["y1_tipoH"];


        }
    }else{
    /*
    Y_I.dirS = Y_I.dirH
    Y_I.tamS = Y_I.tamH
    Y_I.tipoS = Y_I.tipoH
    */
    mapY_["Y_dirS"] = dir;
    mapY_["Y_tamS"] = tam;
    mapY_["Y_tipoS"] = tipo;
        
    }
    return mapY_;
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
        if(E_1h.tipo == G.tipo){
            string E_1dirH = nuevaTemporal();
            int E_1tipoH = maximo(E_1h.tipo, G.tipo);
            string op1 = ampliar(E_1h.dir, E_1h.tipo, E_1tipoH);
            string op2 = ampliar(G.dir, G.tipo, h.tipo );
            genCode(Quadrupla("=", E_1dirH, " ", op1 + " + "+op2 ));
        }
    }else {
        /*
        E_I.dirS = E_I.dirH
        E_I.tipoS = E_I.tipoH
         */ 
    }
    return h;
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
        eat(TOK_RPAR);
        
    }else if (token == TOK_ID){
        eat(TOK_ID);
        string id = lexer->YYText();
        if(TS.existe(id)){
            F.dir = id;
            F.tipo= TS.getTipo(id);
        }
        if(token == TOK_LCOR){
            if(TS.existe(id)){
                map<string, int> mapY = y(TS.getTipo(id),stoi(id));
                F.dir = nuevaTemporal();
                F.tipo = mapY["tipo"];  
                genCode(Quadrupla("=", F.dir, " ", to_string(mapY["Yid"]) + "[" + to_string(mapY["Ydir"])+"]" ));
            }else{
                error("La variable no fue declarada");

            }
        }
    }else if(token == TOK_NUM){
        eat(TOK_NUM);
        F.tipo = lexer->getTipo();
        F.dir =  lexer->YYText();
    }else{
             error("La variable no fue declarada");
    }
    return F;
}

Expresion Parser::g_(Expresion h){
    string op1, op2 ;
    if(token == TOK_MUL){
        eat(TOK_MUL);
        Expresion F = f();
        Expresion G_1h;
    if(G_1h.tipo == F.tipo){
            string G_1dirH = nuevaTemporal();
            int G_1tipoH = maximo(G_1h.tipo, F.tipo);
            op1 = ampliar(G_1h.dir, G_1h.tipo, G_1tipoH);
            op2 = ampliar(F.dir, F.tipo, h.tipo );
            genCode(Quadrupla("=", G_1dirH, " ", op1 + " * "+op2 ));
        }
    }else {
        /*
        G_I.dirS = G_I.dirH
        G_I.tipoS = G_I.tipoH
        */
    }
    return h;
}


void Parser::eat(TOKEN t){
    if(t == token){
        token = (TOKEN)lexer->yylex();    
    }else{
          error("Se esperaba el token "+ to_string(t));
    }

}

void Parser::error(string msg){
    cout << "ERROR: " << msg <<endl;
    exit(EXIT_FAILURE);

}   


void Parser::parse(){
    token = (TOKEN)lexer->yylex();
    cout << "primer token: "+ to_string((TOKEN)token) <<endl;
    p();
    codigointermedio();
    if (token == TOK_FIN){
        cout << "ACEPTADA" << endl;
    }else {
        cout << "RECHAZADA" << endl;
    }
}

string Parser::nuevaEtiqueta(){
    stringstream label;
    label<< "L"<<etiqueta++;
    return label.str();
}

string Parser::nuevaTemporal(){
    stringstream label;
    label<< "T"<<temp++;
    return label.str();
}

void Parser::gen_label(string label){
    code.push_back(Quadrupla("label", "","",label));
}

void Parser::gen_if(string dir, string label){
    code.push_back(Quadrupla("if", dir, "goto", label));
}

void Parser::gen_goto(string label){
    code.push_back(Quadrupla("goto", "", "", label));
}

void Parser::gen_fin(string label){
    code.push_back(Quadrupla("fin", "", "", label));
}

void Parser::genCode(Quadrupla q){
    code.push_back(q);
}

string Parser::reducir(string dir, int t1, int t2){
    string temp;
    if(t1==t2) return dir;
    else if(t1==1 && t2==0){
        string idval = lexer->YYText();
        temp = nuevaTemporal();
        genCode(Quadrupla("int",dir, " ",to_string(this->temp)));
        TS.agregar(idval, this->temp, 0, "temporal");        
        return temp;
    }else {
        return "";
    }

}

int Parser::maximo(int t1, int t2){

    if(t1==t2) return t1;
    else if(t1==0 && t2==1) return 1;
    else if(t1==1 && t2==0) return 1;
    else return -1;
}

string Parser::ampliar(string dir, int t1, int t2)
{
    string temp;
    if(t1==t2) return dir;
    else if(t1==0 && t2==1){
        string idval = lexer->YYText();
        temp = nuevaTemporal();
        code.push_back(Quadrupla("(float)",dir, "", temp));
        TS.agregar(idval,this->temp, 1, "temporal" );
        return temp;
    }else return "";
}

string Parser::imprime(Quadrupla q){
    return q.getOp() + " " + q.getArg1() + " " + q.getArg2() + " " + q.getRes();
}

void Parser::codigointermedio(){
    cout << "\n" << endl;
    cout << "=======================" << endl;
    TT.getTabla();
        cout << "\n" << endl;
    cout << "=======================" << endl;
    TS.getTabla();
    int s = this->code.size();
    cout << "\n" << endl;
    cout << "=======================" << endl;
    for(int i =0 ; i<s; i++){
        cout<< imprime(this->code[i]) <<endl;
    }
    
}

    



