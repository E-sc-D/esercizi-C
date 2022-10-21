#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cellWidth = 4;
int cellHeight = 1;

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

void CellTop(int columns,int cellwidth)
{
    printf("+");
        for(int j = 0;j<columns;j++)
        {
        
           for(int f = 0;f<cellwidth;f++){ printf("-");}
           printf("+");              
        }
        printf("\n");
}
void CellBody(int columns, int cellheight,int cellwidth)
{
    for(int s = 0;s<cellheight;s++)
        {
            printf("|");
            for(int t = 0;t<columns;t++)
            {               
                for(int f = 0;f<cellwidth;f++){ printf(" ");}
                printf("|");              
            } 
            printf("\n"); 
        } 
}

void battleship(int rows,int columns)
{
    for(int i = 0; i<rows;i++)
    {
       CellTop(columns,cellWidth);
       CellBody(columns,cellHeight,cellWidth);     
    }
    CellTop(columns,cellWidth);
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
    battleship(5,5);
    //delay(5);
    //sleep(5);

}
