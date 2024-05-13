#include "scanner.h"
#include <iostream>
#include <fstream>

string* vet;

void print(Token*);
void allocVetor();
void freeVetor();

int main(int argc, char* argv[]) {
    string input;

     // Verifica se foi fornecido o nome do arquivo de teste como argumento
    if (argc < 2) {
        cout << "Uso: " << argv[0] << " <arquivo_de_teste>\n";
        return 1; // Saída de erro
    }

    // Abre o arquivo de teste em modo de leitura
    ifstream file(argv[1]);

    // Verifica se o arquivo foi aberto com sucesso
    if (!file.is_open()) {
        cout << "Erro ao abrir o arquivo.\n";
        return 1; // Saída de erro
    }

    // Lê uma linha de entrada
    //getline(cin, input);

    // Cria um objeto Scanner com a entrada fornecida
    /*Scanner* scanner = new Scanner(input);

    // Aloca o vetor de strings para mapear os tokens
    allocVetor();

    Token* t;

    do {
        // Obtém o próximo token do scanner
        t = scanner->nextToken();

        // Imprime o token
        print(t);
    } while (t->name != END_OF_FILE);*/

    // Libera a memória alocada para o scanner
    //delete scanner;

     while (getline(file, input)) {
        // Cria um objeto Scanner com a entrada fornecida
        Scanner scanner(input);

        allocVetor();

        Token* t;

        // Analisa os tokens até o final do arquivo
        do {
            t = scanner.nextToken();
            //cout << t->name << " ";
            print(t);
        } while (t->name != END_OF_FILE);

        // Libera a memória alocada para o vetor de strings
        freeVetor();
        //delete scanner;
    }

    // Libera a memória alocada para o vetor de strings
    //freeVetor();
    file.close();


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
    vet[TIMES] = "TIMES";
    vet[DIVIDE] = "DIVIDE";
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
    vet[BOOLEAN] = "BOOLEAN"; // PR
    vet[CLASS] = "CLASS"; // PR
    vet[ELSE] = "ELSE"; // PR
    vet[EXTENDS] = "EXTENDS"; // PR
    vet[FALSE] = "FALSE"; // PR
    vet[IF] = "IF"; // PR
    vet[INT] = "INT"; // PR
    vet[LENGTH] = "LENGTH"; // PR
    vet[MAIN] = "MAIN"; // PR
    vet[NEW] = "NEW"; // PR
    vet[PUBLIC] = "PUBLIC"; // PR
    vet[RETURN] = "RETURN"; // PR
    vet[STATIC] = "STATIC"; // PR
    vet[STRING] = "STRING"; // PR
    vet[SYSTEM_OUT_PRINTLN] = "SYSTEM_OUT_PRINTLN"; // PR
    vet[THIS] = "THIS"; // PR
    vet[TRUE] = "TRUE"; // PR
    vet[VOID] = "VOID"; // PR
    vet[WHILE] = "WHILE"; // PR
    vet[END_OF_FILE] = "END_OF_FILE";
}

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


