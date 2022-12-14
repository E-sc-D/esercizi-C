#include <stdio.h>

#include "list.c"
#define DATA_TYPE int


int main()
{
    int array[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    List lista = list_from_array(10, array);
    printf("%d", get_length(&lista));
}