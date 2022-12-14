#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>
#include <ctype.h>

#include "list.c"
#define DATA_TYPE int


struct Studente
{
    // Non usare 0 come numero matricola!!
    // 0 è il numero usato per indicare NULL ovvero che lo Studente non è ancora stato inserito/lo spazio è libero
    int numero_matricola;
    char nome[20];
    char cognome[20];
    int anno_immatricolazione;

    int numero_esami;
    struct PianoStudi *ptrPianoStudi;   // Questo puntatore conterrà l'array di strutture PianoStudi con indice num_esami, che verrà generato all'aggiunta dello studente
} EmptyStudente = { 0, "", "", 0, 0, NULL };

struct Insegnamento
{
    int codice_insegnamento;
    char descrizione[60];
    int anno_somministrazione;
    int crediti;
} EmptyInsegnamento = { 0, "", 0, 0 };

struct PianoStudi // rivedere forse il nome di questa struct
{
    int codice_insegnamento;
    int voto;
};

struct Studente * cercaStudente(List *studenti, int numero_matricola)
{
    int length = list_length_get(studenti);
    for(int i = 0; i < length; i++)
    {
        struct Studente *studenteAttuale = (struct Studente*)var_get(list_element_get(studenti, i));
        if (studenteAttuale->numero_matricola == numero_matricola)
            return studenteAttuale;
    }
    return NULL;
}

void generaPianoStudi(struct Studente *studente, List insegnamenti)
{
    system("cls");
    printf("Piano studi:\n");

    printf("Insegnamenti disponibili");
    int numero_insegnamenti = list_length_get(&insegnamenti);
    for (int i = 0; i < numero_insegnamenti; i++)
    {
        struct Insegnamento *insegnamentoAttuale = (struct Insegnamento*)var_get(list_element_get(&insegnamenti, i));
        printf("\n%d. %s", insegnamentoAttuale->codice_insegnamento, insegnamentoAttuale->descrizione);   // esempio: 1. Analisi 1 \n 2. Programmazione \n 3. Sistemi Operativi
    }

    printf("\n");

    studente->ptrPianoStudi = (struct PianoStudi *) malloc(studente->numero_esami * sizeof(struct PianoStudi));
    int i = 0;
    int uscita = 0;
    while(i < studente->numero_esami && uscita == 0)
    {
        printf("\nIterazione n. %d", i);
        int scelta;
        do
        {
            printf("\nSeleziona un insegnamento da aggiungere al piano studi\n\r");
            printf("(range valori accettabili: [1, %d])\n\r", numero_insegnamenti);
            scanf("%d", &scelta);
        }
        while(scelta < 1 || scelta > numero_insegnamenti);

        int voto;
        do
        {
            struct Insegnamento *insegnamento = (struct Insegnamento*)var_get(list_element_get(&insegnamenti, scelta - 1));
            printf("\nInserisci il voto da aggiungere per %s (0 se non ancora svolto)\n\r", insegnamento->descrizione);
            printf("(range valore accettabili: [0, 30])\n\r");
            scanf("%d", &voto);
        }
        while(voto < 0 || voto > 30);

        struct Insegnamento *insegnamento = (struct Insegnamento*)var_get(list_element_get(&insegnamenti, scelta - 1));
        studente->ptrPianoStudi[i].codice_insegnamento = insegnamento->codice_insegnamento;
        studente->ptrPianoStudi[i].voto = voto;

        i++;

        printf("\nVuoi continuare a modificare il piano di studi? (0 per continuare)\n\r", insegnamento->descrizione);
        printf("(rimangono %d posti disponibili nel tuo piano di studi)\n\r", studente->numero_esami - i);
        scanf("%d", &uscita);
    }
    int k;
    for(k = i; k < studente->numero_esami; k++)
    {
        studente->ptrPianoStudi[k].voto = 0;
        studente->ptrPianoStudi[k].codice_insegnamento = 0;
    }
}

void aggiungiStudente(List *studenti, List insegnamenti)
{
    struct Studente s;
    printf("Inserisci il numero matricola dello studente\n\r");
    scanf("%d", &s.numero_matricola);

    while(s.numero_matricola == 0)
    {
        printf("\nAttenzione! Non puoi inserire 0 come numero matricola. Riprova"); // 0 corrisponde a null

        printf("Inserisci il numero matricola dello studente\n\r");
        scanf("%d", &s.numero_matricola);
    }

    if (cercaStudente(studenti, s.numero_matricola) != NULL)
    {
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

    generaPianoStudi(&s, insegnamenti);

    var studenteGenerico = var_set(sizeof(struct Studente), &s);
    list_push_back(studenti, studenteGenerico);
    printf("\nStudente aggiunto correttamente!\n\r");
}

void aggiungiVotoAPianoStudi(struct Studente *studente, List insegnamenti)
{
    if (studente == NULL)
        return;
    
    int numero_insegnamenti = list_length_get(&insegnamenti);
    
    int scelta;
    do
    {
        printf("\nSeleziona un insegnamento da aggiungere al piano studi\n\r");
        printf("(range valori accettabili: [1, %d])\n\r", numero_insegnamenti);
        scanf("%d", &scelta);
    }
    while(scelta < 1 || scelta > numero_insegnamenti);

    int voto;
    do
    {
        struct Insegnamento *insegnamento = (struct Insegnamento*)var_get(list_element_get(&insegnamenti, scelta - 1));
        printf("\nInserisci il voto da aggiungere per %s (0 se non ancora svolto)\n\r", insegnamento->descrizione);
        printf("(range valore accettabili: [0, 30])\n\r");
        scanf("%d", &voto);
    }
    while(voto < 0 || voto > 30);

    int i;
    
    for(i = 0; i < studente->numero_esami; i++)
        if(studente->ptrPianoStudi[i].codice_insegnamento == 0)
            break;

    struct Insegnamento *insegnamento = (struct Insegnamento*)var_get(list_element_get(&insegnamenti, scelta - 1));
    studente->ptrPianoStudi[i].codice_insegnamento = insegnamento->codice_insegnamento;
    studente->ptrPianoStudi[i].voto = voto;

}

void mostraInfoStudente(struct Studente *studente)
{
    if (studente == NULL)
        return;

    system("cls");
    printf("\nNumero matricola: %d", studente->numero_matricola);
    printf("\nNome: %s", studente->nome);
    printf("\nCognome: %s", studente->cognome);
    printf("\nAnno di immatricolazione: %d", studente->anno_immatricolazione);
    printf("\nPiano di studi:");
    int i;
    for(i = 0; i < studente->numero_esami; i++)
        if(studente->ptrPianoStudi[i].codice_insegnamento != 0)
            printf("\n\tInsegnamento %d, voto: %d", studente->ptrPianoStudi[i].codice_insegnamento, studente->ptrPianoStudi[i].voto);
        else
            printf("\n\tCampo vuoto");

    printf("\n\rPremi invio per tornare al menu principale\n\r");
    getch();
}

struct Insegnamento getInsegnamento(List insegnamenti, int codice_insegnamento)
{
    int numero_insegnamenti = list_length_get(&insegnamenti);
    int i;
    for(i = 0; i < numero_insegnamenti; i++)
    {
        struct Insegnamento *insegnamentoAttuale = (struct Insegnamento*)var_get(list_element_get(&insegnamenti, i));
        if(insegnamentoAttuale->codice_insegnamento == codice_insegnamento)
            return *insegnamentoAttuale;
    }
    return EmptyInsegnamento;
}

double calcolaMediaVoti(List *studenti, List insegnamenti)
{
    int numero_studenti = list_length_get(studenti);
    int numero_insegnamenti = list_length_get(&insegnamenti);

    int sommaPesiVoti = 0;
    int sommaPesi = 0;

    int i, j;
    for(i = 0; i < numero_studenti; i++)
    {
        struct Studente *studenteAttuale = (struct Studente*)var_get(list_element_get(studenti, i));
        for(j = 0; j < studenteAttuale->numero_esami; j++)
        {
            int voto = studenteAttuale->ptrPianoStudi[j].voto;
            int peso = getInsegnamento(insegnamenti, studenteAttuale->ptrPianoStudi[j].codice_insegnamento).crediti;
            sommaPesiVoti += peso * voto;
            sommaPesi += peso;
        }
    }

    return sommaPesiVoti / sommaPesi;
}

int main ()
{
    struct Insegnamento insegnamenti[3] =
    {
        { 1, "Analisi 1", 2022, 6 },
        { 2, "Programmazione", 2022, 6 },
        { 3, "Sistemi operativi", 2022, 6 }
    };

    var insegnamentiGenerici[3] = 
    {
        var_set(sizeof(struct Insegnamento), &insegnamenti[0]),
        var_set(sizeof(struct Insegnamento), &insegnamenti[1]),
        var_set(sizeof(struct Insegnamento), &insegnamenti[2])
    };

    List listaInsegnamenti = list_from_array(3, insegnamentiGenerici);
    List listaStudenti = list_new();

    int numero_studenti;

    int choice;
    do
    {
        printf("Menu principale (versione lista):\n");
        printf("1) Aggiungi nuovo studente\n");
        printf("2) Stampa informazioni studente\n");
        printf("3) Modifica piano di studi\n");
        printf("4) Calcola media voti\n");
        printf("0) Esci\n");

        printf("Scelta: ");
        scanf("%d", &choice);

        int numero_matricola;
        switch(choice)
        {
            case 1:
                aggiungiStudente(&listaStudenti, listaInsegnamenti);
                break;
            case 2:
                printf("Inserire il numero di matricola:\n");
                scanf("%d", &numero_matricola);
                mostraInfoStudente(cercaStudente(&listaStudenti, numero_matricola));
                break;
            case 3:
                printf("Inserire il numero di matricola:\n");
                scanf("%d", &numero_matricola);
                aggiungiVotoAPianoStudi(cercaStudente(&listaStudenti, numero_matricola), listaInsegnamenti);
                break;
            case 4:
                printf("La media pesata di tutti i voti e' %f\n", calcolaMediaVoti(&listaStudenti, listaInsegnamenti));
                break;
        }
    }
    while(choice != 0);

    return 0;
}