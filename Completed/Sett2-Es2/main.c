#include <stdio.h>

int ricercaBinaria(int min, int max) //funzione che cerca il numero dell'utente senza un numero massimo di tentativi, ritorna il numero di tentativi
{
    int numeroTentativi = 0;

    int numeroMedio;
    int flagIndovinato;
    int flagMinMax;

    do
    {
        numeroTentativi++;

        numeroMedio = (min + max) / 2;
        
        printf("Il tuo numero e' %d?\n0)No\n1)Si\n", numeroMedio);
        fflush(stdin);
        scanf("%d", &flagIndovinato);

        if(!flagIndovinato)
        {
            printf("Il tuo numero e' \n0)minore\n1)maggiore\n");
            fflush(stdin);
            scanf("%d", &flagMinMax);

            if(flagMinMax)
            {
                min = numeroMedio; //se il numero è più grande posso restringere il campo di ricerca ai numeri dal numero medio al numero massimo
            }
            else
            {
                max = numeroMedio; //se il numero è più piccolo posso restringere il campo di ricerca ai numeri dal numero minimo al numero medio
            }
        }
    }
    while(!flagIndovinato); //rimane nel while finche' il numero non viene indovinato

    return numeroTentativi;
}

int ricercaBinariaConLimiti(int min, int max, int numeroMassimoTentativi) //funzione che cerca il numero dell'utente con un numero massimo di tentativi
{
    int numeroTentativi = 0;

    int numeroMedio;
    int flagIndovinato;
    int flagMinMax;

    do
    {
        numeroTentativi++;

        numeroMedio = (min + max) / 2;
        
        printf("Il tuo numero e' %d?\n0)No\n1)Si\n", numeroMedio);
        fflush(stdin);
        scanf("%d", &flagIndovinato);

        if(!flagIndovinato && numeroTentativi < numeroMassimoTentativi)
        {
            printf("Il tuo numero e' \n0)minore\n1)maggiore\n");
            fflush(stdin);
            scanf("%d", &flagMinMax);

            if(flagMinMax)
            {
                min = numeroMedio; //se il numero è più grande posso restringere il campo di ricerca ai numeri dal numero medio al numero massimo
            }
            else
            {
                max = numeroMedio; //se il numero è più piccolo posso restringere il campo di ricerca ai numeri dal numero minimo al numero medio
            }
        }
    }
    while(!flagIndovinato && numeroTentativi < numeroMassimoTentativi); //rimane nel while finche' il numero non viene indovinato e il numero di tentativi non supera il massimo

    if(flagIndovinato)
    {
        return numeroTentativi;
    }
    else
    {
        return 0;
    }
}

int main()
{
    int min, max, numeroMassimoTentativi, risultato;

    do
    {
        printf("Inserisci il minimo dell'intervallo che comprende il numero da indovinare\n");
        fflush(stdin);
        scanf("%d", &min);
    }
    while (min < 0);
    
    do
    {
        printf("Inserisci il massimo dell'intervallo che comprende il numero da indovinare\n");
        fflush(stdin);
        scanf("%d", &max);
    }
    while(max < min);

    printf("Inserisci il numero massimo di tentativi [0 = illimitati]\n");
    fflush(stdin);
    scanf("%d", &numeroMassimoTentativi);

    printf("Pensa a un numero compreso tra il minimo ed il massimo!\n");

    if (numeroMassimoTentativi > 0)
    {
        risultato = ricercaBinariaConLimiti(min, max, numeroMassimoTentativi);
    }
    else
    {
        risultato = ricercaBinaria(min, max);
    }

    if(risultato)
    {
        printf("Ho impiegato %d tentativi per indovinare il tuo numero!", risultato);
    }
    else
    {
        printf("Non sono riuscito ad indovinare il tuo numero...\n");
    }

    return 0;
}