#include <stdlib.h>
#include <string.h>
#include "utils.c"

#define NOME_MAX_LENGTH 40
#define COGNOME_MAX_LENGTH 40
#define NUMERO_TELEFONICO_MAX_LENGTH 10

#define RUBRICA_MAX_LENGTH 1000

struct Contatto
{
    char Nome[NOME_MAX_LENGTH + 1]; //plus 1 is for the terminator character
    char Cognome[COGNOME_MAX_LENGTH + 1];
    char NumeroTelefonico[NUMERO_TELEFONICO_MAX_LENGTH + 1];   
} EmptyContatto = { {'\0'}, {'\0'}, {'\0'} };

struct Contatto NewContatto(char nome[], char cognome[], char numeroTelefonico[])
{
    struct Contatto contatto;
    strcpy(contatto.Nome, nome);
    strcpy(contatto.Cognome, cognome);
    strcpy(contatto.NumeroTelefonico, numeroTelefonico);
    return contatto;
}

struct Rubrica
{
    struct Contatto Contatti[RUBRICA_MAX_LENGTH];
};

struct Rubrica NewRubrica() // Constructor-like method to have a Rubrica with every Contatto = EmptyContatto
{
    struct Rubrica initializedRubrica;

    for(int i = 0; i < RUBRICA_MAX_LENGTH; i++)
        initializedRubrica.Contatti[i] = EmptyContatto; // Apparently not needed as the char arrays in Contatto seem to already
                                                        // have the null character, don't know why, how or what is happening

    return initializedRubrica;
}

bool ContattoCompare(const struct Contatto contatto1, const struct Contatto contatto2)
{
    if(strcmp(contatto1.Nome, contatto2.Nome) == 0
    && strcmp(contatto1.Cognome, contatto2.Cognome) == 0
    && strcmp(contatto1.NumeroTelefonico, contatto2.NumeroTelefonico) == 0)
        return true;
    else
        return false;
}

bool IsContattoEmpty(const struct Contatto contatto)
{
    if(ContattoCompare(contatto, EmptyContatto))
        return true;
    else
        return false;
}

int FindEmptyIndex(const struct Rubrica *rubrica) // Returns the index of the first empty place in Rubrica, if none returns -1
{
    for(int i = 0; i < RUBRICA_MAX_LENGTH; i++)
        if(IsContattoEmpty(rubrica->Contatti[i]))
            return i;
    return -1;
}

int FindContatto(const struct Rubrica *rubrica, const struct Contatto contatto) // Returns the index of the first occurrence of Contatto in Rubrica, if none return -1
{
    for(int i = 0; i < RUBRICA_MAX_LENGTH; i++)
        if(ContattoCompare(rubrica->Contatti[i], contatto))
            return i;
    return -1;
}

int SearchContatto(const struct Rubrica *rubrica, const char searchKeyword[], const bool exactMatch) // Returns the index of the first occurrence of searched Contatto in Rubrica, if none return -1
{
    if(exactMatch)
    {
        for(int i = 0; i < RUBRICA_MAX_LENGTH; i++)
            if(strcmp(rubrica->Contatti[i].Nome, searchKeyword) == 0)
                return i;
            else if(strcmp(rubrica->Contatti[i].Cognome, searchKeyword) == 0)
                return i;
            else if(strcmp(rubrica->Contatti[i].NumeroTelefonico, searchKeyword) == 0)
                return i;
        
        return -1;
    }
    else
    {
        int deltaNome = LevenshteinDistance(rubrica->Contatti[0].Nome, searchKeyword);
        int deltaCognome = LevenshteinDistance(rubrica->Contatti[0].Cognome, searchKeyword);
        int deltaNumeroTelefonico = LevenshteinDistance(rubrica->Contatti[0].NumeroTelefonico, searchKeyword);
        int minimumValue = FindMinimum(3, deltaNome, deltaCognome, deltaNumeroTelefonico);
        int minimumIndex = 0;
        for(int i = 1; i < RUBRICA_MAX_LENGTH; i++)
        {
            deltaNome = LevenshteinDistance(rubrica->Contatti[i].Nome, searchKeyword);
            deltaCognome = LevenshteinDistance(rubrica->Contatti[i].Cognome, searchKeyword);
            deltaNumeroTelefonico = LevenshteinDistance(rubrica->Contatti[i].NumeroTelefonico, searchKeyword);
            int tempMinimum = FindMinimum(3, deltaNome, deltaCognome, deltaNumeroTelefonico);

            if(tempMinimum < minimumValue)
            {
                minimumValue = tempMinimum;
                minimumIndex = i;
            }
        }

        return minimumIndex;
    }
}

int GetRubricaLength(const struct Rubrica *rubrica)
{
    int length = 0;

    for(int i = 0; i < RUBRICA_MAX_LENGTH; i++)
        if(!IsContattoEmpty(rubrica->Contatti[i]))
            length++;
    
    return length;
}

bool IsRubricaFull(const struct Rubrica *rubrica)
{
    if(FindEmptyIndex(rubrica) == -1)
        return true;
    else
        return false;
}

bool IsRubricaEmpty(const struct Rubrica *rubrica)
{
    if(GetRubricaLength(rubrica) == 0)
        return true;
    else
        return false;
}

bool AddContatto(struct Rubrica *rubrica, const struct Contatto contatto)
{
    int emptyIndex = FindEmptyIndex(rubrica);
    if(emptyIndex != -1)
    {
        rubrica->Contatti[emptyIndex] = contatto;
        return true;
    }
    else
    {
        return false;
    }
}

bool RemoveContatto(struct Rubrica *rubrica, const struct Contatto contatto)
{
    int contattoIndex = FindContatto(rubrica, contatto);
    if(contattoIndex != -1)
    {
        rubrica->Contatti[contattoIndex] = EmptyContatto;
        return true;
    }
    else
    {
        return false;
    }
}

char* ContattoToString(struct Contatto contatto)
{
    if(!IsContattoEmpty(contatto))
    {
        char* contattoString = (char*)malloc((strlen(contatto.Nome) + strlen(contatto.Cognome) + strlen(contatto.NumeroTelefonico) + 2 + 1) * sizeof(char));
        //Lengths of all Contatto fields plus 2 (\n at the end of each stringified field except the last one) plus 1 (\0, the string terminator)
        sprintf(contattoString, "%s\n%s\n%s", contatto.Nome, contatto.Cognome, contatto.NumeroTelefonico);
        return contattoString;
    }
    else
    {
        return "Il contatto e' vuoto!";
    }
}

char* RubricaToString(const struct Rubrica *rubrica)
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