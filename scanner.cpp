#include "scanner.h"
#include <set>

// Palavras reservadas
set<string> reservedWords = {
    "if",
    "else",
    "while",
    "class",
    "main",
    "void",
    "static",
    "extends",
    "false",
    "true",
    "int",
    "boolean",
    "return",
    "new",
    "String",
    "public",
    "this",
    "System.out.println",
    "args"
};


// Construtor
Scanner::Scanner(string input) {
    this->input = input;
    pos = 0;
}

// Método que retorna o próximo token da entrada
Token* Scanner::nextToken() {
    Token* tok;
    string lexeme;

    while (pos < input.length()) {

        // Caracter atual a ser lido
        char currentChar = input[pos];

        // Verifica se é um espaço em branco e avança para o próximo caractere
        if (isspace(currentChar)) {
            pos++;
            continue;
        }

        // Verifica se é um comentário de linha (//) e avança para o próximo caractere (Deve ser ignorado)
        if (currentChar == '/' && pos + 1 < input.length() && input[pos + 1] == '/') {
            while (pos < input.length() && input[pos] != '\n') {
                pos++;
            }
            continue;
        }

        // Verifica se é um comentário de bloco (/**/) e avança para o próximo caractere (Deve ser ignorado)
        if (currentChar == '/' && pos + 1 < input.length() && input[pos + 1] == '*') {
            pos += 2;
            while (pos + 1 < input.length() && !(input[pos] == '*' && input[pos + 1] == '/')) {
                pos++;
            }
            pos += 2;
            continue;
        }


        if (isalpha(currentChar) || currentChar == '_') {
            string identifier = "";
            identifier += currentChar;
            pos++;
            while (pos < input.length() && (isalnum(input[pos]) || input[pos] == '_')) {
                identifier += input[pos];
                pos++;
            }

			// Trata o System.out.println como uma única palavra reservada
            if (identifier == "System") {
                pos += 12;
                lexeme = "System.out.println";
                tok = new Token(SYSTEM_OUT_PRINT_LN, UNDEF, identifier);
                return tok;
            }

            // Verifica se o identificador é uma palavra reservada
            if (reservedWords.count(identifier) > 0) {
                // Retorna o token correspondente à palavra reservada
                if (identifier == "if")
                    tok = new Token(IF, UNDEF, identifier);
                else if (identifier == "else")
                    tok = new Token(ELSE, UNDEF, identifier);
                else if (identifier == "while")
                    tok = new Token(WHILE, UNDEF, identifier);
                else if (identifier == "class")
                    tok = new Token(CLASS, UNDEF, identifier);
                else if (identifier == "main")
                    tok = new Token(MAIN, UNDEF, identifier);
                else if (identifier == "void")
                    tok = new Token(VOID, UNDEF, identifier);
                else if (identifier == "static")
                    tok = new Token(STATIC, UNDEF, identifier);
                else if (identifier == "extends")
                    tok = new Token(EXTENDS, UNDEF, identifier);
                else if (identifier == "false")
                    tok = new Token(FALSE, UNDEF, identifier);
                else if (identifier == "true")
                    tok = new Token(TRUE, UNDEF, identifier);
                else if (identifier == "int")
                    tok = new Token(INT, UNDEF, identifier);
                else if (identifier == "boolean")
                    tok = new Token(BOOLEAN, UNDEF, identifier);
                else if (identifier == "return")
                    tok = new Token(RETURN, UNDEF, identifier);
                else if (identifier == "new")
                    tok = new Token(NEW, UNDEF, identifier);
                else if (identifier == "String")
                    tok = new Token(STRING, UNDEF, identifier);
                else if (identifier == "true")
                    tok = new Token(TRUE, UNDEF, identifier);
                else if (identifier == "public")
                    tok = new Token(PUBLIC, UNDEF, identifier);
                else if (identifier == "this")
                    tok = new Token(THIS, UNDEF, identifier);
                else if (identifier == "args")
                    tok = new Token(ID, UNDEF, identifier);
            } else {
                // Retorna o token ID para identificadores não reservados
                tok = new Token(ID, UNDEF, identifier);
            }

            lexeme = identifier;
            return tok;
        }


        // Verifica se é um número inteiro
        if (isdigit(currentChar)) {
            string number = "";
            number += currentChar;
            pos++;
            while (pos < input.length() && isdigit(input[pos])) {
                number += input[pos];
                pos++;
            }

            lexeme = number;
            tok = new Token(INTEGER_LITERAL, UNDEF, lexeme);
            return tok;
        }

        // Verifica os demais tokens
        switch (currentChar) {
            case '(':
                pos++;
                lexeme = "(";
            
                tok = new Token(L_PAREN, UNDEF, lexeme);
                return tok;
            case ')':
                pos++;
                lexeme = ")";
            
                tok = new Token(R_PAREN, UNDEF, lexeme);
                return tok;
            case '[':
                pos++;
                lexeme = "[";
            
                tok = new Token(L_BRACKET, UNDEF, lexeme);
                return tok;
            case ']':
                pos++;
                lexeme = "]";
            
                tok = new Token(R_BRACKET, UNDEF, lexeme);
                return tok;
            case '{':
                pos++;
                lexeme = "{";

                tok = new Token(L_BRACE, UNDEF, lexeme);
                return tok;
            case '}':
                pos++;
                lexeme = "}";

                tok = new Token(R_BRACE, UNDEF, lexeme);
                return tok;
            case ';':
                pos++;
                lexeme = ";";

                tok = new Token(SEMICOLON, UNDEF, lexeme);
                return tok;
            case '.':
                pos++;
                lexeme = ".";

                tok = new Token(DOT, UNDEF, lexeme);
                return tok;
            case '"':
                pos++;
                lexeme = '"';

                tok = new Token(QUOTE, UNDEF, lexeme);
                return tok;
            case ',':
                pos++;
                lexeme = ",";

                tok = new Token(COMMA, UNDEF, lexeme);
                return tok;
            case '+':
                pos++;
                lexeme = "+";
            
                tok = new Token(PLUS, UNDEF, lexeme);
                return tok;
            case '-':
                pos++;
                lexeme = "-";
            
                tok = new Token(MINUS, UNDEF, lexeme);
                return tok;
            case '*':
                pos++;
                lexeme = "*";
            
                tok = new Token(MULT, UNDEF, lexeme);
                return tok;
            case '/':
                pos++;
                lexeme = "/";
            
                tok = new Token(DIV, UNDEF, lexeme);
                return tok;
            case '=':
                pos++;
                if (pos < input.length() && input[pos] == '=') {
                    pos++;
                    lexeme = "==";
                
                    tok = new Token(EQ, UNDEF, lexeme);
                    return tok;
                }else{
                lexeme = "=";
            
                tok = new Token(ASSIGN, UNDEF, lexeme);
                return tok;
                }

            case '!':
                pos++;
                if (pos < input.length() && input[pos] == '=') {
                    pos++;
                    lexeme = "!=";
                
                    tok = new Token(NE, UNDEF, lexeme);
                    return tok;
                }
                lexeme = "!";
            
                tok = new Token(NOT, UNDEF, lexeme);
                return tok;
            case '<':
                pos++;
                if (pos < input.length() && input[pos] == '=') {
                    pos++;
                    lexeme = "<=";
                
                    tok = new Token(LE, UNDEF, lexeme);
                    return tok;
                }
                lexeme = "<";
            
                tok = new Token(LESS, UNDEF, lexeme);
                return tok;
            case '>':
                pos++;
                if (pos < input.length() && input[pos] == '=') {
                    pos++;
                    lexeme = ">=";
                
                    tok = new Token(GE, UNDEF, lexeme);
                    return tok;
                }
                lexeme = ">";
            
                tok = new Token(GT, UNDEF, lexeme);
                return tok;
            case '&':
                pos++;
                if (pos < input.length() && input[pos] == '&') {
                    pos++;
                    lexeme = "&&";
                
                    tok = new Token(AND, UNDEF, lexeme);
                    return tok;
                }
                lexicalError();
                break;
            default:

                lexicalError();
        }
    }

    tok = new Token(END_OF_FILE, UNDEF, "");
    return tok;
}

void Scanner::lexicalError() {
    cout << "Token mal formado\n";
    exit(EXIT_FAILURE);
}
