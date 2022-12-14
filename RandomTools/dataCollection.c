#include <stdlib.h>
#include <stdio.h>

#define DATA_TYPE2  int

#ifndef DATA_TYPE2
#error DATA_TYPE not defined
#else

struct Array
{
    DATA_TYPE2 *self;
    int size;
    int elements;
};

struct Array newArray(int size,struct Array **array)
{
    (*array ) = malloc(sizeof(DATA_TYPE2)*size);
    (*array)->size = size;
    (*array)->elements = 0;
}

int stack_push(DATA_TYPE2 value,struct Array *Array)
{
    
        if(Array->elements < Array->size)
        {
            Array->self[Array->elements] = value;
            Array->elements++; 
            return 1; 
        }
    
    return 0;
}

int stack_Fpush(DATA_TYPE2 value,struct Array **Array)
{
    
        if((*Array)->elements < (*Array)->size)
        {
            (*Array)->self[(*Array)->elements] = value;
            (*Array)->elements++; 
            
        }
        else
        {
            (*Array) =  realloc((*Array),(*Array) -> size + 1 );
            if(*Array == NULL)
            {
                return 0 ;
            }       
            (*Array)->self[(*Array)->elements] = value;
            (*Array)->elements++; 
        }
        return 1; 
    
   
}

DATA_TYPE2 stack_pop(struct Array *Array)
{
    if(Array->elements > 0)
    {
        DATA_TYPE2 buffer = Array->self[Array->elements - 1];
        Array->elements--;
        return buffer;
    }
    return;
}

int que_push(DATA_TYPE2 value,struct Array *array)
{
    return stack_push(value,array);
}

int que_Fpush(DATA_TYPE2 value , struct Array **array)
{
    return stack_Fpush(value, array);
}

DATA_TYPE2 que_pop(struct Array *array)
{
    int i;
    DATA_TYPE2 returnVal = array->self[0];

    for( i = 1 ; i < array->size; i++)
    {
        array->self[i-1] = array ->self[i];
    }

    return returnVal;

}
int main()
{
    struct Array *array;
    newArray(10,&array);
    //stack_Fpush(5,&array);
    printf("\nvalori contenuti: %d",array->elements);
    printf("valori contenuti : %d , dimensioni dell'array %d, valore di pop %d",array->elements,array->size,stack_pop(array));
}
#endif