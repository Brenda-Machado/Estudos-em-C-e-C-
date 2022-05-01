// praticando o uso de laços

#include <stdio.h>


int main () { 

    int N = 0;
    int num;
    int i;

    printf("Digite 0 ou 1:");

    scanf("%i", &num);

    if (num == 0) {
        while (N < 20) {
            printf("[");
            for (i = N; i < N+2; i++) {
                printf("%i", i);
            }
            printf("]\n");
            N++;
        }
    }
    if (num == 1) {
        while (N > -20) {
            printf("[");
            for (i = N; i > N-2; i--) {
                printf("%i", i);
            }
            printf("]\n");
            N--;
        }
    }

    return 0;
}