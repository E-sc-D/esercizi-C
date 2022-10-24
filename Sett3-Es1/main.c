#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

    printf("bruh");
    fflush(stdout);
    time_t now = 0;

    for( ; clock() - now < 2*CLOCKS_PER_SEC ; );
    printf("\rHAHA\n");

    BuildTable(5, 5, 4, 1);
}
