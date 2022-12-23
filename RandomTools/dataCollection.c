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

struct Array newArray(int size)
{
    struct Array array;
    array.self = malloc(sizeof(DATA_TYPE2)*size);
    array.size = size;
    array.elements = 0;
    return array;
}

int stack_push(DATA_TYPE2 value,struct Array *array)
{
    
        if(array->elements < array->size)
        {
            array->self[array->elements] = value;
            array->elements++; 
            return 1; 
        }
    
    return 0;
}

int stack_Fpush(DATA_TYPE2 value,struct Array *array)
{
    
        if(array->elements < array->size)
        {
            array->self[array->elements] = value;
            array->elements++; 
            
        }
        else
        {
            array->self =  realloc(array->self,(array->size) + 1  );
            if(array->self == NULL)
            {
                return 0 ;
            }       
            array->self[array->elements] = value;
            array->elements++; 
        }
        return 1; 
    
   
}

DATA_TYPE2 stack_pop(struct Array *array)
{
    if(array->elements > 0)
    {
        DATA_TYPE2 buffer = array->self[array->elements - 1];
        array->elements--;
        return buffer;
    }
    return;
}

int que_push(DATA_TYPE2 value,struct Array *array)
{
    return stack_push(value,array);
}

int que_Fpush(DATA_TYPE2 value , struct Array *array)
{
    return stack_Fpush(value, array);
}   

DATA_TYPE2 que_pop(struct Array *array)
{
    int i;
    DATA_TYPE2 returnVal;
    if(array->elements > 0)
    {
        returnVal = array->self[0];

        for( i = 1 ; i < array->size; i++)
        {
            array->self[i-1] = array ->self[i];
        }

        array->elements--;

    }
   
    return returnVal;
}
int main()
{
    struct Array array;
    array = newArray(10);
    
    que_Fpush(5,&array);
    que_Fpush(4,&array);
    que_Fpush(3,&array);
    que_Fpush(2,&array);
    printf("\nvalori contenuti: %d\n",array.elements);
    printf("valori contenuti : %d , dimensioni dell'array %d, valore di pop %d\n",array.elements,array.size,que_pop(&array));
    printf("valori contenuti : %d , dimensioni dell'array %d, valore di pop %d\n",array.elements,array.size,que_pop(&array));
    printf("valori contenuti : %d , dimensioni dell'array %d, valore di pop %d\n",array.elements,array.size,que_pop(&array));
    printf("valori contenuti : %d , dimensioni dell'array %d, valore di pop %d\n",array.elements,array.size,que_pop(&array));
    free(array.self);
}
#endif