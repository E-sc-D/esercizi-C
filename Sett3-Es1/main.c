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

void BuildTableLine(int columns, int cellWidth)
{
    printf("+");
    for(int j = 0; j < columns; j++)
    {
        for(int f = 0; f < cellWidth; f++)
        {
            printf("-");
        }
        printf("+");              
    }
    printf("\n");
}

void BuildTableCells(int columns, int cellHeight, int cellWidth)
{
    for(int s = 0; s < cellHeight; s++)
    {
        printf("|");
        for(int t = 0; t < columns; t++)
        {               
            for(int f = 0; f < cellWidth; f++)
            {
                printf(" ");
            }
            printf("|");              
        } 
        printf("\n"); 
    } 
}

void BuildTable(int rows, int columns, int cellWidth, int cellHeight)
{
    for(int i = 0; i < rows; i++)
    {
       BuildTableLine(columns, cellWidth);
       BuildTableCells(columns, cellHeight, cellWidth);     
    }
    BuildTableLine(columns, cellWidth);
}


// +----+
// |    |
// +----+

int main(void)
{
    srand(time(NULL));

    struct Point coords;
    coords.x = rand();
    coords.y = rand();
    fflush(stdout);

    BuildTable(5, 5, 4, 1);

    //delay(5);
    //sleep(5);

}
