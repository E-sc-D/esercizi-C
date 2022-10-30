#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct coolerIntArray //Array di int che tiene conto della propria lunghezza
{
    int size;
    int* array;
};

void printArray(int array[], size_t size)
{
    int i = 0;
    for (i = 0; i < size; i++)
    {
        printf("[%d]", array[i]);
    }
    printf("\n");
}

struct coolerIntArray intersezione(const int array1[], const int array2[]) // intersezione senza ripetizioni
{
    int i = 0, j = 0;

    int contaIntersezioni[5];    // Array che terrà conto di quante volte un elemento compare anche nell'altro array (intersezione)
    for (i = 0; i < 5; i++)
    {
        contaIntersezioni[i] = 0;    // Inizializzazione degli elementi dell'array
        for (j = 0; j < 10; j++)
        {
            if (array1[i] == array2[j])
            {
                contaIntersezioni[i]++;  // Conta l'intersezione (sarà la lunghezza dell'array intersezione)
            }
        }
    }

    int cont = 0;
    int flag = 0;
    // Scorro l'array di contaIntersezioni e conto il numero di elementi che fanno intersezione,
    // per poter creare l'array finale che contiene solo elementi di intersezione senza ripetizioni
    for (i = 0; i < 5; i++)
    {
        if (contaIntersezioni[i] >= 1)
        {
            flag = 0;
            for (j = i - 1; j >= 0; j--)
            {
                if (array1[i] == array1[j])
                {
                    flag = 1;
                }
            }
            if (flag == 0)
            {
                cont++;
            }
        }
    }

    int* arrayIntersezione = (int*)malloc(cont * sizeof(int)); //int arrayIntersezione[cont];

    int k = 0;
    for (i = 0; i < 5; i++)
    {
        if (contaIntersezioni[i] >= 1)
        {
            flag = 0;
            for (j = i - 1; j >= 0; j--)
            {
                if (array1[i] == array1[j])
                {
                    flag = 1;
                }
            }
            if (flag == 0)
            {
                arrayIntersezione[k] = array1[i];
                k++;
            }

        }
    }

    struct coolerIntArray coolerArrayIntersezione;
    coolerArrayIntersezione.size = cont;
    coolerArrayIntersezione.array = arrayIntersezione;

    return coolerArrayIntersezione;
}


int main()
{
    srand(time(NULL));
    int rnd = 0;    // Inizializzo la variabile che conterrà il numero random

    int array1[5];
    int array2[10];

    int i = 0, j = 0;

    printf("Inserisci cinque valori interi da tastiera\n");
    for (i = 0; i < 5; i++)
    {
        scanf("%d", &array1[i]);
    }
    printf("Array1: ");
    printArray(array1, sizeof(array1)/sizeof(array1[0]));   // Stampo gli elementi del primo array calcolandone il numero di elementi

    // Genero gli elementi del secondo array in maniera pseudo-casuale
    for (i = 0; i < 10; i++)
    {
        rnd = rand() % 10; // Numero random compreso tra 0 e 9
        array2[i] = rnd;
    }
    printf("Array2: ");
    printArray(array2, sizeof(array2)/sizeof(array2[0])); // Stampo gli elementi del secondo array

    struct coolerIntArray arrayIntersezione = intersezione(array1, array2); //, &size, &p);

    printf("\nArray intersezione: ");
    printArray(arrayIntersezione.array, arrayIntersezione.size);

    free(arrayIntersezione.array); // arrayIntersezione è stato creato originariamente con malloc, quindi la memoria deve essere liberata manualmente
    // Tuttavia il programma termina successivamente, quindi è facoltativo in questo caso, ma rimane una buona pratica.
    return 0;
}



