#define DATA_TYPE int

#include <stdio.h>
#include <stdlib.h>
#include "./list.c"

int main()
{
    List lista = new_list();
    printf("\n aggiunta elemento: %d",add_element(&lista,5));
    printf("\n lunghezza della lista %d",get_length(&lista));
    printf("\n presa di un elemento %d",get_element(&lista,0));
    printf("\n presa di un elemento con pop %d",pop_front(&lista));
    printf("\n lunghezza della lista %d",get_length(&lista));
}