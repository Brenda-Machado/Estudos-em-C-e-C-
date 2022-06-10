#include <stdlib.h>

#include "worker_gate.h"
#include "globals.h"
#include "config.h"
#include "buffet.h"
#include "queue.h"

// Na catraca, apenas um aluno por vez passa, logo um mutex
// Controle de quando os alunos entram, se todas as filas estiverem cheias, eles esperam, logo um semáforo

sem_t entrada_restaurante;
pthread_mutex_t catraca;


void worker_gate_look_queue() // verifica se as filas estão cheias
{
    if (buffet_t -> queue_left == 5 &&  buffet_t -> queue_left == 5) {
        return 1;
    } else {
        return 0;
    }
}

void worker_gate_remove_student() // retira um estudante da fila
{
    queue_t.remove();
}

void worker_gate_look_buffet() // verifica se há comida no buffet
{   
    if (buffet_t -> meal[0] == 0 && buffet_t -> meal[1] == 0 && buffet_t -> meal[2] == 0 && buffet_t -> meal[3] == 0 && buffet_t -> meal[4] == 0) {
            return false;
        }
    return true;
}

void worker_gate_insert_queue_buffet(student_t *student) // estudante vai para o buffet
{
    buffet_t.buffet_queue_insert(buffet_t *self, student_t *student);
}

void *worker_gate_run(void *arg)
{
    int all_students_entered;
    int number_students;

    number_students = *((int *)arg);
    all_students_entered = number_students > 0 ? FALSE : TRUE;

    while (all_students_entered == FALSE)
    {
        if (worker_gate_look_queue() && worker_gate_look_buffet()) { 
                worker_gate_remove_student();
        }
        msleep(5000); /* Pode retirar este sleep quando implementar a solução! */
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