#include "token.h"

class Scanner
{
    private:
        string input;//Armazena o texto de entrada que será analisado
        int pos;//Posição atual de qual caractere está sendo analisado

    public:
        //Construtor
        //Inicializa o objeto Scanner com o texto de entrada fornecido
        Scanner(string);

        //Método que retorna o próximo token da entrada
        //Responsável por analisar o texto de entrada e retornar o próximo token encontrado.
        Token* nextToken();

        //Método para manipular erros
        void lexicalError();
};
