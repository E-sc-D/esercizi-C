#include <stdlib.h>
#include <string.h>
#include "utils.c"

#define CONTATTO_FIELDS_COUNT 3 // Nome, Cognome, NumeroTelefonico
#define RUBRICA_MAX_LENGTH 1000
#define FIELD_MAX_LENGTH 50

struct Rubrica
{
    char Contatti[RUBRICA_MAX_LENGTH][CONTATTO_FIELDS_COUNT][FIELD_MAX_LENGTH];
};

void InitializeRubrica(struct Rubrica *rubrica)
{
    for(int i = 0; i < RUBRICA_MAX_LENGTH; i++)
        for(int j = 0; j < CONTATTO_FIELDS_COUNT; j++)
            rubrica->Contatti[i][j][0] = '\0';
}

bool ContattoCompare(char contatto1[CONTATTO_FIELDS_COUNT][FIELD_MAX_LENGTH], char contatto2[CONTATTO_FIELDS_COUNT][FIELD_MAX_LENGTH])
{
    int strcmpSum = 0;

    for(int i = 0; i < CONTATTO_FIELDS_COUNT; i++)
        strcmpSum += strcmp(contatto1[i], contatto2[i]);

    if(strcmpSum == 0)
        return true;
    else
        return false;
}

bool IsContattoEmpty(char contatto[CONTATTO_FIELDS_COUNT][FIELD_MAX_LENGTH])
{
    int strlenSum = 0;

    for(int i = 0; i < CONTATTO_FIELDS_COUNT; i++)
        strlenSum += strlen(contatto[i]);

    if(strlenSum == 0)
        return true;
    else
        return false;
}

int FindEmptyIndex(struct Rubrica *rubrica) // Returns the index of the first empty place in Rubrica, if none returns -1
{
    for(int i = 0; i < RUBRICA_MAX_LENGTH; i++)
        if(IsContattoEmpty(rubrica->Contatti[i]))
            return i;
    return -1;
}

int FindContatto(struct Rubrica *rubrica, char contatto[CONTATTO_FIELDS_COUNT][FIELD_MAX_LENGTH]) // Returns the index of the first occurrence of Contatto in Rubrica, if none return -1
{
    for(int i = 0; i < RUBRICA_MAX_LENGTH; i++)
        if(ContattoCompare(rubrica->Contatti[i], contatto))
            return i;
    return -1;
}

int SearchContatto(struct Rubrica *rubrica, char searchKeyword[], bool exactMatch) // Returns the index of the first occurrence of searched Contatto in Rubrica, if none return -1
{
    if(exactMatch)
    {
        for(int i = 0; i < RUBRICA_MAX_LENGTH; i++)
            for(int j = 0; j < CONTATTO_FIELDS_COUNT; j++)
                if(strcmp(rubrica->Contatti[i][j], searchKeyword) == 0)
                    return i;
        return -1;
    }
    else
    {
        int minimumValue = LevenshteinDistance(rubrica->Contatti[0][0], searchKeyword);
        int minimumIndex = 0;
        for(int i = 1; i < RUBRICA_MAX_LENGTH; i++)
        {
            int tempValue = LevenshteinDistance(rubrica->Contatti[i][0], searchKeyword);
            if(tempValue < minimumValue)
            {
                minimumValue = tempValue;
                minimumIndex = i;
            }
        }

        return minimumIndex;
    }
}

int GetRubricaLength(struct Rubrica *rubrica)
{
    int length = 0;

    for(int i = 0; i < RUBRICA_MAX_LENGTH; i++)
        if(!IsContattoEmpty(rubrica->Contatti[i]))
            length++;
    
    return length;
}

bool IsRubricaFull(struct Rubrica *rubrica)
{
    if(FindEmptyIndex(rubrica) == -1)
        return true;
    else
        return false;
}

bool IsRubricaEmpty(struct Rubrica *rubrica)
{
    if(GetRubricaLength(rubrica) == 0)
        return true;
    else
        return false;
}

bool AddContatto(struct Rubrica *rubrica, char contatto[CONTATTO_FIELDS_COUNT][FIELD_MAX_LENGTH])
{
    int emptyIndex = FindEmptyIndex(rubrica);
    if(emptyIndex != -1)
    {
        for(int i = 0; i < CONTATTO_FIELDS_COUNT; i++)
            strcpy(rubrica->Contatti[emptyIndex][i], contatto[i]);
        return true;
    }
    else
    {
        return false;
    }
}

bool RemoveContatto(struct Rubrica *rubrica, char contatto[CONTATTO_FIELDS_COUNT][FIELD_MAX_LENGTH])
{
    int contattoIndex = FindContatto(rubrica, contatto);
    if(contattoIndex != -1)
    {
        for(int i = 0; i < CONTATTO_FIELDS_COUNT; i++)
            rubrica->Contatti[contattoIndex][i][0] = '\0';
        return true;
    }
    else
    {
        return false;
    }
}

char* ContattoToString(char contatto[CONTATTO_FIELDS_COUNT][FIELD_MAX_LENGTH])
{
    if(!IsContattoEmpty(contatto))
    {
        int strlenSum = 0;
        for(int i = 0; i < CONTATTO_FIELDS_COUNT; i++)
            strlenSum += strlen(contatto[i]);

        char* contattoString = (char*)malloc((strlenSum + 2 + 1) * sizeof(char));
        char* ptr = contattoString;
        //Lengths of all Contatto fields plus 2 (\n at the end of each stringified field except the last one) plus 1 (\0, the string terminator)
        for(int i = 0; i < CONTATTO_FIELDS_COUNT; i++)
            ptr += sprintf(ptr, "%s\n", contatto[i]);
        return contattoString;
    }
    else
    {
        return "Il contatto e' vuoto!";
    }
}

char* RubricaToString(struct Rubrica *rubrica)
{
    if(!IsRubricaEmpty(rubrica))
    {
        int rubricaLength = GetRubricaLength(rubrica);

        //Precalculate sum of all ContattoToString lengths
        int lengthsSum = 0;
        for(int i = 0; i < rubricaLength; i++)
            lengthsSum += strlen(ContattoToString(rubrica->Contatti[i]));

        char *rubricaString = (char*)malloc((lengthsSum + (2 * rubricaLength) + 1) * sizeof(char));
        //lengthsSum, the sum of all the string lengths of the ContattoToString that will be called,
        //plus 2 (the \n in front of and after the ContattoToString string)
        //plus 1 (the \0 at the end of the whole rubricaString)

        char *ptr = rubricaString;
        for(int i = 0; i < rubricaLength; i++)
            ptr += sprintf(ptr, "\n%s\n", ContattoToString(rubrica->Contatti[i]));

        return rubricaString;
    }
    else
    {
        return "La rubrica e' vuota!\n";
    }
}