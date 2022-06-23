%{
#include <iostream>
#include <string>
using namespace std;

#include "include/Tokens.hpp"
#include "headers/Lexer.hpp"

int line=1;
%}

%option c++
%option outfile="Lexer.cpp"
%option yyclass="Lexer"

%%
FIN ["$"]
ID [a-zA-Z_]([a-zA-Z_0-9_])*
MAS ["+"]
MUL ["*"]
IF "if"
ELSE "else"
WHILE "while"
DO "do"
COMA [,]
PYC [;]
INT "int"
FLOAT "float"
LCOR ["["]
RCOR ["]"]
LPAR ["("]
RPAR [")"]
ASIG [=]
NUM [0-9]


%%
{TOK_FIN} {return FIN;}
{TOK_ID} {return ID;}
{TOK_MAS} {return MAS;}
{TOK_MUL} {return MUL;}
{TOK_IF} {return IF;}
{TOK_ELSE} {return ELSE;}
{TOK_WHILE} { return WHILE;}
{TOK_DO} {return TOK_DO;}
{TOK_COMA}  { return COMA;}
{TOK_PYC}  { return PYC;}
{TOK_INT} { return INT;}
{TOK_FLOAT}   { return FLOAT;}
{TOK_LCOR} {return TOK_LCOR;}
{TOK_RCOR}  { return TOK_RCOR;}
{TOK_LPAR} {return LPAR;}
{TOK_RPAR}  {return RPAR;}
{TOK_ASIG} {return ASIG;}
{TOK_NUM} {return NUM;}


[ \t\r]+ {}
"\n" 	 {line++;}
.    	 { cout << "ERROR LEXICO " << yytext << endl;}

%%

int yyFlexLexer::yywrap(){
    return 1;
}

int Lexer::getLine()
{
    return line;
}
