#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Point
{
    double x;
    double y;
};

void delay(int seconds)
{
    int milliseconds = 1000 * seconds;
    clock_t startTime = clock();
    while(clock() < startTime + milliseconds);
}

int main(void)
{
    srand(time(NULL));

    struct Point coords;
    coords.x = rand();
    coords.y = rand();

    printf("TEST");
    fflush(stdout);
    delay(5);
    //sleep(5);
    printf("\rBRUH\n");
}