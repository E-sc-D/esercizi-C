#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    srand(time(NULL));
    int rnd = 0;    // inizializzo la variabile che conterrà il numero random

    int array1[5];
    int array2[10];
    int i = 0;

    printf("Inserisci cinque valori interi da tastiera\n");
    for (i = 0; i < 5; i++) {
        scanf("%d", &array1[i]);
    }
    printf("Array1: ");
    // Stampo gli elementi del primo array
    for (i = 0; i < 5; i++) {
        printf("[%d]", array1[i]);
    }

    printf("\nArray 2: ");
    // Stampo e genero gli elementi del secondo array in maniera pseudo-casuale
    for (i = 0; i < 10; i++) {
        rnd = rand() % 100; // numero random compreso tra 0 e 99
        array2[i] = rnd;
        printf("[%d]", array2[i]);
    }

    // intersezione senza ripetizioni
    //int arrayIntersezione[5];   // il numero di elementi è 5 perché facendo l'intersezione senza ripetizioni il numero massimo di possibili elementi in comune sarà sempre uguale alla lunghezza dell'array più piccolo (con meno elementi)

    int verifica[5];
    int k = 0;
    for (i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            if (array1[i] == array2[j]) {
                verifica[i]++;
                break;
            }
        }
    }
    // print di array verifica
    for (i = 0; i < 5; i++) {
        printf("[%d]", verifica[i]);
    }


    int cont = 0;
    for (int i = 0; i < 5; i++) {
        if (verifica[i] >= 1) {
            cont++;
        }
    }
    int arrayIntersezione[cont];



    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < cont; j++){
            if (verifica[i] >= 1) {
                arrayIntersezione[j] = array1[i];
            }
        }
    }

    printf("\nArray intersezione: ");
    for (int i = 0; i < 5; i++) {
        printf("[%d]", arrayIntersezione[i]);
    }

    return 0;
}


void intersezione(int array1[], int array2[]) {

}