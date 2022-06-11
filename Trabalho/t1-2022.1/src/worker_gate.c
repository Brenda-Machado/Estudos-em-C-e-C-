#include <stdlib.h>
#include <semaphore.h>
#include "worker_gate.h"
#include "globals.h"
#include "config.h"
#include "buffet.h"
#include "queue.h"

pthread_mutex_t fila_buffet;
pthread_mutex_t fila_catraca;
buffet_t *buffet_id = 1;
char direcao = "R";
int tem_lugar = 1;
student_t *student_1 = NULL;
sem_t catraca_fila;


void worker_gate_look_queue() // verifica a fila da catraca
{   
    queue_t *queue = globals_get_queue();
    student_1 = queue->_first->_student;

}

void worker_gate_remove_student() // retira um estudante da fila
{
    queue_t *queue = globals_get_queue();
    queue_remove(queue);
}

void worker_gate_look_buffet() // verifica se há lugares livres no buffet
{   
    buffet_t *buffet = globals_get_buffets();
    for (int i = 0; i < numero_buffets; i++)
    {
        if (buffet[i].queue_left[0] == 0) {
            buffet_id = &buffet[i];
            direcao = 'L';
            tem_lugar = 1;
            break;
        }
        else if (buffet[i].queue_right[0] == 0) {
            buffet_id = &buffet[i];
            direcao = 'R';
            tem_lugar = 1;
            break;
        }
        else {
            tem_lugar = 0;
        }   
    }
}

void worker_gate_insert_queue_buffet(student_t *student) // estudante vai para o buffet
{   while (student-> _buffet_position == -1) {
        //sem_wait(&catraca_fila);
        if (student_1 != NULL) { 
            if (student == student_1) {
                pthread_mutex_lock(&fila_catraca);
                if (tem_lugar == 1) {
                    pthread_mutex_lock(&fila_buffet);
                    worker_gate_remove_student();
                    worker_gate_look_buffet();
                    //sem_post(&catraca_fila);
                    student->left_or_right = direcao;
                    student->_id_buffet = buffet_id -> _id;
                    
                    if (buffet_queue_insert(buffet_id, student) == TRUE) {
                        pthread_mutex_unlock(&fila_buffet);   
                    }
                }
                pthread_mutex_unlock(&fila_catraca);
            }    
        }
    }    
}


void *worker_gate_run(void *arg)
{   
    msleep(500);
    queue_t *queue = globals_get_queue();
    int all_students_entered;
    int number_students = queue->_length;
    pthread_mutex_init(&fila_buffet, 0);
        pthread_mutex_init(&fila_catraca, 0);
    sem_init(&catraca_fila, 0, 0);

    number_students = *((int *)arg);
    all_students_entered = number_students > 0 ? FALSE : TRUE;
    
    while (all_students_entered == FALSE) {   
        if (queue->_first->_student != NULL) {
            worker_gate_look_queue();
            number_students = queue->_length;
        }
    }
    
    pthread_mutex_destroy(&fila_buffet);
    sem_destroy(&catraca_fila);
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