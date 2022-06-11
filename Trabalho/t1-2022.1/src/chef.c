#include <stdlib.h>
#include "globals.c"
#include "chef.h"
#include "config.h"
#include "buffet.c"


void *chef_run()
{   
    buffet_t *buffet = globals_get_buffets();

    while (buffet_aberto == TRUE)
    {
        chef_check_food();
        msleep(5000);
    }
    
    pthread_exit(NULL);
}


void chef_put_food()
{
    for (i = 0; i < numero_buffets; i++)
    {
        //temporario -> colocar só onde acabou a comida
        for(j = 0; j < 5; j++)
            buffet[i]._meal[j] = 40;
}
void chef_check_food()
{
    if (tem_comida == FALSE) {
        chef_put_food();
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