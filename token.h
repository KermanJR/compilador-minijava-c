#include <iostream>
#include <ctype.h>//Funções de caracteres
#include <string>

using namespace std;

enum Names
{
    UNDEF,
    ID,
    NUMBER,
    PLUS, // +
    MINUS, // -
    MULT, // *
    DIV, // /
    ASSIGN, // =
    EQ, // ==
    NOT, // !
    NE, // !=
    LESS, // <
    LE, // <=
    GT, // >
    GE, // >=
    AND, //&&
    L_PAREN, // (
    R_PAREN, // )
    L_BRACKET, // [
    R_BRACKET,// ]
    L_BRACE, // {
    R_BRACE, // }
    SEMICOLON, // ;
    DOT, // .
    COMMA, // ,
    QUOTE, // ""
    BOOLEAN, // PR
    CLASS, // PR
    ELSE, // PR
    EXTENDS, // PR
    FALSE, // PR
    IF, // PR
    INT, // PR
    LENGTH, // PR
    MAIN, // PR
    NEW, // PR
    PUBLIC, // PR
    RETURN, // PR
    STATIC, // PR
    STRING, // PR
    SYSTEM_OUT_PRINTLN, // PR
    THIS, // PR
    TRUE, // PR
    VOID, // PR
    WHILE, // PR
    END_OF_FILE //Fim de arquivo
};

//PR são palavras reservadas

class Token
{
    public:
        int name;
        int attribute;
        string lexeme;

        Token(int name)
        {
            this->name = name;
            attribute = UNDEF;
        }

        Token(int name, int attr)
        {
            this->name = name;
            attribute = attr;
        }
};
