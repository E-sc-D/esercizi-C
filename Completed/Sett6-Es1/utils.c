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

int LevenshteinStringDistance(const char* string1, const char* string2)
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

int SimpleStringSimilarity(const char* string1, const char* string2)
{
    int length1 = strlen(string1);
    int length2 = strlen(string2);

    int similarity = 0;
    if(length1 >= length2)
    {
        for(int i = 0; i < length2; i++)
            if(string1[i] == string2[i])
                similarity++;
            else
                break;
    }
    else
    {
        for(int i = 0; i < length1; i++)
            if(string1[i] == string2[i])
                similarity++;
            else
                break;
    }
    return similarity;
}