#include <stdio.h>
#include "rubrica.c"

int main()
{
    struct Rubrica rubrica; // = NewRubrica(); Technically needed, but apparently not (detailed explaination in "rubrica.c")

    if(IsRubricaFull(&rubrica))
    {
        printf("Full");
    }
    else
    {
        printf("Not full");
    }

    return 0;
}