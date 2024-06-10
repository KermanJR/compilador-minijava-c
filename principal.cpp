#include "scanner.h"

string* vet;
void print(Token*);
void allocVetor();
void freeVetor();

int main(int argc, char* argv[])
{
    //Verifica se foi executado corretamente
    //Essa main espera receber o nome do arquivo a ser
    //executado na linha de comando.
    if (argc != 2)
    {
        cout << "Uso: ./compiler nome_arquivo.mj\n";
        return 1;
    }

    string input;

    getline(cin, input);

    Scanner* scanner = new Scanner(input);
    allocVetor();

    Token* t;

    do
    {
        t = scanner->nextToken();

        print(t);
    }while (t->name != END_OF_FILE);

    delete scanner;

    return 0;
}

// Aloca o vetor de strings para mapear os tokens
void allocVetor() {
    vet = new string[END_OF_FILE + 1];

    vet[UNDEF] = "UNDEF";
    vet[ID] = "ID";
    vet[INTEGER_LITERAL] = "INTEGER_LITERAL";
    vet[PLUS] = "PLUS";
    vet[MINUS] = "MINUS";
    vet[MULT] = "MULT";
    vet[DIV] = "DIV";
    vet[ASSIGN] = "ASSIGN";
    vet[EQ] = "EQ";
    vet[NOT] = "NOT";
    vet[NE] = "NE";
    vet[LESS] = "LESS";
    vet[LE] = "LE";
    vet[GT] = "GT";
    vet[GE] = "GE";
    vet[AND] = "AND";
    vet[L_PAREN] = "L_PAREN";
    vet[R_PAREN] = "R_PAREN";
    vet[L_BRACKET] = "L_BRACKET";
    vet[R_BRACKET] = "R_BRACKET";
    vet[L_BRACE] = "L_BRACE";
    vet[R_BRACE] = "R_BRACE";
    vet[SEMICOLON] = "SEMICOLON";
    vet[QUOTE] = "QUOTE";
    vet[DOT] = "DOT";
    vet[COMMA] = "COMMA";
    vet[IF] = "IF";
    vet[ELSE] = "ELSE";
     vet[WHILE] = "WHILE";
      vet[CLASS] = "CLASS";
       vet[MAIN] = "MAIN";
        vet[VOID] = "VOID";
         vet[STATIC] = "STATIC";
          vet[EXTENDS] = "EXTENDS";
           vet[FALSE] = "FALSE";
            vet[TRUE] = "TRUE";
             vet[INT] = "INT";
              vet[RETURN] = "RETURN";
              vet[NEW] = "NEW";
              vet[STRING] = "STRING";
              vet[THIS] = "THIS";
               vet[PUBLIC] = "PUBLIC";
               vet[LENGTH] = "LENGTH";
                vet[THIS] = "THIS";
                vet[SYSTEM_OUT_PRINT_LN] = "SYSTEM_OUT_PRINT_LN";
              vet[END_OF_FILE] = "END_OF_FILE";

}

// Libera a memória

// Libera a memória alocada para o vetor de strings
void freeVetor() {
    delete[] vet;
}

// Imprime o token
void print(Token* t) {
    std::cout << vet[t->name];

    // Se o atributo do token não for UNDEF, imprime o atributo
    if (t->attribute != UNDEF)
        std::cout << "(" << vet[t->attribute] << ")";

    std::cout << " ";
}



