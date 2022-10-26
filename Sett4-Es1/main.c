#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    srand(time(NULL));
    int rnd = 0;    // inizializzo la variabile che conterrà il numero random

    int array1[5];
    int array2[10];
    int i = 0, j = 0;

    printf("Inserisci cinque valori interi da tastiera\n");
    for (i = 0; i < 5; i++) {
        scanf("%d", &array1[i]);
    }
    printf("Array1: ");
    // Stampo gli elementi del primo array
    for (i = 0; i < 5; i++) {
        printf("[%d]", array1[i]);
    }

    printf("\nArray2: ");
    // Stampo e genero gli elementi del secondo array in maniera pseudo-casuale
    for (i = 0; i < 10; i++) {
        rnd = rand() % 10; // numero random compreso tra 0 e 99
        //printf("%d", rnd);
        array2[i] = rnd;
        printf("[%d]", array2[i]);
    }

    // intersezione senza ripetizioni
    int verifica[5];    // array che terrà conto di quante volte un elemento compare anche nell'altro array (intersezione)
    for (i = 0; i < 5; i++) {
        verifica[i] = 0;    // per poter lavorare sugli elementi dell'array li inizializzo a 0
        for (j = 0; j < 10; j++) {
            if (array1[i] == array2[j]) {
                verifica[i]++;  // conto l'intersezione
            }
        }
    }
    // print di array verifica
    printf("\nArray verifica: ");
    for (i = 0; i < 5; i++) {
        printf("[%d]", verifica[i]);
    }


    int cont = 0;
    // Scorro l'array di verifica e conto il numero di elementi che fanno intersezione, per poter creare l'array finale che contiene solo elementi di intersezione senza ripetizioni
    for (i = 0; i < 5; i++) {
        if (verifica[i] >= 1) {
            cont++;
        }
    }
    printf("\nCont: %d\nL'array di intersezione avra %d elementi", cont, cont);

    int arrayIntersezione[cont];
    int k = 0;
    for (i = 0; i < 5; i++) {
        if (verifica[i] >= 1) {
            arrayIntersezione[k] = array1[i];
            k++;
        }
    }

    printf("\nArray intersezione: ");
    for (i = 0; i < cont; i++) {
        printf("[%d]", arrayIntersezione[i]);
    }

    return 0;
}


void intersezione(int array1[], int array2[]) {

}