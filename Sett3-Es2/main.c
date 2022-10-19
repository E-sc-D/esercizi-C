#include <stdio.h>
#include <conio.h>
#include <ctype.h>

int main()
{
    char c;

    printf("Inserisci un testo seguito da un '#' per indicarne la fine e ti stampero le statistiche\n");

    do {
        c = getch();
    }
    while (c != '#');

    if (isalnum(c)) {
        printf("Il carattere %c e un carattere alfanumerico ", c);
    } else {
        printf("Il carattere %c non e un carattere alfanumerico ", c);
    }

    if (isalpha(c)) {
        printf("Il carattere %c e alfabetico", c);
    } else {
        printf("Il carattere %c non e alfabetico", c);
    }

    if (iscntrl(c)) {
        printf("Il carattere %c e un carattere di controllo", c);
    } else {
        printf("Il carattere %c non e un carattere di controllo", c);
    }

    if (isdigit(c)) {
        printf("Il carattere %c e una cifra", c);
    } else {
        printf("Il carattere %c non e una cifra", c);
    }

    if (isgraph(c)) {
        printf("Il carattere %c ha una rappresentazione grafica (si puo vedere sulla console", c);
    } else {
        printf("Il carattere %c non ha una rappresentazione grafica (non si puo vedere sulla console ma e comunque stampato", c);
    }

    if (islower(c)) {
        printf("Il carattere %c e minuscolo", c);
    } else {
        printf("Il carattere %c non e minuscolo", c);
    }

    if (isprint(c)) {
        printf("Il carattere %c e stampabile (non e di controllo)", c);
    } else {
        printf("Il carattere %c non e stampabile", c);
    }

    if (ispunct(c)) {
        printf("Il carattere %c e di punteggiatura", c);
    } else {
        printf("Il carattere %c non e di punteggiatura", c);
    }

    if (isspace(c)) {
        printf("Il carattere %c e uno spazio", c);
    } else {
        printf("Il carattere %c non e uno spazio", c);
    }
    return 0;
}