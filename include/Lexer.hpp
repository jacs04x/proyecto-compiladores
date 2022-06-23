#ifndef __LEXER_HPP__
#define __LEXER_HPP__

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include <string>
using namespace std;

class Lexer : public yyFlexLexer
{
public:
    Lexer(istream *in) : yyFlexLexer(in) {};
    using FlexLexer::yylex;
    virtual int yylex();
    virtual int getLine();
    virtual int getTipo();
private:
    int line=1;
    int numType;
};

#endif // !__LEXER_HPP__