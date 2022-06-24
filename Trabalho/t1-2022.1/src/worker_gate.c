#include <stdlib.h>
#include <semaphore.h>
#include "worker_gate.h"
#include "globals.h"
#include "config.h"
#include "buffet.h"
#include "queue.h"


pthread_mutex_t catraca;
sem_t carregar;
int buffet_id;
char direcao;
int tem_lugar;
int all_students_entered;
int number_students;
buffet_t *escolhido;

void worker_gate_look_queue() // verifica a fila da catraca
{   
    /* verifica se a fila da catraca está vazia */
    queue_t *queue = globals_get_queue();
    if (queue->_length == 0) {
        all_students_entered = TRUE;
    }

}

void worker_gate_remove_student() // retira um estudante da fila
{
    /* tira o estudante da fila e o passa pela catraca */
    queue_t *queue = globals_get_queue();
    queue_remove(queue);

}

void worker_gate_look_buffet() // verifica se há lugares livres no buffet
{   
    /* verifica onde há um lugar vazio */
    int buffet_cheio = 0;
    buffet_t *buffet = globals_get_buffets();
    for (int i = 0; i < numero_buffets; i++)
    {
        if (buffet[i].queue_left[0] == 0) {
            buffet_id = i;
            direcao = 'L';
            tem_lugar = 1;
            break;
        }
        else if (buffet[i].queue_right[0] == 0) {
            buffet_id = i;
            direcao = 'R';
            tem_lugar = 1;
            break;
        }
        else {
            buffet_cheio += 0;
        }   
    }
    if (buffet_cheio == numero_buffets){
        tem_lugar = 0;
    }
}

void worker_gate_insert_queue_buffet(student_t *student) // estudante vai para o buffet
{   
    buffet_t *buffet = globals_get_buffets();
    queue_t *queue = globals_get_queue();
    /* espera o worker gate abrir o ru para os estudantes */
    sem_wait(&carregar);
    /* se for o primeiro estudante da fila, avança a catraca */
    while(student->_buffet_position != 0) {
        if (student == queue-> _first->_student) {
            pthread_mutex_lock(&catraca);
            printf("\nEstudante %i passou pela catraca", student->_id);
            worker_gate_look_buffet();
            student->left_or_right = direcao;
            student->_id_buffet = buffet_id;
            escolhido = &buffet[buffet_id];
            buffet_queue_insert(escolhido, student);
            printf("\nEstudante %i entrou na fila", student->_id);
            pthread_mutex_unlock(&catraca);
            worker_gate_remove_student();
        }
    }
}

void *worker_gate_run(void *arg)
{  
    pthread_mutex_init(&catraca, 0);
    sem_init(&carregar, 0, 0);
    queue_t *queue = globals_get_queue();
    number_students = globals_get_students();

    number_students = *((int *)arg);
    all_students_entered = number_students > 0 ? FALSE : TRUE;

    while(queue-> _length < number_students) {
        // espera a fila estar cheia, evita alguns erros com os ponteiros nulos
    }
    for (int i = 0; i < number_students; i++) {
        sem_post(&carregar);
    }
    while (all_students_entered == FALSE) {   
        worker_gate_look_queue();
    }
    sem_destroy(&carregar);
    pthread_mutex_destroy(&catraca);
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