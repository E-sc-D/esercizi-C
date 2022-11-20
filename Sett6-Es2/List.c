#include <stdio.h>;
#include <stdlib.h>;

typedef struct List
{
    struct Coordinata coordinata;
    struct List *lista
}List;

struct Coordinata
{
    int x;
    int y;
}emptyCoordinata = {0,0},nullCoordinata = {}

void AddElement(struct List *lista,struct Coordinata coordinata)
{
    struct List *navigator;
    navigator = lista;

    while((*navigator).lista != NULL)
    {
        navigator = navigator->lista;
    }


    navigator->lista = ( struct List* )malloc( sizeof( struct List ) );//una volta trovato il puntatore vuoto lo riempe

    navigator->lista->coordinata.x = coordinata.x;//gli mette la coordinata dentro
    navigator->lista->coordinata.y = coordinata.y;

}

struct Coordinata PopElement(struct List *lista)//restituisce il primo elemento e lo rimuove dalla lista
{
    struct List *navigator;
    navigator = lista;
    struct List *prec;
    struct Coordinata coordinata;

    while((*navigator).lista != NULL)
    {
        prec = navigator;
        navigator = navigator->lista;
    }

    prec->lista = NULL;//una volta trovato il puntatore vuoto lo riempe

    coordinata.x = navigator->coordinata.x;
    coordinata.y = navigator->coordinata.y;
    
    free(navigator);
    return NULL;
}

