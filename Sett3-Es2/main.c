#include <stdio.h>
#include <ctype.h>

#ifdef _WIN32
#include <conio.h>
#endif

int main()
{
    /*
        Affinché getch funzioni, bisogna aprire direttamente l'eseguibile (problema console CLion)
    */

    char c;

    int contTotale = 0; // Numero di caratteri inseriti
    int contAlfaNum = 0; // Numero di caratteri alfanumerici
    int contAlf = 0; // Numero di caratteri alfabetici
    int contControllo = 0; // Numero di caratteri di controllo
    int contCifre = 0; // Numero di caratteri cifre (0-9)
    int contGraf = 0; // Numero di caratteri con rappresentazione grafica
    int contMinuscoli = 0; // Numero di caratteri minuscoli
    int contMaiuscoli = 0; // Numero di caratteri maiuscoli
    int contStampabile = 0; // Numero di caratteri stampabili (non di controllo)
    int contPunteggiatura = 0; // Numero caratteri di punteggiatura
    int contSpazi = 0; // Numero di caratteri spazio
    int contCifreHex = 0; // Numero di caratteri cifre esadecimali

    printf("Inserisci un testo seguito da un '#' per indicarne la fine e ti stampero' le statistiche\n");

    do {

#ifdef _WIN32
        c = getche();
#else
        c = getc(stdin);
#endif

        contTotale++;

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
        if (isupper(c))
            contMaiuscoli++;
        if (isxdigit(c))
            contCifreHex++;
    }
    while (c != '#');
    printf("\n");
    printf("Il numero totale di caratteri inseriti e' %d\n", contTotale);
    printf("Il numero di caratteri alfanumerici inseriti e' %d\n", contAlfaNum);
    printf("Il numero di caratteri alfabetici inseriti e' %d\n", contAlf);
    printf("Il numero di caratteri di controllo inseriti e' %d\n", contControllo);
    printf("Il numero di caratteri cifra inserite e' %d\n", contCifre);
    printf("Il numero di caratteri con rappresentazione grafica inseriti e' %d\n", contGraf);
    printf("Il numero di caratteri minuscoli inseriti e' %d\n", contMinuscoli);
    printf("Il numero di caratteri maiuscoli inseriti e' %d\n", contMaiuscoli);
    printf("Il numero di caratteri stampabili (non di controllo) inseriti e' %d\n", contStampabile);
    printf("Il numero di caratteri di punteggiatura inseriti e' %d\n", contPunteggiatura);
    printf("Il numero di caratteri spazio inseriti e' %d\n", contSpazi);
    printf("Il numero di caratteri cifra esadecimali inseriti e' %d\n", contCifreHex);

    return 0;
}