#include <stdio.h>
#include <stdlib.h>

typedef struct List
{
    struct Nodo *Head;
} List;

struct Coordinata
{
    int x;
    int y;
} emptyCoordinata = {0, 0};

typedef struct Nodo
{
    struct Coordinata coordinata;
    struct Nodo *Nodo;
} Nodo;

List NewList() // Metodo simil-costruttore per settare a NULL l'Head della lista
{
    List newList;
    newList.Head = NULL;
    return newList;
}

void AddElement( List *lista, struct Coordinata coordinata )
{
    if(lista->Head == NULL) // QUESTO NON SI TRIGGERAVA PERCHE' UNA NUOVA LISTA CON 0 ELEMENTI
                            // NON HA IL PUNTATORE NECESSARIAMENTE A NULL MA AD UN VALORE RANDOM
    {
      lista->Head = malloc(sizeof(Nodo));
      lista->Head->Nodo = NULL; // Setta il puntatore del Nodo successivo a NULL
      lista->Head->coordinata = coordinata;
    }      
    else
    {
        Nodo *navigator = lista->Head;
        while (navigator->Nodo != NULL) // STESSA COSA QUI!
        {
            navigator = navigator->Nodo;
        }

        navigator->Nodo = malloc (sizeof(Nodo));
        navigator->Nodo->Nodo = NULL; // Setta il puntatore del Nodo successivo a NULL
        navigator->Nodo->coordinata = coordinata;
    }
}

Nodo* GetLastElement(struct List *lista)//restituisce il primo elemento e lo rimuove dalla lista
{
    if(lista->Head == NULL)
        return NULL;

    Nodo *navigator = lista->Head;
    
    while (navigator->Nodo != NULL)
    {
        navigator = navigator->Nodo;
    }

    return navigator;
}

void DeleteLastElement(struct List *lista)
{
    if(lista->Head == NULL)
        return;

    if(lista->Head->Nodo == NULL)
    {
       free(lista->Head); 
       lista->Head = NULL;
       return;
    }
        
    Nodo *navigator = lista->Head;
    Nodo *prec;
    while (navigator->Nodo->Nodo != NULL)
    {
        navigator = navigator->Nodo;
    }
    free(navigator->Nodo);
    navigator->Nodo = NULL;

}

