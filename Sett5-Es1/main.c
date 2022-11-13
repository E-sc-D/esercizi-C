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

void FabargeEgg(int resultMatrix[3][400][400])
{
    int i, j, k;
    for(k = 0; k < 3; k++)
    {
        float pulsazione = generaFloat(0.15, 0.80);
        float fasePhi = generaFloat(0.0, 1.0);
        float fasePsi = generaFloat(0.0, 1.0);

        for (i = 0; i < 400; i++)
        {
            for (j = 0; j < 400; j++)
            {
                float Fji = sin(pulsazione * i + fasePhi) + sin(pulsazione * j + fasePsi);
                float mu = generaFloat(0.0, 20.0);
                int beta = generaFloat(128, 256);
                resultMatrix[k][i][j] = ((int)floor((beta + mu)*(1.0 + Fji / 2.0))) % beta;
            }
        }
    }
}

int main()
{
    srand(time(NULL));

    int matrix[3][400][400];
    FabargeEgg(matrix);

    int i, j, k;
    for(k = 0; k < 3; k++)
    {
        printf("Printing matrix number %d\n", k + 1);
        for (i = 0; i < 400; i++)
        {
            for (j = 0; j < 400; j++)
            {
                printf(" %d ", matrix[k][i][j]);
            }
            printf("\n");
        }
    }
    

    // ############################################################# //
    // Is this the end? Does it do what it's supposed to? Who knows? //
    // ############################################################# //

    return 0;
}

