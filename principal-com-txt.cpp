#include "parser.h"
#include <iostream>
#include <fstream>
#include <sstream>
string* vet;

int main(int argc, char* argv[]) {
    string input, content;

    // Abre o arquivo de teste em modo de leitura
    ifstream file(argv[1]);

    if(argc != 2){
        cout << "Uso: ./compiler nome_arquivo.mj\n";
        return 1;
    }

    // Verifica se o arquivo foi aberto com sucesso
    if(!file.is_open()){
        cout << "Erro ao abrir o arquivo.\n";
        return 1; // Saída de erro
    }

    // Lê todo o conteúdo do arquivo
    stringstream buffer;
    buffer << file.rdbuf();
    content = buffer.str();
    //cout << content;

    // Cria um objeto Parser com o conteúdo do arquivo
    Parser* parser = new Parser(content);

    // Executa a análise sintática
    parser->run();

    return 0;
}





