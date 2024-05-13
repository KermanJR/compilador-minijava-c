#include "parser.h"

Parser::Parser(string input) {
    scanner = new Scanner(input);
    advance();
}

void Parser::run() {
    Program();
    if (ltoken->name != END_OF_FILE) {
        error("Token inesperado após o término do programa");
    }
}

void Parser::advance() {
    ltoken = scanner->nextToken();
}

void Parser::match(int tokenType) {
    if (ltoken->name == tokenType) {
        advance();
    } else {
        error("Token inesperado");
    }
}


void Parser::Program() {
    MainClass();
    while (ltoken->name == CLASS) {
        ClassDeclaration();
    }
}

void Parser::MainClass() {
    match(CLASS);
    match(ID);
    match(L_BRACE);
    match(PUBLIC);
    match(STATIC);
    match(VOID);
    match(MAIN);
    match(L_PAREN);
    match(STRING);
    match(L_BRACKET);
    match(R_BRACKET);
    match(ID);
    match(R_PAREN);
    match(L_BRACE);
    Statement();
    match(R_BRACE);
}

void Parser::ClassDeclaration() {
    match(CLASS);
    match(ID);
    if (ltoken->name == EXTENDS) {
        advance();
        match(ID);
    }
    match(L_BRACE);
    while (ltoken->name == INTEGER_LITERAL || ltoken->name == BOOLEAN || ltoken->name == ID) {
        VarDeclaration();
    }
    while (ltoken->name == PUBLIC) {
        MethodDeclaration();
    }
    match(R_BRACE);
}

void Parser::VarDeclaration() {
    Type();
    match(ID);
    match(SEMICOLON);
}

void Parser::MethodDeclaration() {
    match(PUBLIC);
    Type();
    match(ID);
    match(L_PAREN);
    if (ltoken->name == INTEGER_LITERAL || ltoken->name == BOOLEAN || ltoken->name == ID) {
        Params();
    }
    match(R_PAREN);
    match(L_BRACE);
    while (ltoken->name == INTEGER_LITERAL || ltoken->name == BOOLEAN || ltoken->name == ID) {
        VarDeclaration();
    }
    while (ltoken->name == L_BRACE || ltoken->name == IF || ltoken->name == WHILE || ltoken->name == SYSTEM_OUT_PRINTLN || ltoken->name == ID) {
        Statement();
    }
    match(RETURN);
    Expression();
    match(SEMICOLON);
    match(R_BRACE);
}

void Parser::Params() {
    Type();
    match(ID);
    while (ltoken->name == COMMA) {
        advance();
        Type();
        match(ID);
    }
}

void Parser::Type() {
    if (ltoken->name == INTEGER_LITERAL) {
        advance();
        if (ltoken->name == L_BRACKET) {
            advance();
            match(R_BRACKET);
        }
    } else if (ltoken->name == BOOLEAN) {
        advance();
    } else if (ltoken->name == ID) {
        advance();
    } else {
        error("Tipo invalido");
    }
}

void Parser::Statement() {
    if (ltoken->name == L_BRACE) {
        advance();
        while (ltoken->name == L_BRACE || ltoken->name == IF || ltoken->name == WHILE || ltoken->name == SYSTEM_OUT_PRINTLN || ltoken->name == ID) {
            Statement();
        }
        match(R_BRACE);
    } else if (ltoken->name == IF) {
        advance();
        match(L_PAREN);
        Expression();
        match(R_PAREN);
        Statement();
        match(ELSE);
        Statement();
    } else if (ltoken->name == WHILE) {
        advance();
        match(L_PAREN);
        Expression();
        match(R_PAREN);
        Statement();
    } else if (ltoken->name == SYSTEM_OUT_PRINTLN) {
        advance();
        match(L_PAREN);
        Expression();
        match(R_PAREN);
        match(SEMICOLON);
    } else if (ltoken->name == ID) {
        advance();
        if (ltoken->name == ASSIGN) {
            advance();
            Expression();
            match(SEMICOLON);
        } else if (ltoken->name == L_BRACKET) {
            advance();
            Expression();
            match(R_BRACKET);
            match(ASSIGN);
            Expression();
            match(SEMICOLON);
        } else {
            error("Declaracao invalida");
        }
    } else {
        error("Declaracao invalida");
    }
}

void Parser::Expression() {
    RelExpression();
    while (ltoken->name == AND) {
        advance();
        RelExpression();
    }
}

void Parser::RelExpression() {
    AddExpression();
    while (ltoken->name == LESS || ltoken->name == LE || ltoken->name == GT || ltoken->name == GE || ltoken->name == EQ || ltoken->name == NE) {
        advance();
        AddExpression();
    }
}

void Parser::AddExpression() {
    MultExpression();
    while (ltoken->name == PLUS || ltoken->name == MINUS) {
        advance();
        MultExpression();
    }
}

void Parser::MultExpression() {
    UnExpression();
    while (ltoken->name == MULT || ltoken->name == DIV) {
        advance();
        UnExpression();
    }
}

void Parser::UnExpression() {
    if (ltoken->name == NOT || ltoken->name == MINUS) {
        advance();
        UnExpression();
    } else {
        PrimExpression();
    }
}

void Parser::PrimExpression() {
    if (ltoken->name == INTEGER_LITERAL || ltoken->name == TRUE || ltoken->name == FALSE || ltoken->name == ID || ltoken->name == THIS) {
        advance();
    } else if (ltoken->name == L_PAREN) {
        advance();
        Expression();
        match(R_PAREN);
    } else if (ltoken->name == NEW) {
        advance();
        if (ltoken->name == INTEGER_LITERAL) {
            advance();
            match(L_BRACKET);
            Expression();
            match(R_BRACKET);
        } else if (ltoken->name == ID) {
            advance();
            match(L_PAREN);
            match(R_PAREN);
        } else {
            error("Expressao primaria invalida");
        }
    } else {
        error("Expressao primaria invalida");
    }
    while (ltoken->name == DOT || ltoken->name == L_BRACKET) {
        if (ltoken->name == DOT) {
            advance();
            match(ID);
            if (ltoken->name == L_PAREN) {
                advance();
                if (ltoken->name != R_PAREN) {
                    ExpressionsList();
                }
                match(R_PAREN);
            }
        } else if (ltoken->name == L_BRACKET) {
            advance();
            Expression();
            match(R_BRACKET);
        }
    }
}

void Parser::ExpressionsList() {
    Expression();
    while (ltoken->name == COMMA) {
        advance();
        Expression();
    }
}

void Parser::error(string str) {
    cout << "Parsing error: " << str << " at token " << ltoken->lexeme << endl;
    exit(EXIT_FAILURE);
}
