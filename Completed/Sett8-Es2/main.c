#include <stdio.h>

#include "list.c"

int main()
{
    struct burh
    {
        char hah;
        int lol;
    };

    struct burh xd;
    xd.hah = 'J';
    xd.lol = 11037;

    var fakeInt = var_set(sizeof(struct burh), &xd);

    printf("%d", (*(struct burh*)var_get(fakeInt)).lol);

    List list = new_list();
    /*int array[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    List lista = list_from_array(10, array, sizeof(int));
    printf("%d", get_length(&lista));*/
}