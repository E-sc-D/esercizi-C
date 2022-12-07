#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>
#include <ctype.h>

struct Giocatore {
    int posizione; // posizione del giocatore sulla tabella

    char simbolo;   // simbolo con cui verrà identificato il giocatore sulla tavola
};

struct Casella {
    int numero; // numero della casella
    int effetto; // L'effetto può essere andare avanti oppure indietro, per es (+6 posizioni oppure -10). Se è 0 indica che non ha nessun effetto
};

int main() {



    return 0;
}

void CreaTabellone() {
    struct Casella tabellone[100];

}