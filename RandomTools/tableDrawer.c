#include <stdio.h>

// Table example
// +----+----+
// |    |    |
// +----+----+ 
// |    |    |
// +----+----+ 

void PrintTable(char cornersChar, char rowsChar, char columnsChar, int innerCellWidth, int innerCellHeight, int tableWidth, int tableHeight)
{
    int cellWidth = innerCellWidth + 1;
    int cellHeight = innerCellHeight + 1;

    for(int y = 0; y <= (tableHeight * cellHeight); y++)
    {
        for(int x = 0; x <= (tableWidth * cellWidth); x++)
        {
            if(x % cellWidth == 0 && y % cellHeight == 0) // Cell corners
            {
                printf("%c", cornersChar);
            }
            else if(y % cellHeight == 0) // Rows
            {
                printf("%c", rowsChar);
            }
            else if(x % cellWidth == 0) // Columns
            {
                printf("%c", columnsChar);
            }
            else // Cell inside
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}