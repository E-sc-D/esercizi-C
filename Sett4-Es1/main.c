#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

// size_t n è il numero di elementi dell'array
void printArray(int array[], size_t n) {
    int i = 0;
    for (i = 0; i < n; i++) {
        printf("[%d]", array[i]);
    }
}

void intersezione(int array1[], int array2[], int* size, int* array) {
    assert(size);
    assert(array);
    int i = 0, j = 0;
    // intersezione senza ripetizioni
    int contaIntersezioni[5];    // array che terrà conto di quante volte un elemento compare anche nell'altro array (intersezione)
    for (i = 0; i < 5; i++) {
        contaIntersezioni[i] = 0;    // per poter lavorare sugli elementi dell'array li inizializzo a 0
        for (j = 0; j < 10; j++) {
            if (array1[i] == array2[j])
                contaIntersezioni[i]++;  // conto l'intersezione
        }
    }

    // print di array contaIntersezioni
    printf("\nArray contaIntersezioni: ");
    printArray(contaIntersezioni, sizeof(contaIntersezioni) / sizeof(contaIntersezioni[0]));

    int cont = 0;
    int flag = 0;
    // Scorro l'array di contaIntersezioni e conto il numero di elementi che fanno intersezione, per poter creare l'array finale che contiene solo elementi di intersezione senza ripetizioni
    for (i = 0; i < 5; i++) {
        if (contaIntersezioni[i] >= 1) {
            flag = 0;
            for (j = i - 1; j >= 0; j--){
                if (array1[i] == array1[j]) {
                    flag = 1;
                }
            }
            if (flag == 0)
                cont++;
        }
    }
    printf("\nL'array di intersezione avra %d elementi", cont);

    static int* arrayIntersezione;
    arrayIntersezione = (int*) malloc(cont * sizeof(int));

    //int arrayIntersezione[cont];
    int k = 0;
    for (i = 0; i < 5; i++) {
        if (contaIntersezioni[i] >= 1) {
            flag = 0;
            for (j = i - 1; j >= 0; j--){
                if (array1[i] == array1[j]) {
                    flag = 1;
                }
            }
            if (flag == 0) {
                arrayIntersezione[k] = array1[i];
                k++;
            }

        }
    }
    printf("\nArray intersezione: ");
    printArray(arrayIntersezione, cont);

    // Questi sono i valori di return (perche per lavorare sugli array devo anche sapere quanti elementi hanno per non sforare
    *size = cont;
    *array = &arrayIntersezione;

    printf("\nIndirizzo memoria di arrayintersezione %d", &arrayIntersezione);
}


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
    printArray(array1, sizeof(array1)/sizeof(array1[0]));   // Stampo gli elementi del primo array  sizeof(.. calcola il numero di elementi dell'array


    printf("\nArray2: ");
    // Stampo e genero gli elementi del secondo array in maniera pseudo-casuale
    for (i = 0; i < 10; i++) {
        rnd = rand() % 10; // numero random compreso tra 0 e 99
        //printf("%d", rnd);
        array2[i] = rnd;
        printf("[%d]", array2[i]);
    }

    int size;
    int** p;
    intersezione(array1, array2, &size, &p);

    printf("\nSize %d", size);
    printf("\nPuntatore  %d", *p[0]);
    //printArray(&p, size);



    /*// intersezione senza ripetizioni
    int contaIntersezioni[5];    // array che terrà conto di quante volte un elemento compare anche nell'altro array (intersezione)
    for (i = 0; i < 5; i++) {
        contaIntersezioni[i] = 0;    // per poter lavorare sugli elementi dell'array li inizializzo a 0
        for (j = 0; j < 10; j++) {
            if (array1[i] == array2[j])
                contaIntersezioni[i]++;  // conto l'intersezione
        }
    }
    // print di array contaIntersezioni
    printf("\nArray contaIntersezioni: ");
    printArray(contaIntersezioni, sizeof(contaIntersezioni) / sizeof(contaIntersezioni[0]));


    int cont = 0;
    int flag = 0;
    // Scorro l'array di contaIntersezioni e conto il numero di elementi che fanno intersezione, per poter creare l'array finale che contiene solo elementi di intersezione senza ripetizioni
    for (i = 0; i < 5; i++) {
        if (contaIntersezioni[i] >= 1) {
            flag = 0;
            for (j = i - 1; j >= 0; j--){
                if (array1[i] == array1[j]) {
                    flag = 1;
                }
            }
            if (flag == 0)
                cont++;
        }
    }
    printf("\nL'array di intersezione avra %d elementi", cont);

    int arrayIntersezione[cont];
    int k = 0;
    for (i = 0; i < 5; i++) {
        if (contaIntersezioni[i] >= 1) {
            flag = 0;
            for (j = i - 1; j >= 0; j--){
                if (array1[i] == array1[j]) {
                    flag = 1;
                }
            }
            if (flag == 0) {
                arrayIntersezione[k] = array1[i];
                k++;
            }

        }
    }

    printf("\nArray intersezione: ");
    printArray(arrayIntersezione, sizeof(arrayIntersezione)/sizeof(arrayIntersezione[0]));
*/
    return 0;
}



