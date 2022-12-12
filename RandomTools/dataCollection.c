#include <stdlib.h>
#include <stdio.h>

#define DATA_TYPE2 int

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

int pile_push(DATA_TYPE2 value,struct Array *Array)
{
    if(value != NULL)
    {
        if(Array->elements < Array->size)
        {
            Array->self[Array->elements] = value;
            Array->elements++; 
            return 1; 
        }
    }
    return 0;
}

int Fpile_push(DATA_TYPE2 value,struct Array **Array)
{
    if(value != NULL)
    {
        if((*Array)->elements < (*Array)->size)
        {
            (*Array)->self[(*Array)->elements] = value;
            (*Array)->elements++; 
            
        }
        else
        {
            realloc((*Array),(*Array) -> size + 1 );
            if(*Array == NULL)
                return 
            (*Array)->self[(*Array)->elements] = value;
            (*Array)->elements++; 
        }
        return 1; 
    }
    return 0;
}

DATA_TYPE2 pile_pop(struct Array *Array)
{
    if(Array->elements > 0)
    {
        DATA_TYPE2 buffer = Array->self[Array->elements - 1];
        Array->elements--;
        return buffer;
    }
    return NULL;
}
int main()
{

}
#endif