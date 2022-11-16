#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

void inizializza_gioco();
int cambiaDifficolta();

int main() {
    srand(time(NULL));

    int scelta = 0;
    int difficolta = 1;

    do {
        system("cls");
        printf("1) Gioca");
        printf("\n\tDifficolta: %d", difficolta);
        printf("\n2) Cambia difficolta");
        printf("\n3) Esci\r\n");

        scanf("%d", &scelta);

        if (scelta == 2) {
            difficolta = cambiaDifficolta(difficolta);
            scelta = 0;
        }
    }
    while (scelta > 3 || scelta < 1);

    switch (scelta) {
        case 1: gioca(difficolta);
        case 3: exit(0);
    }
}

void inizializza_gioco(int difficolta) {
    int row = 10;
    int column = 10;
    int campo[row][column];
}

void generaMine(int **matrix, int row, int column, int difficolta) {
    int numeroMine;     // quante mine ci saranno sul campo
    // assegnare il numeroMine in base alla difficolta
    numeroMine = 5; // per adesso assegno 5 (statico)

    int minePos[numeroMine][2]; // array che contiene la posizione di ogni mina
    // assegno 2 colonne perché avrò la posizione x e la posizione y della mina

    int flag = 0;
    for (int i = 0; i < numeroMine; i++) {
        do {
            flag = 0;

            minePos[i][0] = rand() % row;
            minePos[i][1] = rand() % column;

            for (int j = i; j > 0; j--) {   // Controllo se nella posizione generata esiste già una mina
                if ((minePos[i][0] == minePos[j][0]) && (minePos[i][1] == minePos[j][1]))
                    flag = 1;
            }
        }
        while (flag == 1);  // Se esiste già una mina nella posizione generata, genera una nuova posizione
    }
}

int cambiaDifficolta(int difficolta) {
    difficolta += 1;

    if(difficolta > 5)  // La difficolta massima è 5
        difficolta = 1;

    return difficolta;
}