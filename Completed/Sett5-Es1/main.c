#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define PRINTED_CHAR '#'

// articolo https://muse.jhu.edu/article/607790/pdf

enum Color
{
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Purple,
    Cyan,
    White
};

void ApplyColor(enum Color color)
{
    printf("\033[0;3%dm", color);
}

void ResetColor()
{
    printf("\033[0m");
}

enum Color RGBToANSI(int r, int g, int b) // Ugly way to convert colors from RGB to ANSI standard, basically converts RGB to 8 bit colors
{
    // Reduce values from a range of 0 - 255, to a 0 or 1
    r = r > 128 ? 1 : 0;
    g = g > 128 ? 1 : 0;
    b = b > 128 ? 1 : 0;

    if(r && g && b)
        return White;
    else if(r && g)
        return Yellow;
    else if(r && b)
        return Purple;
    else if(g && b)
        return Cyan;
    else if(r)
        return Red;
    else if(g)
        return Green;
    else if(b)
        return Blue;
    else
        return Black;
}

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
    printf("Printing matrix number %d\n", k + 1);
    for (i = 0; i < 400; i++)
    {
        for (j = 0; j < 400; j++)
        {
            ApplyColor(RGBToANSI(matrix[0][i][j], matrix[1][i][j], matrix[2][i][j]));
            printf("%c", PRINTED_CHAR);
        }
        printf("\n");
    }

    ResetColor();
    return 0;
}

