#include <stdio.h>
#include <stdlib.h>
#include "list.c"
#include "dataCollection.c"

int main()
{
    int input = 1;
    printf("il testing della pila avviene tramite valori interi\n\n");
    while (input != 0)
    {
       printf("Scegli La base della pila\n[1] per array\n[2] per lista\n\n");
       scanf("%d",&input);
       if(input == 1)
       {
            printf("modalita array scelta\n\n");
            int j;
            int inp;
            struct Array array;
            array = newArray(10);
            while(j != 0)
            {
                printf("[0]  uscire\n[1]  visualizzare la pila\n[2]  inserire un elemento dentro la pila\n");
                printf("[3]  forzare un elemento nella pila\n[4] rimuovere un elemento dalla pila\n\n");
                scanf(" %d",&j);
                switch (j)
                {
                    case 1:
                        que_print_int(&array);
                    break;

                    case 2:
                        scanf("%d",&inp);
                        stack_push(var_set_int(inp),&array);
                    break;

                    case 3:
                        scanf("%d",&inp);
                        stack_Fpush(var_set_int(inp),&array);
                    break;

                    case 4:
                        printf("elemento restituito %d\n",var_get_int(stack_pop(&array)));
                    break;
                    
                    default:
                    break;
                }
            }
       }
       else
       {
            printf("modalita lista scelta\n\n");
            int j = 1;
            int i;
            int inp;
            List lista;
            var *array;
            lista = list_new();
            while(j != 0)
            {
                printf("[0] per uscire\n[1] per visualizzare la pila\n[2] per inserire un elemento dentro la pila\n");
                printf("[3] per rimuovere un elemento dalla pila\n\n");
                scanf(" %d",&j);
                switch (j)
                {
                    case 1:
                        array = list_to_array(&lista);
                        for(i = 0 ; i < list_length_get(&lista) ; i++)
                        {
                            printf(" %d <-->",var_get_int((array[i])));
                        }
                        printf("\n");
                    break;

                    case 2:
                        scanf("%d",&inp);
                        list_element_add(&lista,var_set_int(inp));
                    break;

                    case 3:
                        var buffer = list_pop_back(&lista);
                        if(buffer.data == NULL)
                        {
                            printf("la coda è vuota\n");
                            break;
                        }
                        printf("here");
                        //printf("elemento restituito: %d\n",var_get_int(buffer));
                    break;
                    
                    default:
                    break;
                }
            }
       }
    }
    
}
