#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void robConnect();
int robConfig();
int verificaDuplicato();
void azzeraStruct();
void mostraInfoStanza();
struct Stanza {
    char nome[20];
    int larghezza;
    int lunghezza;
    int area;
    int ostacoli;
    int priorita;
};

int main() {

    int numero_stanze = 5;
    //robConnect();    // connettiti al robot (loading)
    //int numero_stanze = robConfig(); // uso robConfig() per chiedere all'utente il numero di stanze

    struct Stanza *ptrStanza = (struct Stanza *) malloc(numero_stanze * sizeof(struct Stanza));

    azzeraStruct(ptrStanza, numero_stanze);

    mostraInfoStanza("", *ptrStanza, numero_stanze);




    return 0;
}

void robConnect() { // Funzione che simula l'effetto di caricamento
    printf("\t\tConnessione a Rob8");
    printf("\n\t\t");

    int percentage = 0;
    char loading[] = "--------------------";
    printf("%s %d%%", loading, percentage);
    for(int i = 0; i < strlen(loading); i++) {
        //printf("\33[2K\r");
        loading[i] = 'o';
        percentage = (i + 1) * 5;
        printf("\n\t\t");
        printf("%s %d%%", loading, percentage);
        usleep(50*1000);    // 50 milisecondi (50*1000 microsecondi)
    }
}

int robConfig() {   // Funzione che chiede all'utente quante stanze ci sono nella casa e torna il loro numero
    int numero_stanze;

    printf("\nBenvenuto nella pagina di configurazione");
    printf("\nInserisci il numero di stanze presenti nella tua casa");
    scanf("%d", &numero_stanze);


    return numero_stanze;
}


void aggiungiStanza(struct Stanza *ptrStanza, int numero_stanze) {
    struct Stanza s;
    printf("Inserisci il nome della stanza");
    scanf("%s", &s.nome);

    if (verificaDuplicato(*ptrStanza, numero_stanze, s.nome) == 1){
        printf("\nErrore: la stanza inserita e gia presente!");
        return;
    }

    printf("\nInserisci la larghezza della stanza");
    scanf("%d", &s.larghezza);

    printf("\nInserisci la lunghezza della stanza");
    scanf("%d", &s.lunghezza);

    printf("\nInserisci l'area della stanza");
    scanf("%d", &s.area);

    printf("\nInserisci il numero di ostacoli della stanza");
    scanf("%d", &s.ostacoli);

    printf("\nInserisci la priorita di pulizia della stanza");
    scanf("%d", &s.priorita);

    //calcolaPriorita?

}

void mostraInfoStanza(char nomeStanza[], struct Stanza *ptrStanza, int numero_stanze) {
    int i = 0;
    int flag = 0;
    for(i = 0; i < numero_stanze; i++) {
        if (strcmp(nomeStanza, ptrStanza[i].nome) == 0){    // Cerco la stanza con il nome inserito dall'utente
            flag = 1;
            break;
        }
    }

    if (flag == 0) {
        printf("\nNon e stata trovata una stanza con il nome inserito");
        return;
    }



    printf("\nStanza numero: %d", i);
    printf("\nNome: %s", ptrStanza[i].nome);
    printf("\nLarghezza: %d", ptrStanza[i].larghezza);
    printf("\nLunghezza: %d", ptrStanza[i].lunghezza);
    printf("\nArea: %d", ptrStanza[i].area);
    printf("\nOstacoli: %d", ptrStanza[i].ostacoli);
    printf("\nPriorita: %d", ptrStanza[i].priorita);
}

int verificaDuplicato(struct Stanza *ptrStanza, int numero_stanze, char nome[]) {
    int flag = 0;
    for(int i = 0; i < numero_stanze; i++) {
        if (strcmp(ptrStanza[i].nome, nome) == 0) {
            return 1;   // esiste un duplicato
        }
    }

    return 0;   // non ci sono duplicati
}

void azzeraStruct(struct Stanza *ptrStanza, int numero_stanze) {
    for (int i = 0; i < numero_stanze; i++) {
        strcpy(ptrStanza[i].nome, "");  // corrisponde a ptrStanza[i].nome = ""; che pero non si puo fare
        ptrStanza[i].larghezza = 0;
        ptrStanza[i].lunghezza = 0;
        ptrStanza[i].area = 0;
        ptrStanza[i].ostacoli = 0;
        ptrStanza[i].priorita = 0;
    }
}