#include <stdio.h>
#include "rubrica.c"

#define KEYWORD_MAX_LENGTH 50

void AggiungiNuovoContatto(struct Rubrica* rubrica)
{
    struct Contatto nuovoContatto;

    printf("\nAggiunta nuovo contatto\n");
    printf("Inserisci il nome (max %d caratteri): ", NOME_MAX_LENGTH);
    scanf("%s", &nuovoContatto.Nome);
    printf("Inserisci il cognome (max %d caratteri): ", COGNOME_MAX_LENGTH);
    scanf("%s", &nuovoContatto.Cognome);
    printf("Inserisci il numero telefonico (max %d caratteri): ", NUMERO_TELEFONICO_MAX_LENGTH);
    scanf("%s", &nuovoContatto.NumeroTelefonico);

    if(AddContatto(rubrica, nuovoContatto))
        printf("Contatto aggiunto con successo!\n");
    else
        printf("Si e' verificato un errore\n");
}

void RicercaEsattaContatto(const struct Rubrica* rubrica)
{
    char keyword[KEYWORD_MAX_LENGTH];

    printf("\nRicerca esatta contatto\n");
    printf("Inserisci il termine da cercare (max %d caratteri): ", KEYWORD_MAX_LENGTH);
    scanf("%s", &keyword);

    int index = SearchContatto(rubrica, keyword, true);
    if(index != -1)
        printf("Contatto trovato:\n%s\n", ContattoToString(&rubrica->Contatti[index]));
    else
        printf("Nessun risultato trovato\n");
}

void RicercaApprossimataContatto(const struct Rubrica* rubrica)
{
    char keyword[KEYWORD_MAX_LENGTH];

    printf("\nRicerca approssimata contatto\n");
    printf("Inserisci il termine da cercare (max %d caratteri): ", KEYWORD_MAX_LENGTH);
    scanf("%s", &keyword);

    int index = SearchContatto(rubrica, keyword, false);
    printf("Contatto trovato:\n%s\n", ContattoToString(&rubrica->Contatti[index]));
}

void StampaCompletaRubrica(const struct Rubrica* rubrica)
{
    printf("\nStampa completa della rubrica\n");
    printf("%s", RubricaToString(rubrica));
}

int main()
{
    struct Rubrica rubrica = NewRubrica(); // Technically needed, but apparently not (more details in "rubrica.c")

    char choice = '0';
    do
    {
        printf("\n");
        printf("Menu principale\n");
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