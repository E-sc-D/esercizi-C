#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>
#include <ctype.h>

void aggiungiStudente();
void mostraInfoStudente();
int verificaDuplicatoStudente();
void azzeraStructStudente();
void generaInsegnamenti();
void aggiungiPianoStudi();

struct Studente {
    // Non usare 0 come numero matricola!!
    // 0 è il numero usato per indicare NULL ovvero che lo Studente non è ancora stato inserito/lo spazio è libero
    int numero_matricola;
    char nome[20];
    char cognome[20];
    int anno_immatricolazione;

    int numero_esami;
    struct PianoStudi *ptrPianoStudi;   // Questo puntatore conterrà l'array di strutture PianoStudi con indice num_esami, che verrà generato all'aggiunta dello studente
};

struct Insegnamento {
    int codice_insegnamento;
    char descrizione[60];
    int anno_somministrazione;
    int crediti;

};

struct PianoStudi {  // rivedere forse il nome di questa struct
    int codice_insegnamento;
    int voto;
};

int main () {
    int numero_insegnamenti;
    struct Insegnamento *ptrInsegnamento;
    generaInsegnamenti(&numero_insegnamenti, &ptrInsegnamento); // inserisco in ptrInsegnamento un array di insegnamenti default (vedi metodo)


    int numero_studenti = 10;
    struct Studente *ptrStudente = (struct Studente *) malloc(numero_studenti * sizeof(struct Studente));   // creo un array di numero_studenti strutture

    azzeraStructStudente(ptrStudente, numero_studenti);

    printf("%d", *ptrStudente);
    printf("\n%d", ptrStudente);

    aggiungiStudente(ptrStudente, numero_studenti, ptrInsegnamento, numero_insegnamenti);

    return 0;
}

void aggiungiStudente(struct Studente *ptrStudente, int numero_studenti, struct Insegnamento *ptrInsegnamento, int numero_insegnamenti) {
    int indiceStudente = 0;
    int flag = 0;
    for (indiceStudente = 0; indiceStudente < numero_studenti; indiceStudente++) {
        if (ptrStudente[indiceStudente].numero_matricola == 0) {
            flag = 1;   // trovato un posto libero di indice "indiceStudente"
            break;
        }
    }

    if (flag == 0) {
        printf("Attenzione: il vettore di studenti e completo. Non si possono aggiungere ulteriori studenti");
        printf("\nPremi invio per tornare al menu principale");
        getch();
        return;
    }

    struct Studente s;
    printf("Inserisci il numero matricola dello studente\n\r");
    scanf("%d", &s.numero_matricola);

    while(s.numero_matricola == 0) {
        printf("\nAttenzione! Non puoi inserire 0 come numero matricola. Riprova"); // 0 corrisponde a null

        printf("Inserisci il numero matricola dello studente\n\r");
        scanf("%d", &s.numero_matricola);
    }

    if (verificaDuplicatoStudente(ptrStudente, numero_studenti, s.numero_matricola) == 1) {
        printf("\nErrore: lo studente inserito e gia presente! Premi invio per tornare al menu principale");
        getch();
        return;
    }

    printf("\nInserisci il nome dello studente\n\r");
    scanf("%s", &s.nome);

    printf("\nInserisci il cognome dello studente\n\r");
    scanf("%s", &s.cognome);

    printf("\nInserisci l'anno di immatricolazione dello studente\n\r");
    scanf("%d", &s.anno_immatricolazione);

    printf("\nInserisci il numero di esami dello studente\n\r");
    scanf("%d", &s.numero_esami);

    s.ptrPianoStudi = (struct PianoStudi *) malloc(s.numero_esami * sizeof(struct PianoStudi));
    aggiungiPianoStudi(s.ptrPianoStudi, s.numero_esami, ptrInsegnamento, numero_insegnamenti);









}

void aggiungiPianoStudi(struct PianoStudi *ptrPianoStudi, int numero_esami, struct Insegnamento *ptrInsegnamento, int numero_insegnamenti) {
    system("cls");
    printf("Piano studi:");

    printf("Scegli l'insegnamento:");
    for (int i = 0; i < numero_insegnamenti; i++) {
        printf("\n%d. %s", ptrInsegnamento[i].codice_insegnamento, ptrInsegnamento[i].descrizione);   // esempio: 1. Analisi 1 \n 2. Programmazione \n 3. Sistemi Operativi
    }

    int scelta;
    scanf("%d", &scelta);

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

int verificaDuplicatoStudente(struct Studente *ptrStudente, int numero_studenti, int numero_matricola) {
    for (int i = 0; i < numero_studenti; i++) {
        if (ptrStudente[i].numero_matricola == numero_matricola) {
            return 1;   // esiste un duplicato
        }
    }

    return 0;   // non ci sono duplicati
}

void azzeraStructStudente(struct Studente *ptrStudente, int numero_studenti) {
    for(int i = 0; i < numero_studenti; i++) {
        //memset(&ptrStudente[i], 0, sizeof(struct Studente));
        //ptrStudente[i] = (struct Studente){0};
        ptrStudente[i].numero_matricola = 0;
        strcpy(ptrStudente[i].nome, "");
        strcpy(ptrStudente[i].cognome, "");
        ptrStudente[i].anno_immatricolazione = 0;
        ptrStudente[i].numero_esami = 0;
        ptrStudente[i].ptrPianoStudi = 0;
    }
}

void generaInsegnamenti(int *numero, int *struttura) {  // passando gli indirizzi delle variabili, questo metodo le riempie con rispettivamente il numero di insegnamenti e l'array di strutture insegnamenti
    int numero_insegnamenti = 3;
    struct Insegnamento *ptrInsegnamento = (struct Insegnamento *) malloc(numero_insegnamenti * sizeof(struct Insegnamento));

    ptrInsegnamento[0].codice_insegnamento = 1;
    strcpy(ptrInsegnamento[0].descrizione, "Analisi 1");
    ptrInsegnamento[0].anno_somministrazione = 2022;
    ptrInsegnamento[0].crediti = 6;

    ptrInsegnamento[1].codice_insegnamento = 2;
    strcpy(ptrInsegnamento[1].descrizione, "Programmazione");
    ptrInsegnamento[1].anno_somministrazione = 2022;
    ptrInsegnamento[1].crediti = 6;

    ptrInsegnamento[2].codice_insegnamento = 3;
    strcpy(ptrInsegnamento[2].descrizione, "Sistemi operativi");
    ptrInsegnamento[2].anno_somministrazione = 2022;
    ptrInsegnamento[2].crediti = 6;

    *numero = numero_insegnamenti;
    *struttura = ptrInsegnamento;
}