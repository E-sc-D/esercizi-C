#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>

void crea_tabellone();
void genera_tabellone();
int genera_numero_in_range();


struct Giocatore {
    int posizione; // posizione del giocatore sulla tabella

    char simbolo;   // simbolo con cui verrà identificato il giocatore sulla tavola
};

struct Casella {
    int numero; // numero della casella
    int effetto;    // L'effetto può essere andare avanti oppure indietro, per es (+6 posizioni oppure -10). Se è 0 indica che non ha nessun effetto
};

int main() {
    srand(time(NULL));

    return 0;
}

void crea_tabellone() {
    int numero_caselle;
    struct Casella tabellone[100];

}

void genera_tabellone(struct Casella *tabellone, int numero_caselle) {   // Questo metodo genera il tabellone e assegna quindi anche quali caselle sono scivoli e quali scale
    int contatore = 1;
    for(int i = 0; i < numero_caselle; i++) {   // Scorro l'array di caselle
        tabellone[i].numero = contatore;    // Assegno il numero a ogni casella partendo da 1
        contatore++;

        tabellone[i].effetto = 0;   // Azzero gli effetti di ogni casella
    }

    int indice_casella = 0;
    int indice_coda = 0;
    int effetto = 0, max_effetto = 0, min_effetto = 0;


    int max_serpenti = 10; //  numero massimo di serpenti
    int min_serpenti = 4;  // numero minimo di serpenti
    int num_serpenti = genera_numero_in_range(min_serpenti, max_serpenti);  // genero randomicamente un numero di serpenti tra min_serpenti e max_serpenti

    for(int i = 0; i < num_serpenti; i++) {
        indice_casella = genera_numero_in_range(1, indice_casella - 1);  // genero un indice_casella randomico compreso tra 1 e indice_casella - 1 (perché la prima casella è la partenza e l'ultima è la vincita)
        if (tabellone[indice_casella].effetto == 0) {   // controllo se la casella di indice_casella non ha nessun effetto assegnato
            max_effetto = -1;   // L'effetto serpente per esistere deve far scendere i giocatori di almeno 1 posizione
            min_effetto = -indice_casella;  // I giocatori non possono scendere più della grandezza della tabella

            do {
            effetto = genera_numero_in_range(min_effetto, max_effetto); // genero randomicamente il valore dell'effetto tra min_effetto e max_effetto

            indice_coda = indice_casella - abs(effetto); // ottengo l'indice della casella della coda del serpente; uso abs(x) perché l'effetto è negativo

            } while (tabellone[indice_coda].effetto != 0);  // Rigenero l'effetto finché l'indice della coda non trovo una coda libera (senza effetti)

            tabellone[indice_casella].effetto = effetto;    // assegno l'effetto generato
        }
    }
}

int genera_numero_in_range(int min, int max) {
    int numero = (rand() % (max - min + 1)) + min;

    return numero;
}