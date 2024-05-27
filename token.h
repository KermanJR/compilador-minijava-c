#include <iostream>
#include <string>

using namespace std;

// Enumeração para os nomes dos tokens
enum Names {
    UNDEF,
    ID,
    PLUS,
    ASSIGN,
    MINUS,
    MULT,
    DIV,
    EQ,
    NOT,
    NE,
    LESS,
    LE,
    GT,
    GE,
    AND,
    L_PAREN,
    R_PAREN,
    L_BRACKET,
    R_BRACKET,
    L_BRACE,
    R_BRACE,
    SEMICOLON,
    DOT,
    COMMA,
    QUOTE,
    INTEGER_LITERAL,
    IF,
    ELSE,
    WHILE,
    CLASS,
    MAIN,
    VOID,
    STATIC,
    EXTENDS,
    FALSE,
    TRUE,
    INT,
    BOOLEAN,
    RETURN,
    NEW,
    STRING,
    THIS,
    PUBLIC,
    LENGTH,
    SYSTEM_OUT_PRINT_LN,
    END_OF_FILE
};

// Classe Token
class Token {
public:
    int name;
    int attribute;
    string lexeme;
    void* entry; // Ponteiro para a entrada na tabela de símbolos associada ao token

    // Construtores
    Token(int name) {
        this->name = name;
        attribute = UNDEF;
        entry = nullptr;
    }

    Token(int name, int attr) {
        this->name = name;
        attribute = attr;
        entry = nullptr;
    }

    Token(int name, int attr, string lexeme) {
        this->name = name;
        attribute = attr;
        this->lexeme = lexeme;
        entry = nullptr;
    }
};
