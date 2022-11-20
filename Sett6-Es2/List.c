#include <stdio.h>
#include <stdlib.h>

typedef struct List
{
    struct Nodo *Head;

}List;

struct Coordinata
{
    int x;
    int y;
}emptyCoordinata = {0,0};

typedef struct Nodo
{
    struct Coordinata coordinata;
    struct Nodo *Nodo;
}Nodo;

void AddElement( List *lista,struct Coordinata coordinata )
{
    
    if(lista->Head == NULL)
    {
      lista->Head = (Nodo*) malloc (sizeof(Nodo));
      lista->Head->coordinata = coordinata;
    }      
    else
    {
        Nodo *navigator = lista->Head;
        while (navigator->Nodo != NULL)
        {
            navigator = navigator->Nodo;
        }

        navigator->Nodo = (Nodo*) malloc (sizeof(Nodo));

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

