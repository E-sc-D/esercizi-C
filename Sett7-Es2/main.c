#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>
#include <ctype.h>

void aggiungiStudente();

struct Studente {
    int numero_matricola;
    char nome[20];
    char cognome[20];
    int anno_immatricolazione;


};

struct Insegnamento {
    int codice_insegnamento;
    char descrizione[60];
    int anno_somministrazione;
    int crediti;

};

struct Esame {  // rivedere forse il nome di questa struct
    int codice_insegnamento;
    int voto;
};

int main () {

    int numero_studenti = 10;

    struct Studente *ptrStudente = (struct Studente *) malloc(numero_studenti * sizeof(struct Studente));
    //azzeraStruct()?




    return 0;
}

void aggiungiStudente(int numero_matricola) {

}

void mostraInfoStudente(struct Studente *ptrStudente, int numero_studenti, int numero_matricola) {
    int indiceStudente = 0;
    int flag = 0;
    for (indiceStudente = 0; indiceStudente < numero_studenti; indiceStudente++) {
        if (ptrStudente[indiceStudente].numero_matricola == numero_matricola) {
            flag = 1;
            break;
        }
    }

    if (flag == 0) {
        printf("Non e stato trovato uno studente con il numero di matricola inserito. Premi invio per continuare\r\n");
        getch();
        return;
    }
    system("cls");
    printf("\nNumero matricola: %d", ptrStudente[indiceStudente].numero_matricola);
    printf("\nNome: %s", ptrStudente[indiceStudente].nome);
    printf("\nCognome: %s", ptrStudente[indiceStudente].cognome);
    printf("\nAnno di immatricolazione: %d", ptrStudente[indiceStudente].anno_immatricolazione);

    printf("\n\rPremi invio per tornare al menu principale\n\r");
    getch();

}