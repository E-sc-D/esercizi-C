#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef enum bool
{
    false = 0,
    true = 1
} bool;

int FindMinimumInArray(const int numbersCount, const int numbers[numbersCount])
{
    int minimumNumber = numbers[0];

    int i;
    for(i = 1; i < numbersCount; i++)
        if(numbers[i] < minimumNumber)
            minimumNumber = numbers[i];

    return minimumNumber;
}

int FindMaximumInArray(const int numbersCount, const int numbers[numbersCount])
{
    int maximumNumber = numbers[0];

    int i;
    for(i = 1; i < numbersCount; i++)
        if(numbers[i] > maximumNumber)
            maximumNumber = numbers[i];

    return maximumNumber;
}

int FindMinimum(const int numbersCount, ... )
{
    va_list valist;
    va_start(valist, numbersCount);
    
    int minimumNumber = va_arg(valist, int);

    int i;
    for(i = 1; i < numbersCount; i++)
    {
        int currentNumber = va_arg(valist, int);
        if(currentNumber < minimumNumber)
            minimumNumber = currentNumber;
    }

    va_end(valist);

    return minimumNumber;
}

int FindMaximum(const int numbersCount, ... )
{
    va_list valist;
    va_start(valist, numbersCount);
    
    int maximumNumber = va_arg(valist, int);
    
    int i;
    for(i = 1; i < numbersCount; i++)
    {
        int currentNumber = va_arg(valist, int);
        if(currentNumber > maximumNumber)
            maximumNumber = currentNumber;
    }

    va_end(valist);

    return maximumNumber;
}

int LevenshteinDistance(const char* string1, const char* string2)
{
    int length1 = strlen(string1);
    int length2 = strlen(string2);

    int levenshteinMatrix[length1 + 1][length2 + 1];

    for(int i = 0; i <= length1; i++)
        for(int j = 0; j <= length2; j++)
            levenshteinMatrix[i][j] = 0;
    
    for(int i = 0; i <= length1; i++)
        levenshteinMatrix[i][0] = i;

    for(int j = 0; j <= length2; j++)
        levenshteinMatrix[0][j] = j;

    int substitutionCost;
    for(int i = 1; i <= length1; i++)
    {
        for(int j = 1; j <= length2; j++)
        {
            if(string1[i - 1] == string2[j - 1])
                levenshteinMatrix[i][j] = levenshteinMatrix[i - 1][j - 1];
            else
                levenshteinMatrix[i][j] = FindMinimum(3, levenshteinMatrix[i - 1][j] + 1, levenshteinMatrix[i][j - 1] + 1, levenshteinMatrix[i - 1][j - 1] + 1);
        }
    }

    return levenshteinMatrix[length1][length2];
}

struct consoleBuffer
{
    int count;
    char buffer[100];
};

int ReadString(char **pointer)//legge una stringa è la salva nel puntatore che punta pointer
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);//serve a pulire il buffer;

    struct consoleBuffer console;
    console.count = 0;
    do
    {
        console.buffer[console.count] = getchar();
        console.count++;
    }
    while(console.buffer[console.count - 1] != '\n'); //vengono salvati dentro un buffer di 100 elementi i char inseriti
    console.buffer[console.count - 1] = '\0';//l'ultimo elemento sarà il terminatore
    (*pointer) = (char*)malloc((sizeof(char) * console.count));//viene inizializzata la matrice in base al numero di elementi inseriti

    for(int j = 0;j < console.count ; j++)
    {
        (*pointer)[j] = console.buffer[j];//viene riempita
    }
    return console.count ; //viene restituito il numero di char dentro il vettore
}

struct Array
{
    char* array;
    int n;//dimensione array
} emptyArray = { NULL , 0 };

int StringLen(char *string)
{
    int i;
    for(i = 0; string[i]!='\0';i++);

    return i + 1; //in questo modo il risultato conta anche il carattere terminatore: "ciao\0" sarà lunga 5
    
}