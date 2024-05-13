#include "scanner.h"

//Construtor
Scanner::Scanner(string input)
{
    this->input = input;
    cout << "Entrada: " << input << endl << "Tamanho: "
         << input.length() << endl;

    pos = 0;
}

//Método que retorna o próximo token da entrada
Token* Scanner::nextToken() {
    Token* tok;
    string lexeme;

    while (pos < input.length()) {

        //Caracter atual a ser lido
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

        // Verifica se é um ID
        if (isalpha(currentChar) || currentChar == '_') {
            string identifier = "";
            identifier += currentChar;
            pos++;
            while (pos < input.length() && (isalnum(input[pos]) || input[pos] == '_')) {
                identifier += input[pos];
                pos++;
            }


            // Verifica se o identificador é "System.out.println"
            if (identifier == "System.out.println") {
                //lexeme.push_back(identifier)
                tok = new Token(SYSTEM_OUT_PRINTLN, UNDEF);
                return tok;
            } else {
                //lexeme.push_back(identifier)
                tok = new Token(ID, UNDEF);
                return tok;
            }
        }

        // Verifica se é um número inteiro
        if (isdigit(currentChar)) {
            string number = "";
            number += currentChar;
            //lexeme.push_back(number)
            pos++;
            while (pos < input.length() && isdigit(input[pos])) {
                number += input[pos];
                pos++;
            }
             //lexeme.push_back(number)
             tok = new Token(NUMBER, UNDEF);
             return tok;
        }

        // Verifica os demais tokens
        switch (currentChar) {
            case '(':
                pos++;
                 tok = new Token(L_PAREN);
                 return tok;
            case ')':
                pos++;
                 tok = new Token(R_PAREN);
                 return tok;
            case '[':
                pos++;
                 tok = new Token(L_BRACKET);
                 return tok;
            case ']':
                pos++;
                 tok = new Token(R_BRACKET);
                 return tok;
            case '{':
                pos++;
                 tok = new Token(L_BRACE);
                 return tok;
            case '}':
                pos++;
                 tok = new Token(R_BRACE);
                 return tok;
            case ';':
                pos++;
                 tok = new Token(SEMICOLON);
                 return tok;
            case '.':
                pos++;
                 tok = new Token(DOT);
                 return tok;
            case '"':
                pos++;
                 tok = new Token(QUOTE);
                 return tok;
            case ',':
                pos++;
                 tok = new Token(COMMA);
                 return tok;
            case '+':
                pos++;
                return new Token(PLUS);
                return tok;
            case '-':
                pos++;
                 tok = new Token(MINUS);
                 return tok;
            case '*':
                pos++;
                 tok = new Token(MULT);
                 return tok;
            case '/':
                pos++;
                 tok = new Token(DIV);
                 return tok;
            case '=':
                pos++;
                if (pos < input.length() && input[pos] == '=') {
                    pos++;
                     tok = new Token(EQ);
                     return tok;
                }
                 tok =  new Token(ASSIGN);
                 return tok;
            case '!':
                pos++;
                if (pos < input.length() && input[pos] == '=') {
                    pos++;
                     tok = new Token(NE);
                     return tok;
                }
                 tok = new Token(NOT);
                 return tok;
            case '<':
                pos++;
                if (pos < input.length() && input[pos] == '=') {
                    pos++;
                     tok = new Token(LE);
                     return tok;
                }
                 tok = new Token(LESS);
                 return tok;
            case '>':
                pos++;
                if (pos < input.length() && input[pos] == '=') {
                    pos++;
                     tok = new Token(GE);
                     return tok;
                }
                 tok = new Token(GT);
                 return tok;
            case '&':
                pos++;
                if (pos < input.length() && input[pos] == '&') {
                    pos++;
                     tok = new Token(AND);
                     return tok;
                }
                lexicalError();
                break;
            default:
                lexicalError();
        }
    }

     tok = new Token(END_OF_FILE);

     return tok;
}

void Scanner::lexicalError()
{
    cout << "Token mal formado\n";

    exit(EXIT_FAILURE);
}
