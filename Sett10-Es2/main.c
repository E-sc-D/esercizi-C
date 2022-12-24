#include <stdio.h>
#include <stdlib.h>
#include "list.c"
#include "dataCollection.c"
int main()
{
    int input;
    printf("il testing della pila avviene tramite valori interi\n");
    while (input != 0)
    {
       printf("Scegli La base della pila/coda\n[1] per array\n[2] per coda\n");
       scanf(" %d",&input);
       if(input == 1)
       {
            printf("modalità array scelta\n");
            int j;
            struct Array array;
            array = newArray();
            while(j != 0)
            {
                printf("[0] per uscire\n[1] per visualizzare la pila\n[2] per inserire un elemento dentro la pila\n");
                printf("[3] per rimuovere un elemento dalla pila");
                scanf(" %d",&j);
                switch (j)
                {
                    case 1:
                    
                    break;

                    case 2:
                    
                    break;

                    case 3:
                    
                    break;
                    
                    default:
                    break;
                }
            }
       }
       else
       {
            printf("modalità coda scelta\n");
            int j;
            List lista;
            lista = list_new();
            while(j != 0)
            {
                printf("[0] per uscire\n[1] per visualizzare la pila\n[2] per inserire un elemento dentro la pila\n");
                printf("[3] per rimuovere un elemento dalla pila");
                scanf(" %d",&j);
                switch (j)
                {
                    case 1:
                    
                    break;

                    case 2:
                    
                    break;

                    case 3:
                    
                    break;
                    
                    default:
                    break;
                }
            }
       }
    }
    
}
