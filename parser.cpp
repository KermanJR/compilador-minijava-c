#include "parser.h"

Parser::Parser(string input) {
    scanner = new Scanner(input);
    advance();
}

void Parser::advance() {
    currentToken = scanner->nextToken();
}

void Parser::match(int expected) {
    if (currentToken->name == expected) {
        advance();
    } else {
        syntaxError("expected " + std::to_string(expected) + " but found " + currentToken->lexeme);
    }
}

void Parser::syntaxError(std::string message) {
    std::cerr << "Syntax error: " << message << std::endl;
    exit(EXIT_FAILURE);
}


void Parser::run() {
    Program();
    std::cout << "Compilation successful." << std::endl;
}

void Parser::Program() {
    MainClass();
    while (currentToken->name == CLASS) {
        ClassDeclaration();
    }
    match(END_OF_FILE);
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
    while (currentToken->name != R_BRACE) {
        Statement();
    }
    match(R_BRACE);
    match(R_BRACE);
}

void Parser::ClassDeclaration() {
    match(CLASS);
    match(ID);
    if (currentToken->name == EXTENDS) {
        match(EXTENDS);
        match(ID);
    }
    match(L_BRACE);
    while (currentToken->name == INT || currentToken->name == BOOLEAN || currentToken->name == ID) {
        VarDeclaration();
    }
    while (currentToken->name == PUBLIC) {
        MethodDeclaration();
    }
    match(R_BRACE);
}

void Parser::VarDeclaration() {
    Type();
    match(ID);
    match(SEMICOLON);
}

void Parser::Type() {
    if (currentToken->name == INT) {
        match(INT);
        if (currentToken->name == L_BRACKET) {
            match(L_BRACKET);
            match(R_BRACKET);
        }
    } else if (currentToken->name == BOOLEAN) {
        match(BOOLEAN);
    } else if (currentToken->name == ID) {
        match(ID);
    } else {
        std::cerr << "Syntax error: expected type but found " << currentToken->name << std::endl;
        exit(EXIT_FAILURE);
    }
}


void Parser::MethodDeclaration() {
    match(PUBLIC);
    Type();
    match(ID);
    match(L_PAREN);
    if (currentToken->name == INT || currentToken->name == BOOLEAN || currentToken->name == ID) {
        Params();
    }
    match(R_PAREN);
    match(L_BRACE);
    while (currentToken->name == INT || currentToken->name == BOOLEAN || currentToken->name == ID) {
        VarDeclaration();
    }
    while (currentToken->name == L_BRACE || currentToken->name == IF || currentToken->name == WHILE || currentToken->name == SYSTEM_OUT_PRINT_LN || currentToken->name == ID) {
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
    while (currentToken->name == COMMA) {
        match(COMMA);
        Type();
        match(ID);
    }
}


void Parser::Statement() {
    if (currentToken->name == L_BRACE) {
        match(L_BRACE);
        while (currentToken->name != R_BRACE) {
            Statement();
        }
        match(R_BRACE);
    } else if (currentToken->name == IF) {
        match(IF);
        match(L_PAREN);
        Expression();
        match(R_PAREN);
        Statement();
        match(ELSE);
        Statement();
    } else if (currentToken->name == WHILE) {
        match(WHILE);
        match(L_PAREN);
        Expression();
        match(R_PAREN);
        Statement();
    } else if (currentToken->name == SYSTEM_OUT_PRINT_LN) {
        match(SYSTEM_OUT_PRINT_LN);
        match(L_PAREN);
		Expression();
        match(R_PAREN);
        match(SEMICOLON);
    }else if (currentToken->name == ID) {
        string idName = currentToken->lexeme;
        match(ID);
        if (currentToken->name == ASSIGN) {
            match(ASSIGN);
            Expression();
            match(SEMICOLON);
        } else if (currentToken->name == L_BRACKET) {
            match(L_BRACKET);
            Expression();
            match(R_BRACKET);
            match(ASSIGN);
            Expression();
            match(SEMICOLON);
        } else {
            std::cerr << "Syntax error: expected '=' or '[' but found " << currentToken->name << std::endl;
            exit(EXIT_FAILURE);
        }
    } else if (currentToken->name == INT || currentToken->name == BOOLEAN) {
        Type();
        match(ID);
        match(SEMICOLON);
    } else {
        std::cerr << "Syntax error: expected statement but found " << currentToken->name << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Parser::Expression() {
    RelExpression();
    while (currentToken->name == AND) {
        match(AND);
        RelExpression();
    }
}

void Parser::RelExpression() {
    AddExpression();
    while (currentToken->name == LESS || currentToken->name == GT || currentToken->name == EQ || currentToken->name == NE) {
        if (currentToken->name == LESS) {
            match(LESS);
        } else if (currentToken->name == GT) {
            match(GT);
        } else if (currentToken->name == EQ) {
            match(EQ);
        } else if (currentToken->name == NE) {
            match(NE);
        }
        AddExpression();
    }
}

void Parser::AddExpression() {
    MultExpression();
    while (currentToken->name == PLUS || currentToken->name == MINUS) {
        if (currentToken->name == PLUS) {
            match(PLUS);
        } else if (currentToken->name == MINUS) {
            match(MINUS);
        }
        MultExpression();
    }
}

void Parser::MultExpression() {
    UnExpression();
    while (currentToken->name == MULT || currentToken->name == DIV) {
        if (currentToken->name == MULT) {
            match(MULT);
        } else if (currentToken->name == DIV) {
            match(DIV);
        }
        UnExpression();
    }
}

void Parser::UnExpression() {
    if (currentToken->name == NOT) {
        match(NOT);
        UnExpression();
    } else if (currentToken->name == MINUS) {
        match(MINUS);
        UnExpression();
    } else if (currentToken->name == INTEGER_LITERAL || currentToken->name == TRUE || currentToken->name == FALSE || currentToken->name == NEW || currentToken->name == ID || currentToken->name == THIS || currentToken->name == L_PAREN) {
        PrimExpression();
    } else {
        std::cerr << "Syntax error: expected unary expression but found " << currentToken->name << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Parser::PrimExpression() {
    if (currentToken->name == ID) {
        match(ID);
        if (currentToken->name == DOT) {
            match(DOT);
            if (currentToken->name == LENGTH) {
                match(LENGTH);
            } else {
                match(ID);
                if (currentToken->name == L_PAREN) {
                    match(L_PAREN);
                    if (currentToken->name == INTEGER_LITERAL || currentToken->name == TRUE || currentToken->name == FALSE || currentToken->name == NEW || currentToken->name == ID || currentToken->name == THIS || currentToken->name == L_PAREN) {
                        ExpressionsList();
                    }
                    match(R_PAREN);
                }
            }
        } else if (currentToken->name == L_BRACKET) {
            match(L_BRACKET);
            Expression();
            match(R_BRACKET);
        }
    } else if (currentToken->name == THIS) {
        match(THIS);
    } else if (currentToken->name == NEW) {
        match(NEW);
        if (currentToken->name == INT) {
            match(INT);
            match(L_BRACKET);
            Expression();
            match(R_BRACKET);
        } else if (currentToken->name == ID) {
            match(ID);
            match(L_PAREN);
            match(R_PAREN);
        } else {
            std::cerr << "Syntax error: expected type after 'new' but found " << currentToken->name << std::endl;
            exit(EXIT_FAILURE);
        }
    } else if (currentToken->name == INTEGER_LITERAL || currentToken->name == TRUE || currentToken->name == FALSE) {
        match(currentToken->name);
    } else if (currentToken->name == L_PAREN) {
        match(L_PAREN);
        Expression();
        match(R_PAREN);
    } else {
        std::cerr << "Syntax error: expected primary expression but found " << currentToken->name << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Parser::ExpressionsList() {
    Expression();
    while (currentToken->name == COMMA) {
        match(COMMA);
        Expression();
    }
}
