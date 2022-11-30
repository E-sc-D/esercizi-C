#include <stdio.h>
#include <stdlib.h>
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

typedef struct List
{
    struct Nodo *Head;
} List;

struct Coordinata
{
    int colonna;
    int riga;
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

int ConfrontaCoordinate(struct Coordinata c1, struct Coordinata c2)
{
    if(c1.colonna == c2.colonna && c1.riga == c2.riga)
        return 1;

    return 0;
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

void AddUniqueElement( List *lista, struct Coordinata coordinata )
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
            if(ConfrontaCoordinate(coordinata,navigator->coordinata))
            {
                //se trova una coordinata uguale viene interrotta la ricerca e la coordinata non viene inserita
                gotoxy(0,30);
                printf("trovata coordinata uguale");
                gotoxy(0,0);
                return;
            }
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
    while (navigator->Nodo->Nodo != NULL)
    {
        navigator = navigator->Nodo;
    }
    free(navigator->Nodo);
    navigator->Nodo = NULL;

}

int length(List *lista)
{
    int counter = 0;
    if(lista->Head == NULL)
        return counter;

    counter++;
    
    Nodo *navigator = lista->Head;
    
    while (navigator->Nodo != NULL)
    {
        navigator = navigator->Nodo;
        counter++;
    }
    
    return counter;
}

