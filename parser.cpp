#include "parser.h"

Parser::Parser(string input) {
    scanner = new Scanner(input);
    advance();
}

void Parser::advance() {
    int prevTokenName = currentToken ? currentToken->name : -1;
    currentToken = scanner->nextToken();
}

void Parser::match(int expected) {
    if (currentToken->name == expected) {
        advance();
    } else {
        syntaxError("expected " + getTokenName(expected) + " but found " + currentToken->lexeme);
    }
}

void Parser::syntaxError(std::string message) {
    std::cerr << "Syntax error on line " << scanner->getLineNumber() << ": " << message << std::endl;
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

    // Adicionado para permitir métodos dentro da classe principal
    while (currentToken->name == PUBLIC || currentToken->name == STATIC) {
        MethodDeclaration();
    }

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
    while (currentToken->name == PUBLIC) {
        MethodDeclaration();
    }
    match(R_BRACE);
}

void Parser::VarDeclaration() {
    Type();
    match(ID);
    if (currentToken->name == L_BRACKET) {
        match(L_BRACKET);
		if(currentToken->name == INTEGER_LITERAL){
			match(INTEGER_LITERAL);
		}else{
			match(R_BRACKET);
		}
        
        
    }
    if (currentToken->name == ASSIGN) {
        match(ASSIGN);
        Expression();
    }
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
        syntaxError("expected type but found " + getTokenName(currentToken->name));
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
	
    while (currentToken->name == L_BRACE || currentToken->name == IF || currentToken->name == WHILE || currentToken->name == SYSTEM_OUT_PRINT_LN || currentToken->name == ID) {
        Statement();
    }
    }

    

    
    match(RETURN); 
    Expression(); 
    match(SEMICOLON); 

    match(R_BRACE);
}

void Parser::Params() {
    Type();
    if (currentToken->name == L_BRACKET) {
        match(L_BRACKET);
        match(R_BRACKET);
    }
    match(ID);
    while (currentToken->name == COMMA) {
        match(COMMA);
        Type();
        if (currentToken->name == L_BRACKET) {
            match(L_BRACKET);
            match(R_BRACKET);
        }
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
    } else if (currentToken->name == ID) {
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
            syntaxError("expected '=' or '[' but found " + getTokenName(currentToken->name));
        }
    } else if (currentToken->name == INT || currentToken->name == BOOLEAN) {
        VarDeclaration();
    } else {
        syntaxError("expected statement but found " + getTokenName(currentToken->name));
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
        syntaxError("expected unary expression but found " + getTokenName(currentToken->name));
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
            syntaxError("expected type after 'new' but found " + getTokenName(currentToken->name));
        }
    } else if (currentToken->name == INTEGER_LITERAL || currentToken->name == TRUE || currentToken->name == FALSE) {
        match(currentToken->name);
    } else if (currentToken->name == L_PAREN) {
        match(L_PAREN);
        Expression();
        match(R_PAREN); 
    } else {
        syntaxError("expected primary expression but found " + getTokenName(currentToken->name));
    }
}

void Parser::ExpressionsList() {
    Expression();
    while (currentToken->name == COMMA) {
        match(COMMA);
        Expression();
    }
}

string Parser::getTokenName(int tokenId) {
    switch (tokenId) {
        case IF: return "if";
        case ELSE: return "else";
        case WHILE: return "while";
        case CLASS: return "class";
        case MAIN: return "main";
        case VOID: return "void";
        case STATIC: return "static";
        case EXTENDS: return "extends";
        case FALSE: return "false";
        case TRUE: return "true";
        case INT: return "int";
        case BOOLEAN: return "boolean";
        case RETURN: return "return";
        case NEW: return "new";
        case STRING: return "String";
        case PUBLIC: return "public";
        case THIS: return "this";
        case SYSTEM_OUT_PRINT_LN: return "System.out.println";
        case ID: return "identifier";
        case INTEGER_LITERAL: return "integer literal";
        case L_PAREN: return "(";
        case R_PAREN: return ")";
        case L_BRACKET: return "[";
        case R_BRACKET: return "]";
        case L_BRACE: return "{";
        case R_BRACE: return "}";
        case SEMICOLON: return ";";
        case COMMA: return ",";
        case DOT: return ".";
        case ASSIGN: return "=";
        case PLUS: return "+";
        case MINUS: return "-";
        case MULT: return "*";
        case DIV: return "/";
        case LESS: return "<";
        case GT: return ">";
        case EQ: return "==";
        case NE: return "!=";
        case NOT: return "!";
        case AND: return "&&";
        default: return "unknown token";
    }
}
