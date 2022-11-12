#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// articolo https://muse.jhu.edu/article/607790/pdf
float generaFloat(float min, float max) {
    float scale = rand() / (float) RAND_MAX;

    float randomFloat = min + scale * (max - min);
    printf("Numero float generator: %.2f", randomFloat);
    return randomFloat;
}

void FabargeEgg() {
    float matrice[400][400];

    int i = 0, j = 0;
    float pulsazione;
    float fasePhi, fasePsi;
    pulsazione = generaFloat(0.15, 0.80);
    fasePhi = generaFloat(0.0, 1.0);
    fasePsi = generaFloat(0.0, 1.0);

    for (i = 0; i < 400; i++) {
        for (j = 0; j < 400; j++) {
            //matrice[i,j] = 1 + 0.5;
        }
    }


}

int main() {
    srand(time(NULL));

    FabargeEgg();

    return 0;
}

