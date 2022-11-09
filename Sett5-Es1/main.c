#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float generaFloat(float min, float max) {
    float scale = rand() / (float) RAND_MAX;

    float randomFloat = min + scale * (max - min);
    printf("Numero float generator: %.2f", randomFloat);
    return randomFloat;
}

void FabargeEgg() {
    float pulsazione;
    float fasePhi, fasePsi;
    pulsazione = generaFloat(0.15, 0.80);
    fasePhi = generaFloat(0.0, 1.0);
    fasePsi = generaFloat(0.0, 1.0);


}

int main() {
    srand(time(NULL));

    FabargeEgg();

    return 0;
}

