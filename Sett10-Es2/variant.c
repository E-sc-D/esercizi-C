#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Variant
{
    void* data;
    size_t size;
};

typedef struct Variant Variant;
typedef Variant var;

const var var_null = { NULL, 0 };

void var_free(var *variant)
{
    free(variant->data);
    variant->data = NULL;
    variant->size = 0;
}

var var_set(size_t size, void* data)
{
    var new_variant;
    new_variant.size = size;
    new_variant.data = malloc(new_variant.size);
    memcpy(new_variant.data, data, new_variant.size);
    return new_variant;
}

var var_set_var(var variant)
{
    return var_set(variant.size, variant.data);
}

var var_set_int(int variable)
{
    return var_set(sizeof(int), &variable);
}

var var_set_char(char variable)
{
    return var_set(sizeof(char), &variable);
}

var var_set_float(float variable)
{
    return var_set(sizeof(float), &variable);
}

var var_set_double(double variable)
{
    return var_set(sizeof(double), &variable);
}

void* var_get(var variant)
{
    return variant.data;
}

int var_get_int(var variant)
{
    return *((int*)variant.data);
}

char var_get_char(var variant)
{
    return *((char*)variant.data);
}

float var_get_float(var variant)
{
    return *((float*)variant.data);
}

double var_get_double(var variant)
{
    return *((double*)variant.data);
}