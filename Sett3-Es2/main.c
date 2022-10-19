#include <stdio.h>
#include <conio.h>
#include <ctype.h>

int main()
{
    /*
     * Finché getch funzioni, bisogna aprire direttamente l'eseguibile (problema console CLion)
     * */
    char c;
    int contAlfaNum; // numero di caratteri alfanumerici
    int contAlf; // numero di caratteri alfabetici
    int contControllo; // numero di caratteri di controllo
    int contCifre; // numero di caratteri cifre (0-9)
    int contGraf; // numero di caratteri con rappresentazione grafica
    int contMinuscoli; // numero di caratteri minuscoli
    int contStampabile; // numero di caratteri stampabili (non di controllo)
    int contPunteggiatura; // numero caratteri di punteggiatura
    int contSpazi; // numero di caratteri spazio

    printf("Inserisci un testo seguito da un '#' per indicarne la fine e ti stampero le statistiche\n");

    do {
        c = getch();

        if (isalnum(c))
            contAlfaNum++;
        if (isalpha(c))
            contAlf++;
        if (iscntrl(c))
            contControllo++;
        if (isdigit(c))
            contCifre++;
        if (isgraph(c))
            contGraf++;
        if (islower(c))
            contMinuscoli++;
        if (isprint(c))
            contStampabile++;
        if (ispunct(c))
            contPunteggiatura++;
        if (isspace(c))
            contSpazi++;






    }
    while (c != '#');

    if (isspace(c)) {
        printf("Il carattere %c e uno spazio", c);
    } else {
        printf("Il carattere %c non e uno spazio", c);
    }

    if (isupper(c)) {
        printf("Il carattere %c e una maiuscola", c);
    } else {
        printf("Il carattere %c non e una maiuscola", c);
    }

    if (isxdigit(c)) {
        printf("Il carattere %c e esadecimale", c);
    } else {
        printf("Il carattere %c non e esadecimale", c);
    }

    return 0;
}