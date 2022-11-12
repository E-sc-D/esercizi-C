#include <stdio.h>

#define COSTANTE_DI_CONVERSIONE 235.21458357139 //Costante di conversione da miglia per gallone a litri per 100km

int main() 
{
    int migliaPercorse, galloniConsumati;
    printf("Inserisci il numero di miglia percorse: ");
    scanf("%d", &migliaPercorse);

    printf("Inserisci il numero di galloni di benzina consumati: ");
    scanf("%d", &galloniConsumati);

    float migliaPerGallone;
    migliaPerGallone = (float)migliaPercorse / (float)galloniConsumati;

    printf("Il valore di miglia per gallone e: %.2f\n", migliaPerGallone);

    float litriPer100km;
    litriPer100km = COSTANTE_DI_CONVERSIONE / migliaPerGallone;

    printf("Il valore convertito in litri per 100km e: %.3f\n", litriPer100km);

    return 0;
}
