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



struct Libro caricaLibriDaFile(char *percorso,List *lista)
{
   
    struct Libro libro;
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
    while(!feof(stream))//questo metodo legge un libro da ogni riga
    {     
        fscanf(stream,"%d-%d-%d %d-%d-%d %s %s %s %s %d %d",&libro.data_di_lettura.giorno,&libro.data_di_lettura.mese,&libro.data_di_lettura.anno,//questo legge la prima data
        &libro.anno_di_pubblicazione.giorno,&libro.anno_di_pubblicazione.mese,&libro.anno_di_pubblicazione.anno,//questo la seconda
        &libro.titolo,&libro.autore,&libro.genere,
        &libro.casa_editrice,&libro.valutazione,&libro.id);//la stringa che legge deve essere formattata cosi:
        //data_di_lettura(giorno-mese-anno) data_di_pubblicazione titolo autore genere casa_editrice valutazione id
        add_element(lista,libro);  
    }

    printf("libri caricati");
   
    fclose(stream);
}

void inserisciLibro(List *lista)
{
    struct Libro libro;
    printf("per inserire il libro segui precisamente la formattazione: data_di_lettura(giorno-mese-anno) data_di_pubblicazione(giorno-mese-anno) titolo autore genere casa_editrice valutazione id\n");
    scanf("%d-%d-%d %d-%d-%d %s %s %s %s %d %d",&libro.data_di_lettura.giorno,&libro.data_di_lettura.mese,&libro.data_di_lettura.anno,//questo legge la prima data
        &libro.anno_di_pubblicazione.giorno,&libro.anno_di_pubblicazione.mese,&libro.anno_di_pubblicazione.anno,//questo la seconda
        &libro.titolo,&libro.autore,&libro.genere,
        &libro.casa_editrice,&libro.valutazione,&libro.id);
    if(add_element(lista,libro))
    {
        printf("libro correttamente inserito\n");
        return;
    }
    printf("c'e stato un errore");
    return;
}

void stampa_libro(struct Libro libro)
{
    printf("%d-%d-%d %d-%d-%d %s %s %s %s %d %d",libro.data_di_lettura.giorno,libro.data_di_lettura.mese,libro.data_di_lettura.anno,
        libro.anno_di_pubblicazione.giorno,libro.anno_di_pubblicazione.mese,libro.anno_di_pubblicazione.anno,
        libro.titolo, libro.autore,libro.genere,
        libro.casa_editrice,libro.valutazione,libro.id);
}

void stampa_libro_by_valutazione(struct Libro libro,int valutazione)
{
    if(libro.valutazione = valutazione)
    {
     printf("%d-%d-%d %d-%d-%d %s %s %s %s %d %d",libro.data_di_lettura.giorno,libro.data_di_lettura.mese,libro.data_di_lettura.anno,
        libro.anno_di_pubblicazione.giorno,libro.anno_di_pubblicazione.mese,libro.anno_di_pubblicazione.anno,
        libro.titolo, libro.autore,libro.genere,
        libro.casa_editrice,libro.valutazione,libro.id);   
    }
    return;
}

void rimuovi_libro(List *lista)
{
    printf("inserisci il titolo del libro che vuoi rimuovere");
    char *titolo;
    scanf("%s",&titolo);

    iterator_init(lista);
    int lunghezza = get_length(lista);
    int i = 0;
    for(i; i < lunghezza ; i++ )
    {
        if(strcmp(lista->iterator.current_node->data.titolo,titolo))
        {
            node_remove(lista,i);
            printf("libro rimosso");
        }
    }
}

void stampa_libri(List *lista)
{
    struct Libro *libri = list_to_array(lista);
    int size = get_length(lista);
    int i = 0;
    
    for(i = 0; i < size ; i++)
    {
        printf("libro n.%d ",i);
        stampa_libro(libri[i]);
        printf("\n");
    }

}

void stampa_libri_by_valutazione(List *lista)
{
    int valutazione = 0;
    struct Libro *libri = list_to_array(lista);
    int size = get_length(lista);
    int i = 0;

    prinf("inserisci la valutazione che i libri devono avere\n");
    scanf("%d",&valutazione);
    
    for(i = 0; i < size ; i++)
    {
        printf("libro n.%d ",i);
        stampa_libro_by_valutazione(libri[i],valutazione);
        printf("\n");
    }

}


int main()
{
    List lista_di_libri = new_list();
    
    /* stampa_libri(&lista_di_libri);
    printf("fatto"); */
    int input = 1;
    printf("[0] per uscire dal programma\n [1] per caricare i libri dal file libri.txt\n [2] per visualizzare tutti i libri\n [3] per inserire un libro\n [4] per rimuovere un libro\n [5] filtra libri per valutazione\n");
            
    while(input != 0)
    {
        scanf("%d",&input);

        switch (input)
        {

            case 1:
                caricaLibriDaFile("./libri.txt",&lista_di_libri);
            break;
            
            case 2:
                stampa_libri(&lista_di_libri);
            break;

            case 3:
                inserisciLibro(&lista_di_libri);
            break;

            case 4:
                rimuovi_libro(&lista_di_libri);
            break;

            case 5:
                stampa_libri_by_valutazione(&lista_di_libri);
            break;

            default:
                break;
        }
    }
}