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
"$"       {return TOK_FIN;}
[a-zA-Z_]([a-zA-Z_0-9_])* {return TOK_ID;}
"+"       { return TOK_MAS;}
"*"       { return TOK_MUL;}
"if"    { return(TOK_IF); }
"else"  { return(TOK_ELSE);}
"while" { return TOK_WHILE;}
"do"    { return TOK_DO;}
","     { return TOK_COMA;}
";"       { return(TOK_PYC); }  
"int"   { return TOK_INT;}
"float" { return TOK_FLOAT;}
"["     {return TOK_LCOR;}
"]"     {return TOK_RCOR;}
\(      { return TOK_LPAR;}
\)      { return TOK_RPAR;}
[0-9]+  { return TOK_NUM;}
"="       { return(TOK_ASIG); }
"\n" 	{line++;}
.    	{ cout << "ERROR LEXICO " << yytext << endl;}
%%
int yyFlexLexer::yywrap(){
    return 1;
}
int Lexer::getLine()
{
    return line;
}