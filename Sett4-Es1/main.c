#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    srand(time(NULL));
    int rnd;    // inizializzo la variabile che conterrà il numero random

    int array1[5];
    int array2[10];

    printf("Inserisci cinque valori interi da tastiera\n");
    for (int i = 0; i < 5; i++) {
        scanf("%d", &array1[i]);
    }

    printf("Array1:");
    for (int i = 0; i < 5; i++) {
        printf("[%d]", array1[i]);
    }

    for (int i = 0; i < 5; i++) {
        rnd = rand() % 100; // numero random compreso tra 0 e 99
    }

    return 0;
}