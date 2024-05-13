#include "parser.h"



Parser::Parser(string input) {
    scanner = new Scanner(input);
    advance();
}

//Teremos um (1) método para cada não-terminal

void Parser::run() {
    goal();
}

void Parser::advance() {
    lToken = scanner->nextToken();
}

void Parser::match(int t) {
    if (lToken->name == t || lToken->attribute == t)
        advance();
    else
        error("Erro inesperado");
}

void Parser::goal() {
    expr();
}

void Parser::expr() {
    term();
    exprLinha();
}

void Parser::exprLinha() {
    if (lToken->name == PLUS || lToken->name == MINUS) {
        match(lToken->name);
        term();
        exprLinha();
    }
}

void Parser::term() {
    factor();
    termLinha();
}

void Parser::termLinha() {
    if (lToken->name == MULT || lToken->name == DIV) {
        match(lToken->name);
        factor();
        termLinha();
    }
}

void Parser::factor() {
    if (lToken->name == ID || lToken->name == NUMBER) {
        match(lToken->name);
    } else if (lToken->name == L_PAREN) {
        match(L_PAREN);
        expr();
        match(R_PAREN);
    } else {
        error("Erro: fator mal formado!");
    }
}

void Parser::error(string str) {
    cout << str << endl;
    exit(EXIT_FAILURE);
}
