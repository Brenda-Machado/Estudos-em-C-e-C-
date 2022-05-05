// código para estudos da linguagem C
// alguns exemplos de comandos e estruturas essenciais

#include <stdio.h>// indica as funções que vão ser usadas no programa
// biblioteca standart de entradas e saídas

int main () { // função principal, início do funcionamento do programa

    int x; // armazena um número inteiro na memória

    x = 50; 

    printf("Print x na tela: %i.\n", x);

    int y = 25;

    int subtracao = x - y;

    printf("Print x-y na tela: %i.\n", subtracao);

    return 0;

}
// no terminal para compilar e rodar é só seguir os seguintes passos
// 1) cd C\ e\ C++/
// 2) g++ primeiros_passos.c
// 3) ./a.out
