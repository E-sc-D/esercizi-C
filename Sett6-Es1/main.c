#include <stdio.h>
#include "rubrica.c"
#include "interactableMenu.c"

void function1()
{
    printf("xd");
}

void function2()
{
    printf("lol");
}

int main()
{
    /*struct Rubrica rubrica; // = NewRubrica(); Technically needed, but apparently not (detailed explaination in "rubrica.c")

    if(IsRubricaFull(rubrica))
    {
        printf("Full");
    }
    else
    {
        printf("Not full");
    }*/

    struct MenuOption options[2] =
    {
        NewMenuOption("Test", &function1),
        NewMenuOption("Test2", &function2)
    };
    struct Menu menu = NewMenu(20, 2, options);

    DrawMenu(&menu);

    return 0;
}