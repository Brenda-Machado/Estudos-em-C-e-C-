#include <stdlib.h>
#include <semaphore.h>
#include "worker_gate.h"
#include "globals.h"
#include "config.h"
#include "buffet.h"
#include "queue.h"

int comida_buffet = 1;
int fila_cheia = 0;
pthread_mutex_t fila_buffet;
buffet_t *buffet_id = NULL;
char direcao;
int tem_lugar = 0;
student_t *student_1 = NULL;
sem_t catraca_fila;

void worker_gate_look_queue() // verifica se as filas estão cheias
{   
    buffet_t *buffet = globals_get_buffets();
    for (int i = 0; i < numero_buffets; i++)
    {
        if (buffet[i].queue_left[0] == 0) {
            buffet_id = &buffet[i];
            direcao = 'L';
            tem_lugar = 1;
            sem_post(&catraca_fila);
            break;
        }
        else if (buffet[i].queue_right[0] == 0) {
            buffet_id = &buffet[i];
            direcao = 'R';
            tem_lugar = 1;
            sem_post(&catraca_fila);
            break;
        }
    }
    tem_lugar = 0;
}

void worker_gate_remove_student() // retira um estudante da fila
{
    queue_t *queue = globals_get_queue();
    student_1 = queue_remove(queue);
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
    worker_gate_look_queue();
    if (tem_lugar == 1) {
        worker_gate_remove_student();
        if (student_1 != NULL) { 
            if (comida_buffet == 1 && student-> _id == student_1->_id) {
                pthread_mutex_lock(&fila_buffet);
                student->left_or_right = direcao;
                if (buffet_queue_insert(buffet_id, student) && student->_buffet_position!=-1) {
                    pthread_mutex_unlock(&fila_buffet);
                }
            }
        }
        }
}


void *worker_gate_run(void *arg)
{
    int all_students_entered;
    int number_students;
    pthread_mutex_init(&fila_buffet, 0);
    sem_init(&catraca_fila, 0, 0);

    number_students = *((int *)arg);
    all_students_entered = number_students > 0 ? FALSE : TRUE;
    while (all_students_entered == FALSE)
    {
        worker_gate_look_buffet();
        worker_gate_look_queue();

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