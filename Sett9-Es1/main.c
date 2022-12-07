#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>

void creaTabellone();
void generaTabellone();

struct Giocatore {
    int posizione; // posizione del giocatore sulla tabella

    char simbolo;   // simbolo con cui verrà identificato il giocatore sulla tavola
};

struct Casella {
    int numero; // numero della casella
    int effetto;
};

struct Ladder {
    int posizione;
    int proprieta;  // L'effetto può essere andare avanti oppure indietro, per es (+6 posizioni oppure -10). Se è 0 indica che non ha nessun effetto
};

struct Snake {

};



int main() {
    srand(time(NULL));


    return 0;
}

void creaTabellone() {
    int numero_caselle;
    struct Casella tabellone[100];

}

void generaTabellone(struct Casella *tabellone, int numero_caselle) {
    int contatore = 1;
    for(int i = 0; i < numero_caselle; i++) {
        tabellone[i].numero = contatore;    // Assegno il numero a ogni casella
        contatore++;

        tabellone[i].effetto = rand() % 100;


    }
}