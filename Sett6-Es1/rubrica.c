#include <string.h>
#include "myBool.c"

#define NOME_LENGTH 40
#define COGNOME_LENGTH 40
#define NUMERO_TELEFONICO_LENGTH 10

#define RUBRICA_LENGTH 1000

struct Contatto
{
    char Nome[NOME_LENGTH];
    char Cognome[COGNOME_LENGTH];
    char NumeroTelefonico[NUMERO_TELEFONICO_LENGTH];   
} EmptyContatto = { {'\0'}, {'\0'}, {'\0'} };

struct Rubrica
{
    struct Contatto Contatti[RUBRICA_LENGTH];
};

struct Rubrica NewRubrica() // Constructor-like method to have a Rubrica with every Contatto = EmptyContatto
{
    struct Rubrica initializedRubrica;

    int i;
    for(i = 0; i < RUBRICA_LENGTH; i++)
        initializedRubrica.Contatti[i] = EmptyContatto; // Apparently not needed as the char arrays in Contatto seem to already
                                                        // have the null character, don't know why, how or what is happening

    return initializedRubrica;
}

enum bool ContattoCompare(const struct Contatto contatto1, const struct Contatto contatto2) // Returns 1 if contatto1 and contatto2 are the same, 0 if not
{
    if(strcmp(contatto1.Nome, contatto2.Nome) == 0
    && strcmp(contatto1.Cognome, contatto2.Cognome) == 0
    && strcmp(contatto1.NumeroTelefonico, contatto2.NumeroTelefonico) == 0)
        return true;
    else
        return false;
}

enum bool IsContattoEmpty(const struct Contatto contatto) // Returns 1 if contatto is empty, 0 if not
{
    if(ContattoCompare(contatto, EmptyContatto))
        return true;
    else
        return false;
}

int FindEmptyIndex(const struct Rubrica *rubrica) // Returns the index of the first empty place in rubrica, if none returns -1
{
    int i;
    for(i = 0; i < RUBRICA_LENGTH; i++)
        if(IsContattoEmpty(rubrica->Contatti[i]))
            return i;
    return -1;
}

int FindContatto(const struct Rubrica *rubrica, const struct Contatto contatto) // Returns the index of the first occurrence of contatto in rubrica, if none return -1
{
    int i;
    for(i = 0; i < RUBRICA_LENGTH; i++)
        if(ContattoCompare(rubrica->Contatti[i], contatto))
            return i;
    return -1;
}

enum bool IsRubricaFull(const struct Rubrica *rubrica) // Returns 1 if rubrica is full (no empty places), 0 if not
{
    if(FindEmptyIndex(rubrica) == -1)
        return true;
    else
        return false;
}

enum bool AddContatto(struct Rubrica *rubrica, const struct Contatto contatto) // Returns 1 if contatto has been successfully added to rubrica, 0 if not
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

enum bool RemoveContatto(struct Rubrica *rubrica, const struct Contatto contatto) // Returns 1 if contatto has been successfully removed from rubrica, 0 if not
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