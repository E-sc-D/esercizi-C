#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include "utils.c"
#include "dataCollection.c"
#include "list.c"


struct Casella* crea_tabellone();
void genera_tabellone();
int genera_numero_in_range();
void genera_serpenti();
void genera_scale();
struct Giocatore* istanzia_giocatori();
void stampa_tabellone();
struct RigaDiTesto string_read();
void gioca_snakes_and_ladders();
int lancia_dado();
void print_table();
void stampa_posizione_giocatori();

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"


struct RigaDiTesto
{
    struct StringArray* array;
    int len;
};

struct Giocatore
{
    int id;
    int posizione; // posizione del giocatore sulla tabella
    char simbolo;   // simbolo con cui verrà identificato il giocatore sulla tavola
};

struct Casella
{
    int numero; // numero della casella
    int effetto;    // L'effetto può essere andare avanti oppure indietro, per es (+6 posizioni oppure -10). Se è 0 indica che non ha nessun effetto
};

int main() 
{
    srand(time(NULL));

    gioca_snakes_and_ladders(3);

    return 0;
}

void gioca_snakes_and_ladders(int numero_giocatori) {
    int numero_caselle = 100;
    struct Casella* tabellone = crea_tabellone();   // creo un tabellone e lo riempio di snakes and ladders
    struct Giocatore* giocatori = istanzia_giocatori(numero_giocatori); // creo i giocatori e assegno la loro posizione a 0

    char path[] = ".\\FileDomande.txt";
    struct RigaDiTesto domande = string_read(path);
    printf("%d", domande.len);
    
    strcpy(path, ".\\FileRisposte.txt");
    struct RigaDiTesto risposte = string_read(path);

    int dado = 0;

    //struct Array *coda_giocatori = NULL;
    List coda_giocatori;
    coda_giocatori = list_new(); // istanzio la coda

    for (int i = 0; i < numero_giocatori; i++) {
        var indice;
        indice = var_set_int(i);
        list_push_back(&coda_giocatori, indice);    // Inserisco l'indice dei giocatori nella coda
    }

    int indice_giocatore_attuale = 0;
    struct Giocatore* giocatore_attuale = NULL;
    int c;
    int indice_domanda = 0;
    char risposta[15];
    //  Turno
    do {
        //system("cls");
        stampa_tabellone(tabellone, numero_caselle);
        stampa_posizione_giocatori(giocatori, numero_giocatori);

        indice_giocatore_attuale = var_get_int(list_pop_front(&coda_giocatori)); // ottengo l'indice del giocatore facendo pop della coda
        giocatore_attuale = &giocatori[indice_giocatore_attuale]; // assegno a giocatore_attuale l'indirizzo del giocatore in turno nella struttura giocatori

        printf("\n\nGiocatore in turno: %d", giocatore_attuale->id);
        printf("\nInserisci invio per lanciare il dado");
        while( getchar() != '\n' );
        dado = lancia_dado();
        //print_table(tabellone, numero_caselle, giocatori, numero_giocatori);
        if ((giocatore_attuale->posizione + dado) >= 99) {
            //il giocatore ha vinto
            giocatore_attuale-> posizione = 99;

            printf(ANSI_COLOR_GREEN "Lanciando il dado il giocatore %d si muove di %d posti e arriva alla fine e VINCE", giocatore_attuale->id, dado);
            printf(ANSI_COLOR_RESET);

            exit(0);
            break;
        }

        giocatore_attuale->posizione += dado;    // aumento la posizione del giocatore di dado posti

        system("cls");
        if(tabellone[giocatore_attuale->posizione].effetto == 0) {
            printf(ANSI_COLOR_YELLOW "Lanciando il dado il giocatore %d e salito di %d posti", giocatore_attuale->id, dado);
            printf(ANSI_COLOR_RESET);
            printf("\nInserisci invio per continuare");
            while( getchar() != '\n' );
        }
        else if (tabellone[giocatore_attuale->posizione].effetto > 0) {
            printf(ANSI_COLOR_GREEN "Lanciando il dado il giocatore %d si muove di %d posti e arriva a una scala", giocatore_attuale->id, dado);
            printf(ANSI_COLOR_RESET);

            printf("\nRispondi correttamente a questa domanda per salire di %d posti", tabellone[giocatore_attuale->posizione].effetto);
            indice_domanda = 0;
            printf("\n%s", domande.array[indice_domanda].array);
            fgets(risposta, sizeof(risposta), stdin);

            if(strcmp(risposte.array[indice_domanda].array, risposta) == 0) { // Se la risposta data equivale a quella salvata nel testo
                printf(ANSI_COLOR_GREEN "Complimenti, hai risposto bene. Il giocatore %d sale di %d posti", giocatore_attuale->id, tabellone[giocatore_attuale->posizione].effetto);
                printf(ANSI_COLOR_RESET);
                giocatore_attuale->posizione += tabellone[giocatore_attuale->posizione].effetto;
            } else {
                printf(ANSI_COLOR_YELLOW "Mi dispiace hai risposto male. Il giocatore %d rimane sulla posizione %d", giocatore_attuale->id, giocatore_attuale->posizione);
                printf(ANSI_COLOR_RESET);
            }

            printf("\nInserisci invio per continuare");
            while( getchar() != '\n' );

        } else if (tabellone[giocatore_attuale->posizione].effetto < 0){
            printf(ANSI_COLOR_RED "Lanciando il dado il giocatore %d e entrato nella bocca di un serpente e sceso di %d posti", giocatore_attuale->id, tabellone[giocatore_attuale->posizione].effetto);
            printf(ANSI_COLOR_RESET);

            printf("\nInserisci invio per continuare");
            while( getchar() != '\n' );

            giocatore_attuale->posizione += tabellone[giocatore_attuale->posizione].effetto;
        }

        list_push_back(&coda_giocatori, var_set_int(indice_giocatore_attuale)); // rimetto il giocatore nella coda
    } while (giocatore_attuale->posizione != 99);
}

struct Casella* crea_tabellone()
{
    int numero_caselle = 100;
    struct Casella* tabellone = (struct Casella*) malloc(numero_caselle * sizeof(struct Casella));

    genera_tabellone(tabellone, numero_caselle);

    //stampa_tabellone(tabellone, numero_caselle);

    return tabellone;

}

void genera_tabellone(struct Casella *tabellone, int numero_caselle) // Questo metodo genera il tabellone e assegna quindi anche quali caselle sono scivoli e quali scale
{
    int contatore = 1;
    for(int i = 0; i < numero_caselle; i++)   // Scorro l'array di caselle
    {
        tabellone[i].numero = contatore;    // Assegno il numero a ogni casella partendo da 1
        contatore++;

        tabellone[i].effetto = 0;   // Azzero gli effetti di ogni casella
    }

    int max_serpenti = 10; //  numero massimo di serpenti
    int min_serpenti = 4;  // numero minimo di serpenti
    int num_serpenti;
    num_serpenti = genera_numero_in_range(min_serpenti, max_serpenti);  // genero randomicamente un numero di serpenti tra min_serpenti e max_serpenti
    printf("Numero serpenti: %d", num_serpenti);

    genera_serpenti(tabellone, numero_caselle, num_serpenti);  // Genero i serpenti sul tabellone

    int max_scale = 10; // numero massimo di scale
    int min_scale = 4;  // numero minimo di scale
    int num_scale;
    num_scale = genera_numero_in_range(min_scale, max_scale); // genero randomicamente un numero di scale tra min_scale e max_scale
    printf("\nNumero scale: %d\r\n", num_scale);

    genera_scale(tabellone, numero_caselle, num_scale);
}

void genera_serpenti(struct Casella* tabellone, int numero_caselle, int numero_serpenti)
{
    int indice_casella = 0; // Indice della casella per cui sto generando l'effetto
    int indice_coda = 0;    // Indice della coda di tabellone[indice_casella]. Ogni serpente e scala ha una coda e una testa
    int effetto = 0, max_effetto = 0, min_effetto = 0;

    for(int i = 0; i < numero_serpenti; i++) {
        do {
            do {
                indice_casella = genera_numero_in_range(1, numero_caselle - 2);  // genero un indice_casella randomico compreso tra 1 e numero_caselle - 2 (perché la prima casella è la partenza e l'ultima è la vincita)
            } while (tabellone[indice_casella].effetto != 0);   // Genera finché non trovi un posto non occupato da serpenti o scale

            max_effetto = -1;   // L'effetto serpente per esistere deve far scendere i giocatori di almeno 1 posizione
            min_effetto = -indice_casella;  // Il serpente non può sforare inferiormente il tabellone


            effetto = genera_numero_in_range(min_effetto, max_effetto); // genero randomicamente il valore dell'effetto tra min_effetto e max_effetto

            indice_coda = indice_casella - abs(effetto); // ottengo l'indice della casella della coda del serpente; uso abs(x) perché l'effetto è negativo

        } while (tabellone[indice_coda].effetto != 0);  // Rigenero un nuovo indice_casella e di conseguenza un indice_coda finché non trovo una coda libera (non occupata da serpenti o scale)

        tabellone[indice_casella].effetto = effetto;    // assegno l'effetto generato
    }
}

void genera_scale(struct Casella* tabellone, int numero_caselle, int numero_scale)
{
    int indice_casella = 0; // Indice della casella per cui sto generando l'effetto
    int indice_testa = 0;    // Indice della testa di tabellone[indice_casella]. La testa della scala è la posizione tabellone[indice_testa] dove il giocatore arrivera dopo aver salito le scale
    int effetto = 0, max_effetto = 0, min_effetto = 0;

    for(int i = 0; i < numero_scale; i++) {
        do {
            do {
                indice_casella = genera_numero_in_range(1,  numero_caselle - 2);  // genero un indice_casella randomico compreso tra 1 e numero_caselle - 2 (perché la prima casella è la partenza e l'ultima è la vincita)
            } while (tabellone[indice_casella].effetto == 0);   // Genera finché non trovi un posto non occupato da serpenti o scale

            max_effetto = numero_caselle - indice_casella;   // La scala non può sforare superiormente la tabella
            min_effetto = 1;  // La scala per esistere deve avere grandezza almeno 1


            effetto = genera_numero_in_range(min_effetto, max_effetto); // genero randomicamente il valore dell'effetto tra min_effetto e max_effetto

            indice_testa = indice_casella + effetto; // ottengo l'indice della casella della testa della scala

        } while (tabellone[indice_testa].effetto != 0);  // Rigenero un nuovo indice_casella e di conseguenza un indice_testa finché non trovo una testa libera (non occupata da serpenti o scale)

        tabellone[indice_casella].effetto = effetto;    // assegno l'effetto generato
    }
}

int genera_numero_in_range(int min, int max)
{
    int numero = (rand() % (max - min + 1)) + min;

    return numero;
}

struct Giocatore* istanzia_giocatori(int numero_giocatori) {    //creo i giocatori e assegno la loro posizione a 0
    struct Giocatore* giocatori = (struct Giocatore*) malloc(numero_giocatori * sizeof(struct Giocatore));

    for(int i = 0; i < numero_giocatori; i++) {
        giocatori[i].id = i;
        giocatori[i].posizione = 0;
    }

    return giocatori;
}


void stampa_tabellone(struct Casella* tabellone, int numero_caselle)
{
   /*printf("\nTabellone effetti");
    for(int i = 0; i < numero_caselle; i++)    // Stampo il tabellone con partenza che corrisonde a t[0][0] e fine t[10][10]
    {
        if ((i % 10) == 0)
        {
            printf("\n");
        }
        printf("[%03+d]", tabellone[i].effetto);
    }
    printf("\n\n");
    */
    printf("\nTabellone con numeri delle caselle");
    for(int i = 0; i < numero_caselle; i++)    // Stampo il tabellone con partenza che corrisonde a t[0][0] e fine t[9][9]
    {
        if ((i % 10) == 0)
        {
            printf("\n");
        }

        if(tabellone[i].effetto > 0)
            printf(ANSI_COLOR_GREEN);
        else if (tabellone[i].effetto < 0)
            printf(ANSI_COLOR_RED);
        printf("[%03d]", i);
        printf(ANSI_COLOR_RESET);
    }
}

void stampa_posizione_giocatori(struct Giocatore* giocatori, int numero_giocatori) {

    printf("\n-------- Posizione giocatori --------");
    for(int i = 0; i < numero_giocatori; i++) {
        printf("\nGiocatore %d: %d", giocatori[i].id, giocatori[i].posizione);
    }
}

struct RigaDiTesto string_read(char *path)
{
    struct RigaDiTesto rigaditesto;
    char array[1000];
    FILE *stream = fopen(path,"r");
    int count = 0;
    char c;

    if(stream == NULL)
    {
        printf("file non trovato o path sbagliato");
        return;
    }

     while(fgets(array, 1000, stream))//contiamo il numero di righe
    {
        count++;
    }  

    rigaditesto.array = malloc(sizeof(struct StringArray) * count);//allochiamo l'array di stringhe
    rewind(stream);//riportiamo indietro il puntatore del lettore di file
    int i = 0;

    while(fgets(array, 1000, stream))//ogni giro legge una riga e la salva dentro l'array di stringhe
    {
        (rigaditesto.array[i]).array = malloc(StringLen(array)*sizeof(char));//malloca la stringa da salvare
        (rigaditesto.array[i]).n = StringLen(array);//stringlen conta i caratteri fino a quando non trova \0
        strcpy((rigaditesto.array[i]).array,array);
        i++;
    }  
    rigaditesto.len = count;
    fclose(stream);
    return rigaditesto;
}

int lancia_dado() {
    int dado = genera_numero_in_range(1,6);
    return dado;
}

void print_table(struct Casella* tabellone, int numero_caselle, struct Giocatore* giocatori, int numero_giocatori)
{
    char cornersChar = '+', rowsChar = '-', columnsChar = '|';
    int innerCellWidth = 3, innerCellHeight = 3, tableWidth = 10, tableHeight = 10;
    int cellWidth = innerCellWidth + 1;
    int cellHeight = innerCellHeight + 1;
    int cont = 0;

    for(int y = 0; y <= (tableHeight * cellHeight); y++)
    {
        for(int x = 0; x <= (tableWidth * cellWidth); x++)
        {
            if(x % cellWidth == 0 && y % cellHeight == 0) // Cell corners
            {
                printf("%c", cornersChar);
            }
            else if(y % cellHeight == 0) // Rows
            {
                printf("%c", rowsChar);
            }
            else if(x % cellWidth == 0) // Columns
            {
                printf("%c", columnsChar);
            }
            else // Cell inside
            {
                printf("%d", tabellone[cont]);
                cont++;
            }
        }
        printf("\n");
    }
}