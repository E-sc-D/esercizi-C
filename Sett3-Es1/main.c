#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Point
{
    double x;
    double y;
};

int main(void)
{

    srand(time(NULL));

    struct Point coords;
    coords.x = rand();
    coords.y = rand();



}