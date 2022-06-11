#include <stdlib.h>
#include <semaphore.h>
#include "worker_gate.h"
#include "globals.h"
#include "globals.c"
#include "config.h"
#include "buffet.h"
#include "queue.h"
#include "queue.c"

int comida_buffet = 1;
int fila_cheia = 0;

void worker_gate_look_queue() // verifica se as filas estão cheias
{   

    buffet_t *buffet = globals_get_buffets();
    if (buffet-> queue_left[5] == 1 && buffet-> queue_right[5] == 1) {
        fila_cheia = 1;
    } else {
        fila_cheia = 0;
    }
}

void worker_gate_remove_student() // retira um estudante da fila
{
    queue_t *queue = globals_get_queue();
    queue_remove(queue);
}

void worker_gate_look_buffet() // verifica se há comida no buffet
{   
    if (tem_comida == TRUE) {
        comida_buffet = 1;
    } else {
        comida_buffet = 0;
    }
}

void worker_gate_insert_queue_buffet(student_t *student) // estudante vai para o buffet
{   

    buffet_t *buffet = globals_get_buffets();
    buffet_queue_insert(buffet, student);
}

void *worker_gate_run(void *arg)
{
    int all_students_entered;
    int number_students;   

    number_students = *((int *)arg);
    all_students_entered = number_students > 0 ? FALSE : TRUE;

    while (all_students_entered == FALSE)
    {
        worker_gate_look_buffet();
        worker_gate_look_queue();
        if (comida_buffet == 1 && fila_cheia == 0) 
            worker_gate_remove_student();
    }

    pthread_exit(NULL);

}

void worker_gate_init(worker_gate_t *self)
{   

    int number_students = globals_get_students();
    pthread_create(&self->thread, NULL, worker_gate_run, &number_students);
}

void worker_gate_finalize(worker_gate_t *self)
{   
    pthread_join(self->thread, NULL);
    free(self);
}