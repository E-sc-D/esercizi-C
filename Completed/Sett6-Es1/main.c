#include <stdio.h>

// Un-comment for the alternate version with a jagged array instead of an array of structs
// #define RUBRICA_FRASTAGLIATA

#ifdef RUBRICA_FRASTAGLIATA
    #include "rubricaFrastagliata.c"
#else
    #include "rubricaBella.c"
#endif

#define INPUT_MAX_LENGTH 50

void AggiungiNuovoContatto(struct Rubrica* rubrica)
{

    char nome[INPUT_MAX_LENGTH];
    char cognome[INPUT_MAX_LENGTH];
    char numeroTelefonico[INPUT_MAX_LENGTH];

    printf("\nAggiunta nuovo contatto\n");
    printf("Inserisci il nome (max %d caratteri): ", INPUT_MAX_LENGTH);
    scanf("%s", &nome);
    printf("Inserisci il cognome (max %d caratteri): ", INPUT_MAX_LENGTH);
    scanf("%s", &cognome);
    printf("Inserisci il numero telefonico (max %d caratteri): ", INPUT_MAX_LENGTH);
    scanf("%s", &numeroTelefonico);

#ifdef RUBRICA_FRASTAGLIATA
    char nuovoContatto[3][FIELD_MAX_LENGTH];
    strcpy(nuovoContatto[0], nome);
    strcpy(nuovoContatto[1], cognome);
    strcpy(nuovoContatto[2], numeroTelefonico);
#else
    struct Contatto nuovoContatto;
    strcpy(nuovoContatto.Nome, nome);
    strcpy(nuovoContatto.Cognome, cognome);
    strcpy(nuovoContatto.NumeroTelefonico, numeroTelefonico);
#endif
    if(AddContatto(rubrica, nuovoContatto))
        printf("Contatto aggiunto con successo!\n");
    else
        printf("Si e' verificato un errore\n");
}

void RicercaEsattaContatto(struct Rubrica* rubrica)
{
    char keyword[INPUT_MAX_LENGTH];

    printf("\nRicerca esatta contatto\n");
    printf("Inserisci il termine da cercare (max %d caratteri): ", INPUT_MAX_LENGTH);
    scanf("%s", &keyword);

    int index = SearchContatto(rubrica, keyword, true);
    if(index != -1)
        printf("Contatto trovato:\n%s\n", ContattoToString(rubrica->Contatti[index]));
    else
        printf("Nessun risultato trovato\n");
}

void RicercaApprossimataContatto(struct Rubrica* rubrica)
{
    char keyword[INPUT_MAX_LENGTH];

    printf("\nRicerca approssimata contatto\n");
    printf("Inserisci il termine da cercare (max %d caratteri): ", INPUT_MAX_LENGTH);
    scanf("%s", &keyword);

    int index = SearchContatto(rubrica, keyword, false);
    printf("Contatto trovato:\n%s\n", ContattoToString(rubrica->Contatti[index]));
}

void StampaCompletaRubrica(struct Rubrica* rubrica)
{
    printf("\nStampa completa della rubrica\n");
    printf("%s", RubricaToString(rubrica));
}

int main()
{
#ifdef RUBRICA_FRASTAGLIATA
    struct Rubrica rubrica;
    InitializeRubrica(&rubrica);
#else
    struct Rubrica rubrica = NewRubrica(); // Technically needed, but apparently not (more details in "rubrica.c")
#endif

    char choice = '0';
    do
    {
        printf("\n");
#ifdef RUBRICA_FRASTAGLIATA
        printf("Menu principale (rubrica frastagliata)\n");
#else
        printf("Menu principale (rubrica struct)\n");
#endif
        printf("1) Aggiungi nuova voce in rubrica\n");
        printf("2) Ricerca esatta\n");
        printf("3) Ricerca approssimata\n");
        printf("4) Stampa completa\n");
        printf("0) Esci\n");

        printf("Scelta: ");
        scanf("\n%c", &choice);

        switch(choice)
        {
            case '1':
                AggiungiNuovoContatto(&rubrica);
                break;
            case '2':
                RicercaEsattaContatto(&rubrica);
                break;
            case '3':
                RicercaApprossimataContatto(&rubrica);
                break;
            case '4':
                StampaCompletaRubrica(&rubrica);
                break;
        }
    } while (choice != '0');

    return 0;
}