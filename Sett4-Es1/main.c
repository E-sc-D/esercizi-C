#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct coolerIntArray //Array di int che tiene conto della propria lunghezza
{
    int size;
    int* array;
};

void printCoolerIntArray(const struct coolerIntArray arrayToPrint)
{
    int i = 0;
    for (i = 0; i < arrayToPrint.size; i++)
    {
        printf("[%d]", arrayToPrint.array[i]);
    }
    printf("\n");
}

void printIntArray(const int arrayToPrint[], const size_t size)
{
    int i = 0;
    for (i = 0; i < size; i++)
    {
        printf("[%d]", arrayToPrint[i]);
    }
    printf("\n");
}

struct coolerIntArray intersezioneSenzaRipetizioni(const struct coolerIntArray array1, const struct coolerIntArray array2)
{
    struct coolerIntArray arrayMaggiore;
    struct coolerIntArray arrayMinore;

    // Determinare quale array ha la lunghezza minore e quale la lunghezza maggiore
    if(array1.size > array2.size) // I puntatori arrayMaggiore e arrayMinore, punteranno rispettivamente array1 e array2
    {
        arrayMaggiore = array1;
        arrayMinore = array2;
    }
    else // I puntatori punteranno il contrario di quanto accade sopra
    {
        arrayMaggiore = array2;
        arrayMinore = array1;
    }

    int i = 0, j = 0;

    int contaIntersezioni[arrayMinore.size];    // Array che terrà conto di quante volte un elemento compare anche nell'altro array (intersezione)
    for (i = 0; i < arrayMinore.size; i++)
    {
        contaIntersezioni[i] = 0;    // Inizializzazione degli elementi dell'array
        for (j = 0; j < arrayMaggiore.size; j++)
        {
            if (arrayMinore.array[i] == arrayMaggiore.array[j])
            {
                contaIntersezioni[i]++;  // Conta l'intersezione (sarà la lunghezza dell'array intersezione)
            }
        }
    }

    int cont = 0;
    int flag = 0;
    // Scorro l'array di contaIntersezioni e conto il numero di elementi che fanno intersezione,
    // per poter creare l'array finale che contiene solo elementi di intersezione senza ripetizioni
    for (i = 0; i < arrayMinore.size; i++)
    {
        if (contaIntersezioni[i] >= 1)
        {
            flag = 0;
            for (j = i - 1; j >= 0; j--)
            {
                if (arrayMinore.array[i] == arrayMinore.array[j])
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
    for (i = 0; i < arrayMinore.size; i++)
    {
        if (contaIntersezioni[i] >= 1)
        {
            flag = 0;
            for (j = i - 1; j >= 0; j--)
            {
                if (arrayMinore.array[i] == arrayMinore.array[j])
                {
                    flag = 1;
                }
            }
            if (flag == 0)
            {
                arrayIntersezione[k] = arrayMinore.array[i];
                k++;
            }

        }
    }

    struct coolerIntArray coolerArrayIntersezione;
    coolerArrayIntersezione.size = cont;
    coolerArrayIntersezione.array = arrayIntersezione;
    return coolerArrayIntersezione;
}

struct coolerIntArray intersezioneConRipetizioni(const struct coolerIntArray array1, const struct coolerIntArray array2)
{
    int i = 0, j = 0;

    int cont = 0;
    for(i = 0; i < array1.size; i++)
    {
        for(j = 0; j < array2.size; j++)
        {
            if(array1.array[i] == array2.array[j])
            {
                cont++;
            }
        }
    }

    int* arrayIntersezione = (int*)malloc(cont * sizeof(int)); //int arrayIntersezione[cont];ù
    
    int k = 0;
    for(i = 0; i < array1.size; i++)
    {
        for(j = 0; j < array2.size; j++)
        {
            if(array1.array[i] == array2.array[j])
            {
                arrayIntersezione[k] = array1.array[i];
                k++;
            }
        }
    }

    struct coolerIntArray coolerArrayIntersezione;
    coolerArrayIntersezione.size = cont;
    coolerArrayIntersezione.array = arrayIntersezione;
    return coolerArrayIntersezione;
}

struct coolerIntArray unione(const struct coolerIntArray array1, const struct coolerIntArray array2)
{
    int unioneSize = array1.size + array2.size;
    int* arrayUnione = (int*)malloc(unioneSize * sizeof(int)); //int arrayUnione[cont];

    int i = 0, k = 0;
    for(i = 0; i < array1.size; i++)
    {
        arrayUnione[k] = array1.array[i];
        k++;
    }
    for(i = 0; i < array2.size; i++)
    {
        arrayUnione[k] = array2.array[i];
        k++;
    }

    struct coolerIntArray coolerArrayUnione;
    coolerArrayUnione.size = unioneSize;
    coolerArrayUnione.array = arrayUnione;
    return coolerArrayUnione;
}

int main()
{
    srand(time(NULL));
    int rnd = 0;    // Inizializzo la variabile che conterrà il numero random

    const int array1_length = 5;
    int array1[array1_length];
    const int array2_length = 10;
    int array2[array2_length];

    struct coolerIntArray coolerArray1;
    coolerArray1.size = array1_length;
    coolerArray1.array = array1;

    struct coolerIntArray coolerArray2;
    coolerArray2.size = array2_length;
    coolerArray2.array = array2;

    int i = 0, j = 0;
    printf("Inserisci dei valori interi da tastiera\n");
    for (i = 0; i < coolerArray1.size; i++)
    {
        scanf("%d", &coolerArray1.array[i]);
    }
    printf("Array1: ");
    printCoolerIntArray(coolerArray1);   // Stampo gli elementi del primo array calcolandone il numero di elementi

    // Genero gli elementi del secondo array in maniera pseudo-casuale
    for (i = 0; i < coolerArray2.size; i++)
    {
        rnd = rand() % 10; // Numero random compreso tra 0 e 9
        coolerArray2.array[i] = rnd;
    }
    printf("Array2: ");
    printCoolerIntArray(coolerArray2); // Stampo gli elementi del secondo array

    struct coolerIntArray coolerArrayResult;
    
    coolerArrayResult = intersezioneSenzaRipetizioni(coolerArray1, coolerArray2); //, &size, &p);
    printf("Array intersezione senza ripetizioni: ");
    printCoolerIntArray(coolerArrayResult);
    free(coolerArrayResult.array); // coolerArrayResult.array è stato creato originariamente con malloc,
                                   // quindi la memoria deve essere liberata manualmente

    coolerArrayResult = intersezioneConRipetizioni(coolerArray1, coolerArray2);
    printf("Array intersezione con ripetizioni: ");
    printCoolerIntArray(coolerArrayResult);
    free(coolerArrayResult.array);

    coolerArrayResult = unione(coolerArray1, coolerArray2);
    printf("Array unione: ");
    printCoolerIntArray(coolerArrayResult);
    free(coolerArrayResult.array);

    return 0;
}