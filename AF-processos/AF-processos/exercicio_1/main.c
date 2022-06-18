#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
/*
Você deve escrever um programa em C em que o processo pai crie 2 processos filhos (fork()). 

Para cada processo filho criado, o processo pai deve imprimir "Processo pai criou XXX", onde XXX é o PID do processo criado.

Cada processo filho deve apenas imprimir "Processo filho XXX criado", onde XXX é o PID do processo corrente (use a função getpid() para isso).

O processo pai (e apenas ele) deve imprimir "Processo pai finalizado!", somente após os filhos terminarem (use a função wait() para aguardar que os 
filhos terminem de executar).


*/

//       (pai)      
//         |        
//    +----+----+
//    |         |   
// filho_1   filho_2


// ~~~ printfs  ~~~
// pai (ao criar filho): "Processo pai criou %d\n"
//    pai (ao terminar): "Processo pai finalizado!\n"
//  filhos (ao iniciar): "Processo filho %d criado\n"

// Obs:
// - pai deve esperar pelos filhos antes de terminar!


int main(int argc, char** argv) {
    for(int i =0; i < 4; i++) {
        printf("\n%i", getpid());
        fflush(stdout);
        if(fork() != 0) {
            printf("\n%i", getpid());
            fflush(stdout);
            for (int j=i; j < 4; j++)
            {   printf("\n%i", getpid());
                fflush(stdout);
                if(fork() == 0){
                    printf("\n%i", getpid());
                    fflush(stdout);
                    break;
                } break;
            } 
        }
    }

/*     for(int i=0; i<2;i++ ){

        pid_t pid;
        pid = fork();


        if(pid >= 0) { // se pid é positivo, criou o processo
            if (pid == 0){
                printf("Processo filho %d criado\n", getpid());
                exit(0);
            }     
            else {
                wait(NULL); // aguarda o termino do filho                
                printf("Processo pai criou %d\n", pid);
            }
        }
    }

    printf("Processo pai finalizado!\n"); */

    // ....

    /*************************************************
     * Dicas:                                        *
     * 1. Leia as intruções antes do main().         *
     * 2. Faça os prints exatamente como solicitado. *
     * 3. Espere o término dos filhos                *
     *************************************************/
    return 0;
}
