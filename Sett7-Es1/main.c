#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>
#include <ctype.h>
void menu();
void robConnect();
int robConfig();
int verificaDuplicato();
void azzeraStruct();
void mostraInfoStanza();
void aggiungiStanza();
void modificaStanza();
void calcolaPercorso();
void selectionSort();
void swap();
void robDisconnect();
struct Stanza {
    char nome[20];
    int larghezza;
    int lunghezza;
    int area;
    int ostacoli;
    int priorita;
};

int main() {

    //int numero_stanze = 5;
    //robConnect();    // connettiti al robot (loading)
    int numero_stanze = robConfig(); // uso robConfig() per chiedere all'utente il numero di stanze

    struct Stanza *ptrStanza = (struct Stanza *) malloc(numero_stanze * sizeof(struct Stanza));
    azzeraStruct(ptrStanza, numero_stanze);

    menu(ptrStanza, numero_stanze);


    return 0;
}

void robConnect() { // Funzione che simula l'effetto di caricamento
    
    int percentage = 0;
    char loading[] = "--------------------";
    
   while (percentage <= 100) {
       printf("\t\tConnessione a Rob8");
       printf("\n\t\t");

       for (int i = 0; i < strlen(loading); i++) {
           printf("%c", loading[i]);
       }
       
       loading[percentage/5] = 'o';
       
       printf(" %d%%", percentage);
       
       percentage += 5;
       
       usleep(50 * 1000);    // 50 millisecondi (50*1000 microsecondi)
       system("cls");
   }
}

void menu(struct Stanza *ptrStanza, int numero_stanze) {    // Menù principale che consente all'utente di scegliere tra le varie opzioni di rob8
    int scelta;
    do {
        system("cls");
        printf("------ Menu principale di Rob8 ------");
        printf("\nScegli una opzione inserendo il numero corrispondente a sinistra di ogni opzione");
        printf("\n\n");
        printf("0. Aggiungi una stanza");
        printf("\n1. Mostra informazioni di una stanza");
        printf("\n2. Modifica una stanza");
        printf("\n3. Calcola il percorso");
        printf("\n\n4. Disconnettiti dal Rob8\r\n");

        scanf("%d", &scelta);

        switch(scelta) {
            case 4:
                robDisconnect();
                break;
            case 0:
                aggiungiStanza(ptrStanza, numero_stanze);
                break;
            case 1:
                mostraInfoStanza(ptrStanza, numero_stanze);
                break;
            case 2:
                modificaStanza(ptrStanza, numero_stanze);
                break;
            case 3:
                calcolaPercorso(ptrStanza, numero_stanze);
                break;
        }
    }
    while(1);
}

int robConfig() {   // Funzione che chiede all'utente quante stanze ci sono nella casa e torna il loro numero
    int numero_stanze;

    printf("Benvenuto nella pagina di configurazione di Rob8");
    printf("\nInserisci il numero di stanze presenti nella tua casa\r\n");
    scanf("%d", &numero_stanze);
    system("cls");


    return numero_stanze;
}

void aggiungiStanza(struct Stanza *ptrStanza, int numero_stanze) {
    system("cls");
    int flag = 0;
    int i = 0;
    for (i = 0; i < numero_stanze; i++) {
        if (strcmp(ptrStanza[i].nome, "") == 0) {
            flag = 1;   // trovato un posto libero "i"
            break;
        }
    }

    if (flag == 0) {
        printf("Attenzione: il vettore di stanze e completo. Non si possono aggiungere ulteriori stanze");
        printf("\nPremi invio per tornare al menu principale");
        getch();
        return;
    }

    struct Stanza s;
    printf("Inserisci il nome della stanza\n\r");
    scanf("%s", &s.nome);

    if (verificaDuplicato(*ptrStanza, numero_stanze, s.nome) == 1){
        printf("\nErrore: la stanza inserita e gia presente!");
        return;
    }

    printf("\nInserisci la larghezza della stanza\n\r");
    scanf("%d", &s.larghezza);

    printf("\nInserisci la lunghezza della stanza\n\r");
    scanf("%d", &s.lunghezza);

    printf("\nInserisci l'area della stanza\n\r");
    scanf("%d", &s.area);

    printf("\nInserisci il numero di ostacoli della stanza\n\r");
    scanf("%d", &s.ostacoli);

    printf("\nInserisci la priorita di pulizia della stanza\n\r");
    scanf("%d", &s.priorita);

    ptrStanza[i] = s;   // i è l'indice della struttura non occupata

    system("cls");
    printf("L'inserimento della stanza e avvenuto con successo. Premi invio per tornare al menu principale\n\r");
    getch();

    //calcolaPriorita?

}

void modificaStanza(struct Stanza *ptrStanza, int numero_stanze) {   // Funzione che dato il nome della stanza consente di modificare le informazioni di essa
    char nomeStanza[20];

    system("cls");
    printf("Inserisci il nome della stanza della quale vuoi stampare le informazioni\r\n");
    scanf("%s", &nomeStanza);

    int indiceStanza = 0;
    int flag = 0;
    for(indiceStanza = 0; indiceStanza < numero_stanze; indiceStanza++) {
        if (strcmp(nomeStanza, ptrStanza[indiceStanza].nome) == 0){    // Cerco la stanza con il nome inserito dall'utente
            flag = 1;   // è stata trovata una stanza di indiceStanza con il nome inserito
            break;
        }
    }

    if (flag == 0) {
        printf("\nNon e stata trovata una stanza con il nome inserito. Premi invio per continuare\r\n");
        getch();
        return;
    }

    int scelta = 0;
    do {
        system("cls");
        printf("Modifica le informazioni della stanza inserendo il numero corrispondente a sinistra");

        printf("\n0. Nome: %s", ptrStanza[indiceStanza].nome);
        printf("\n1. Larghezza: %d", ptrStanza[indiceStanza].larghezza);
        printf("\n2. Lunghezza: %d", ptrStanza[indiceStanza].lunghezza);
        printf("\n3. Area: %d", ptrStanza[indiceStanza].area);
        printf("\n4. Ostacoli: %d", ptrStanza[indiceStanza].ostacoli);
        printf("\n5. Priorita: %d", ptrStanza[indiceStanza].priorita);

        printf("\n\n6. Torna nel menu principale\r\n");

        scanf("%d", &scelta);

        system("cls");
        switch(scelta) {
            case 6: // Se la scelta è 6, torna direttamente nel menu principale
                return;
            case 0:
                printf("Inserisci il nome della stanza\r\n");
                scanf("%s", &ptrStanza[indiceStanza].nome);
                break;
            case 1:
                printf("Inserisci la larghezza della stanza\r\n");
                scanf("%d", &ptrStanza[indiceStanza].larghezza);
                break;
            case 2:
                printf("Inserisci la lunghezza della stanza\r\n");
                scanf("%d", &ptrStanza[indiceStanza].lunghezza);
                break;
            case 3:
                printf("Inserisci l'area della stanza\r\n");
                scanf("%d", &ptrStanza[indiceStanza].area);
                break;
            case 4:
                printf("Inserisci il numero di ostacoli nella stanza\r\n");
                scanf("%d", &ptrStanza[indiceStanza].ostacoli);
                break;
            case 5:
                printf("Inserisci la priorita della stanza\r\n");
                scanf("%d", &ptrStanza[indiceStanza].priorita);
                break;
            default:
                return;
        }
    }
    while(1);
}

void mostraInfoStanza(struct Stanza *ptrStanza, int numero_stanze) { // Funzione che stampa le informazioni di una stanza dato il nome
    char nomeStanza[20];

    system("cls");
    printf("Inserisci il nome della stanza della quale vuoi stampare le informazioni\r\n");
    scanf("%s", &nomeStanza);

    int indiceStanza = 0;
    int flag = 0;
    for(indiceStanza = 0; indiceStanza < numero_stanze; indiceStanza++) {
        if (strcmp(nomeStanza, ptrStanza[indiceStanza].nome) == 0){    // Cerco la stanza con il nome inserito dall'utente
            flag = 1;   // è stata trovata una stanza di indice i con il nome inserito
            break;
        }
    }

    if (flag == 0) {
        printf("\nNon e stata trovata una stanza con il nome inserito. Premi invio per continuare\r\n");
        getch();
        return;
    }
    system("cls");
    printf("\nNome: %s", ptrStanza[indiceStanza].nome);
    printf("\nStanza numero: %d", indiceStanza);
    printf("\nLarghezza: %d", ptrStanza[indiceStanza].larghezza);
    printf("\nLunghezza: %d", ptrStanza[indiceStanza].lunghezza);
    printf("\nArea: %d", ptrStanza[indiceStanza].area);
    printf("\nOstacoli: %d", ptrStanza[indiceStanza].ostacoli);
    printf("\nPriorita: %d", ptrStanza[indiceStanza].priorita);

    printf("\n\rPremi invio per tornare al menu principale\n\r");
    getch();


}

void calcolaPercorso(struct Stanza *ptrStanza, int numero_stanze) {
    selectionSort(ptrStanza, numero_stanze);

    system("cls");
    printf("Percorso di pulizia");
    for(int i = 0; i < numero_stanze; i++) {
        if(strcmp(ptrStanza[i].nome, "") != 0)
            printf("\n--> Stanza: %s\tPriorita: %d -->", ptrStanza[i].nome, ptrStanza[i].priorita);
    }

    printf("\nPremi invio per tornare al menu principale.");
    getch();
}

void selectionSort(struct Stanza *ptrStanza, int numero_stanze) {
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < numero_stanze - 1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < numero_stanze; j++)
            if (ptrStanza[j].priorita < ptrStanza[min_idx].priorita)
                min_idx = j;

        // Swap the found minimum element with the first element
        if(min_idx != i)
            swap(&ptrStanza[min_idx], &ptrStanza[i]);
    }
}

void swap(struct Stanza *s1, struct Stanza *s2) {
    struct Stanza temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}



int verificaDuplicato(struct Stanza *ptrStanza, int numero_stanze, char nome[]) {   // Funzione che dato il nome della stanza controlla se ci sono duplicati
    int flag = 0;
    for(int i = 0; i < numero_stanze; i++) {
        if (strcmp(ptrStanza[i].nome, nome) == 0) {
            return 1;   // esiste un duplicato
        }
    }

    return 0;   // non ci sono duplicati
}

void azzeraStruct(struct Stanza *ptrStanza, int numero_stanze) {    // mette a 0 tutti gli elementi nella struct ("" per le stringhe)
    for (int i = 0; i < numero_stanze; i++) {
        strcpy(ptrStanza[i].nome, "");  // corrisponde a ptrStanza[i].nome = ""; che pero non si puo fare
        ptrStanza[i].larghezza = 0;
        ptrStanza[i].lunghezza = 0;
        ptrStanza[i].area = 0;
        ptrStanza[i].ostacoli = 0;
        ptrStanza[i].priorita = 0;
    }
}

void robDisconnect(){
    system("cls");
    printf("Disconnessione avvenuta con successo.");
    exit(0); //programma terminato correttamente
}
