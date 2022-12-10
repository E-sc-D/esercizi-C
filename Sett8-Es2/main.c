#include <stdio.h>

#define DATA_TYPE int
#include "list.c"

int main()
{
    int array[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    List lista = list_from_array(10, array);
    printf("%d", get_length(&lista));
}