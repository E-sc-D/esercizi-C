#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Data
{
    int giorno;
    int mese;
    int anno;
};
struct Libro
{
    struct Data data_di_lettura;
    struct Data anno_di_pubblicazione;
    char titolo[50];
    char autore[50];
    char genere[20];
    char casa_editrice[30];
    int valutazione;
    int id;
};

#define DATA_TYPE struct Libro
#include "list.c"



struct Libro caricaLibroDaFile(char *percorso)
{
    char *campi_libro[] = 
    {
        "data_di_lettura",
        "anno_di_pubblicazione",
        "titolo",
        "autore",
        "genere",
        "casa_editrice",
        "valutazione",
        "id"
    };

    char array[1000];
    FILE *stream = fopen(percorso,"r");
    int campi = 8;
    int counter = 0;

    if(stream == NULL)
    {
        printf("file non trovato o path sbagliato");
        return;
    }
   
    int i = 0;
    int j = 0;

    while(fgets(array, 1000, stream))//fget aggiunge il terminatore
    {
        for(i ; i<8 ; i++)
        {
            if(strncmp(array, campi_libro[i], strlen(campi_libro[i]))) //se è stato trovato il nome del campo
            {
                
            }  
        }
        
    }  

    fclose(stream);
    return stringArray;
}

int main()
{

}