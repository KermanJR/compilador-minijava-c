
#include "scanner.h"

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


        //Verifica se é ID ou Palavra reservada
        if (isalpha(currentChar) || currentChar == '_') {
            string identifier = "";
            identifier += currentChar;
            pos++;
            while (pos < input.length() && isalnum(input[pos])) {
                identifier += input[pos];
                pos++;
            }

            // Verifica se é uma palavra reservada
            cout << identifier << endl;
            if (identifier == "boolean") {
                tok = new Token(BOOLEAN, UNDEF);
            } else if (identifier == "class") {
                tok = new Token(CLASS, UNDEF);
            } else if (identifier == "else") {
                tok = new Token(ELSE, UNDEF);
            } else if (identifier == "extends") {
                tok = new Token(EXTENDS, UNDEF);
            } else if (identifier == "false") {
                tok = new Token(FALSE, UNDEF);
            } else if (identifier == "if") {
                tok = new Token(IF, UNDEF);
            } else if (identifier == "int") {
                tok = new Token(INT, UNDEF);
            } else if (identifier == "length") {
                tok = new Token(LENGTH, UNDEF);
            } else if (identifier == "main") {
                tok = new Token(MAIN, UNDEF);
            } else if (identifier == "new") {
                tok = new Token(NEW, UNDEF);
            } else if (identifier == "public") {
                tok = new Token(PUBLIC, UNDEF);
            } else if (identifier == "return") {
                tok = new Token(RETURN, UNDEF);
            } else if (identifier == "static") {
                tok = new Token(STATIC, UNDEF);
            } else if (identifier == "String") {
                tok = new Token(STRING, UNDEF);
            } else if (identifier == "true") {
                tok = new Token(TRUE, UNDEF);
            } else if (identifier == "void") {
                tok = new Token(VOID, UNDEF);
            } else if (identifier == "while") {
                tok = new Token(WHILE, UNDEF);
            } else {
                // Se não for uma palavra reservada, trata como um ID genérico
                tok = new Token(ID, UNDEF);
            }
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
                lexeme = "\"";
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
