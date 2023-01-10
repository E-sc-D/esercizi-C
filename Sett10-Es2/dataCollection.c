#include <stdlib.h>
#include <stdio.h>
#include "variant.c"


struct Array
{
    var *self;
    int size;
    int elements;
};

struct Array newArray(int size)
{
    struct Array array;
    array.self = malloc(sizeof(var)*size);
    array.size = size;
    array.elements = 0;
    return array;
}

int stack_push(var value,struct Array *array)
{
    
        if(array->elements < array->size)
        {
            array->self[array->elements] = value;
            array->elements++; 
            return 1; 
        }
    
    return 0;
}

int stack_Fpush(var value,struct Array *array)
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

var stack_pop(struct Array *array)
{
    if(array->elements > 0)
    {
        var buffer = array->self[array->elements - 1];
        array->elements--;
        return buffer;
    }
    return;
}

int que_push(var value,struct Array *array)
{
    return stack_push(value,array);
}

int que_Fpush(var value , struct Array *array)
{
    return stack_Fpush(value, array);
}   

var que_pop(struct Array *array)
{
    int i;
    var returnVal;
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
    
    que_Fpush(var_set_int(5),&array);
    que_Fpush(var_set_int(5),&array);
    que_Fpush(var_set_int(5),&array);
    que_Fpush(var_set_int(5),&array);
    printf("\nvalori contenuti: %d\n",array.elements);
    printf("valori contenuti : %d , dimensioni dell'array %d, valore di pop %d\n",array.elements,array.size,que_pop(&array));
    printf("valori contenuti : %d , dimensioni dell'array %d, valore di pop %d\n",array.elements,array.size,que_pop(&array));
    printf("valori contenuti : %d , dimensioni dell'array %d, valore di pop %d\n",array.elements,array.size,que_pop(&array));
    printf("valori contenuti : %d , dimensioni dell'array %d, valore di pop %d\n",array.elements,array.size,que_pop(&array));
    free(array.self);
}
