#include <stdlib.h>
#include "globals.h"
#include "chef.h"
#include "config.h"
#include "buffet.h"
#include <semaphore.h>

int id_do_buffet; // número do buffet da bacia
int id_da_bacia; // id da bacia para repor

void *chef_run()
{   /* Espera o buffet abrir. */
    while (buffet_aberto == NULL) {
        msleep(1); 
    } 
    while (buffet_aberto == TRUE) /* variável mantida pelo próprio buffet, se fechar, o chef para de trabalhar */
    {
        chef_check_food();
    }
    
    pthread_exit(NULL);
}


void chef_put_food()
{   
    buffet_t *buffet = globals_get_buffets();
    /* repõe a comida da bacia vazia */
    buffet[id_do_buffet]._meal[id_da_bacia] = 40;
    /* estudantes podem se servir */
    sem_post(&bacia[id_do_buffet*5+id_da_bacia]);
}
void chef_check_food()
{
    buffet_t *buffet = globals_get_buffets();
    for (int i = 0; i < numero_buffets; i++)
    {
        for(int j = 0; j < 5; j++)
            /* checa se há comida na bacia. */
            if (buffet[i]._meal[j] == 0) {
                /* bloqueia a bacia para o estudante esperar. */
                sem_wait(&bacia[i*5+j]);
                id_do_buffet = i;
                id_da_bacia = j;
                /* só põe comida se estiver vezia e somente uma bacia por vez */
                chef_put_food();
            }
    }
}

/* --------------------------------------------------------- */
/* ATENÇÃO: Não será necessário modificar as funções abaixo! */
/* --------------------------------------------------------- */

void chef_init(chef_t *self)
{       
    pthread_create(&self->thread, NULL, chef_run, NULL);
}

void chef_finalize(chef_t *self)
{
    pthread_join(self->thread, NULL);
    free(self);
}