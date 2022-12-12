#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include "utils.c"

void crea_tabellone();
void genera_tabellone();
int genera_numero_in_range();
void genera_serpenti();
void genera_scale();
void stampa_tabellone();


struct Giocatore 
{
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
    crea_tabellone();
    return 0;
}

void crea_tabellone()
 {
    int numero_caselle = 100;
    struct Casella tabellone[numero_caselle];

    genera_tabellone(tabellone, numero_caselle);

    stampa_tabellone(tabellone, numero_caselle);

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
    int num_serpenti = genera_numero_in_range(min_serpenti, max_serpenti);  // genero randomicamente un numero di serpenti tra min_serpenti e max_serpenti
    printf("Numero serpenti: %d", num_serpenti);

    genera_serpenti(tabellone, numero_caselle, num_serpenti);  // Genero i serpenti sul tabellone

    int max_scale = 10; // numero massimo di scale
    int min_scale = 4;  // numero minimo di scale
    int num_scale = genera_numero_in_range(min_scale, max_scale); // genero randomicamente un numero di scale tra min_scale e max_scale
    printf("\nNumero scale: %d\r\n", num_serpenti);

    genera_scale(tabellone, numero_caselle, num_scale);
}

void genera_serpenti(struct Casella* tabellone, int numero_caselle, int numero_serpenti) 
{
    int indice_casella = 0; // Indice della casella per cui sto generando l'effetto
    int indice_coda = 0;    // Indice della coda di tabellone[indice_casella]. Ogni serpente e scala ha una coda e una testa
    int effetto = 0, max_effetto = 0, min_effetto = 0;

    for(int i = 0; i < numero_serpenti; i++)
     {
        do 
        {
            do 
            {
                indice_casella = genera_numero_in_range(1, numero_caselle - 2);  // genero un indice_casella randomico compreso tra 1 e numero_caselle - 2 (perché la prima casella è la partenza e l'ultima è la vincita)
            } 
            while (tabellone[indice_casella].effetto != 0);   // Genera finché non trovi un posto non occupato da serpenti o scale

            max_effetto = -1;   // L'effetto serpente per esistere deve far scendere i giocatori di almeno 1 posizione
            min_effetto = -indice_casella;  // Il serpente non può sforare inferiormente il tabellone

            effetto = genera_numero_in_range(min_effetto, max_effetto); // genero randomicamente il valore dell'effetto tra min_effetto e max_effetto

            indice_coda = indice_casella - abs(effetto); // ottengo l'indice della casella della coda del serpente; uso abs(x) perché l'effetto è negativo

        } 
        while (tabellone[indice_coda].effetto != 0);  // Rigenero un nuovo indice_casella e di conseguenza un indice_coda finché non trovo una coda libera (non occupata da serpenti o scale)

        tabellone[indice_casella].effetto = effetto;    // assegno l'effetto generato
    }
}

void genera_scale(struct Casella* tabellone, int numero_caselle, int numero_scale) 
{
    int indice_casella = 0; // Indice della casella per cui sto generando l'effetto
    int indice_testa = 0;    // Indice della testa di tabellone[indice_casella]. La testa della scala è la posizione tabellone[indice_testa] dove il giocatore arrivera dopo aver salito le scale
    int effetto = 0, max_effetto = 0, min_effetto = 0;

    for(int i = 0; i < numero_scale; i++) 
    {
        do 
        {
            do 
            {
                indice_casella = genera_numero_in_range(1,  numero_caselle - 2);  // genero un indice_casella randomico compreso tra 1 e numero_caselle - 2 (perché la prima casella è la partenza e l'ultima è la vincita)
            } 
            while (tabellone[indice_casella].effetto == 0);   // Genera finché non trovi un posto non occupato da serpenti o scale

            max_effetto = numero_caselle - indice_casella;   // La scala non può sforare superiormente la tabella
            min_effetto = 1;  // La scala per esistere deve avere grandezza almeno 1


            effetto = genera_numero_in_range(min_effetto, max_effetto); // genero randomicamente il valore dell'effetto tra min_effetto e max_effetto

            indice_testa = indice_casella + effetto; // ottengo l'indice della casella della testa della scala

        } 
        while (tabellone[indice_testa].effetto != 0);  // Rigenero un nuovo indice_casella e di conseguenza un indice_testa finché non trovo una testa libera (non occupata da serpenti o scale)

        tabellone[indice_casella].effetto = effetto;    // assegno l'effetto generato
    }
}


int genera_numero_in_range(int min, int max) 
{
    int numero = (rand() % (max - min + 1)) + min;

    return numero;
}

void stampa_tabellone(struct Casella* tabellone, int numero_caselle) 
{
    printf("\nTabellone effetti");
    for(int i = 0; i < numero_caselle; i++)    // Stampo il tabellone con partenza che corrisonde a t[0][0] e fine t[10][10]
    {
        if ((i % 10) == 0) 
        {
            printf("\n");
        }
        printf("[%03+d]", tabellone[i].effetto);
    }
    printf("\n\n");

    printf("\nTabellone con numeri delle caselle");
    for(int i = 0; i < numero_caselle; i++)    // Stampo il tabellone con partenza che corrisonde a t[0][0] e fine t[10][10]
    {
        if ((i % 10) == 0) 
        {
            printf("\n");
        }
        printf("[%03d]", tabellone[i].numero);
    }
}
struct Array* string_read(char *path)
{
    struct Array *stringArray;
    struct Array buffer;
    FILE *stream = fopen(path,"r");
    if(stream == NULL)
        return 1;

    while(fgets(buffer.array, buffer.n, stream))
    {
        printf(buffer.array);
    }
    fclose(stream);

}