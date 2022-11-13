#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// articolo https://muse.jhu.edu/article/607790/pdf
float generaFloat(float min, float max)
{
    float scale = rand() / (float) RAND_MAX;

    float randomFloat = min + scale * (max - min);
    //printf("Numero float generator: %.2f", randomFloat); // For debugging purposes
    return randomFloat;
}

void FabargeEgg(int matrixHeight, int matrixWidth, int resultMatrix[matrixHeight][matrixWidth])
{
    int i = 0, j = 0;
    float pulsazione = generaFloat(0.15, 0.80);
    float fasePhi = generaFloat(0.0, 1.0);
    float fasePsi = generaFloat(0.0, 1.0);

    for (i = 0; i < matrixHeight; i++)
    {
        for (j = 0; j < matrixWidth; j++)
        {
            float Fji = sin(pulsazione * i + fasePhi) + sin(pulsazione * j + fasePsi);
            float mu = generaFloat(0.0, 20.0);
            int beta = generaFloat(128, 256);
            resultMatrix[i][j] = ((int)floor((beta + mu)*(1.0 + Fji / 2.0))) % beta;
        }
    }
}

int main()
{
    srand(time(NULL));

    int rows = 20;
    int columns = 20;

    int matrix1[rows][columns];
    FabargeEgg(rows, columns, matrix1);
    int matrix2[rows][columns];
    FabargeEgg(rows, columns, matrix2);
    int matrix3[rows][columns];
    FabargeEgg(rows, columns, matrix3);
    // No fourth matrix as it's not needed (also it would be an horrible movie)

    int i, j;
    printf("Printing first matrix\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            printf(" %d ", matrix1[i][j]);
        }
        printf("\n");
    }

    printf("Printing second matrix\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            printf(" %d ", matrix2[i][j]);
        }
        printf("\n");
    }

    printf("Printing third matrix\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            printf(" %d ", matrix3[i][j]);
        }
        printf("\n");
    }

    return 0;
}

