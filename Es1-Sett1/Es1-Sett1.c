#include <stdio.h> //Libreria standard per l'input output
#include <stdlib.h> //Libreria standard multifunzione
#include <limits.h> //Libreria contenente i define dei limiti massimi e minimi per ogni tipo
#include <float.h> //Libreria contenente metodi e define dei limiti per i tipi decimali

int main(void)
{
    //Dichiarazione di tutte le variabili necessarie

    char carattere = 'H';
    signed char carattereConSegno = 'F';
    unsigned char carattereSenzaSegno = 'J';

    short int interoCorto = 6;
    int intero = 96;
    long int interoLungo = 3636;
    long long int interoMoltoLungo = 558589;

    signed short int interoCortoConSegno = +5;
    signed int interoConSegno = +86;
    signed long int interoLungoConSegno = -58;
    signed long long int interoMoltoLungoConSegno = -68;

    unsigned short int interoCortoSenzaSegno = 96;
    unsigned int interoSenzaSegno = 65;
    unsigned long int interoLungoSenzaSegno = 478;
    unsigned long long int interoMoltoLungoSenzaSegno = 98459;

    float decimale = 1.6f;
    double decimalePreciso = 55.3;
    long double decimalePrecisoLungo = 85.3223;

    int caratteriStampati = 0;

    //Spiegazione del printf
    //Sintassi: %[parametro][flags][larghezza][.precisione][lunghezza]tipo
    //[parametro] permette di selezionare quale parametro del printf mettere in quel posto (con il valore 2 stamperebbe il terzo parametro del printf)
    //[flags] permette alcune azioni tra cui l'allineamento del testo o aggiungere il segno ai numeri positivi
    //[larghezza] permette di scegliere il minimo numero di caratteri da stampare, se la variabile stampata occupa meno caratteri, gli altri verranno riempiti da spazi
    //[.precisione] permette di scegliere il numero di cifre dopo la virgola per i numeri decimali
    //[lunghezza] permette di scegliere la lunghezza del tipo menzionato successivamente
    //tipo è la tipologia di valore che vogliamo stampare, di solito corrisponde al tipo di variabile (c per char, s per string, d per interi ecc.)

    //Avendo creato una tabella usando i campi [flags] e [larghezza] di printf, il numero di caratteri stampati sarà costante per ogni riga.

    printf("%-25s | %-25s | %-25s | %-25s | %-25s | %-25s\n", "Tipologia variabile", "Contenuto", "Byte necessari", "Massimo valore", "Minimo valore", "Caratteri stampati");
    caratteriStampati = printf("%-25s | %-25c | %-25d | %-25d | %-25d | ", "CHAR", carattere, sizeof(char), CHAR_MAX, CHAR_MIN);
    printf("%-25d\n", caratteriStampati);
    caratteriStampati = printf("%-25s | %-25c | %-25d | %-25d | %-25hd | ", "SIGNED CHAR", carattereConSegno, sizeof(signed char), SCHAR_MAX, SCHAR_MIN);
    printf("%-25d\n", caratteriStampati);
    caratteriStampati = printf("%-25s | %-25c | %-25d | %-25d | %-25d | ", "UNSIGNED CHAR", carattereSenzaSegno, sizeof(unsigned char), UCHAR_MAX, 0);
    printf("%-25d\n", caratteriStampati);
    caratteriStampati = printf("%-25s | %-25hd | %-25d | %-25hd | %-25hd | ", "SHORT INT", interoCorto, sizeof(short int), SHRT_MAX, SHRT_MIN);
    printf("%-25d\n", caratteriStampati);
    caratteriStampati = printf("%-25s | %-25d | %-25d | %-25d | %-25d | ", "INT", intero, sizeof(int), INT_MAX, INT_MIN);
    printf("%-25d\n", caratteriStampati);
    caratteriStampati = printf("%-25s | %-25ld | %-25d | %-25ld | %-25ld | ", "LONG INT", interoLungo, sizeof(long int), LONG_MAX, LONG_MIN);
    printf("%-25d\n", caratteriStampati);
    caratteriStampati = printf("%-25s | %-25lld | %-25d | %-25lld | %-25lld | ", "LONG LONG INT", interoMoltoLungo, sizeof(long long int), LLONG_MAX, LLONG_MIN);
    printf("%-25d\n", caratteriStampati);
    caratteriStampati = printf("%-25s | %-25hd | %-25d | %-25hd | %-25hd | ", "SIGNED SHORT INT", interoCortoConSegno, sizeof(signed short int), SHRT_MAX, SHRT_MIN);
    printf("%-25d\n", caratteriStampati);
    caratteriStampati = printf("%-25s | %-25d | %-25d | %-25d | %-25d | ", "SIGNED INT", interoConSegno, sizeof(signed int), INT_MAX, INT_MIN);
    printf("%-25d\n", caratteriStampati);
    caratteriStampati = printf("%-25s | %-25ld | %-25d | %-25ld | %-25ld | ", "SIGNED LONG INT", interoLungoConSegno, sizeof(signed long int), LONG_MAX, LONG_MIN);
    printf("%-25d\n", caratteriStampati);
    caratteriStampati = printf("%-25s | %-25lld | %-25d | %-25lld | %-25lld | ", "SIGNED LONG LONG INT", interoMoltoLungoConSegno, sizeof(signed long long int), LLONG_MAX, LLONG_MIN);
    printf("%-25d\n", caratteriStampati);
    caratteriStampati = printf("%-25s | %-25hu | %-25d | %-25hu | %-25hu | ", "UNSIGNED SHORT INT", interoCortoSenzaSegno, sizeof(unsigned short int), USHRT_MAX, 0);
    printf("%-25d\n", caratteriStampati);
    caratteriStampati = printf("%-25s | %-25u | %-25d | %-25u | %-25u | ", "UNSIGNED INT", interoSenzaSegno, sizeof(unsigned int), UINT_MAX, 0);
    printf("%-25d\n", caratteriStampati);
    caratteriStampati = printf("%-25s | %-25lu | %-25d | %-25lu | %-25lu | ", "UNSIGNED LONG INT", interoLungoSenzaSegno, sizeof(unsigned long int), ULONG_MAX, 0);
    printf("%-25d\n", caratteriStampati);
    caratteriStampati = printf("%-25s | %-25llu | %-25d | %-25llu | %-25llu | ", "UNSIGNED LONG LONG INT", interoMoltoLungoSenzaSegno, sizeof(unsigned long long int), ULLONG_MAX, 0);
    printf("%-25d\n", caratteriStampati);
    caratteriStampati = printf("%-25s | %-25.15f | %-25d | %-25.5e | %-25.5e | ", "FLOAT", decimale, sizeof(float), FLT_MAX, FLT_MIN);
    printf("%-25d\n", caratteriStampati);
    caratteriStampati = printf("%-25s | %-25.15f | %-25d | %-25.5e | %-25.5e | ", "DOUBLE", decimalePreciso, sizeof(double), DBL_MAX, DBL_MIN);
    printf("%-25d\n", caratteriStampati);
    caratteriStampati = printf("%-25s | %-25.15Lf | %-25d | %-25.5Le | %-25.5Le | ", "LONG DOUBLE", decimalePrecisoLungo, sizeof(long double), LDBL_MAX, LDBL_MIN);
    printf("%-25d\n", caratteriStampati);

    return 0;
}