#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.c"

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
        printf("file non trovato o path sbagliato\n");
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

    printf("libri caricati\n");
   
    fclose(stream);
}

void inserisciLibro(List *lista)
{
    struct Libro libro;
    
    printf("inserisci il giorno di lettura del libro\n");
    scanf("%d",&libro.data_di_lettura.giorno);
    printf("inserisci il mese di lettura del libro");
    scanf("%d",&libro.data_di_lettura.mese);
    printf("inserisci l'anno di lettura del libro\n");
    scanf("%d",&libro.data_di_lettura.anno);

    printf("inserisci il giorno di pubblicazione del libro\n");
    scanf("%d",&libro.anno_di_pubblicazione.giorno);
    printf("inserisci il mese di pubblicazione del libro\n");
    scanf("%d",&libro.anno_di_pubblicazione.mese);
    printf("inserisci l'anno di pubblicazione del libro\n");
    scanf("%d",&libro.data_di_lettura.anno);

    printf("inserisci il titolo del libro\n");
    scanf(" %s",&libro.titolo);
    printf("inserisci l'autore del libro\n");
    scanf(" %s",&libro.autore);
    printf("inserisci il genere del libro\n");
    scanf(" %s",&libro.genere);
    printf("inserisci la casa editrice del libro del libro\n");
    scanf(" %s",&libro.autore);
    printf("inserisci la valutazione del libro\n");
    scanf("%d",&libro.valutazione);
    printf("inserisci l'id del libro\n");
    scanf(" %s",&libro.id);

    if(add_element(lista,libro))
    {
        printf("libro correttamente inserito\n");
        return;
    }
    printf("c'e stato un errore\n");
    return;
}

void stampa_libro(struct Libro libro)
{
    printf("%d-%d-%d %d-%d-%d %s %s %s %s %d %d\n",libro.data_di_lettura.giorno,libro.data_di_lettura.mese,libro.data_di_lettura.anno,
        libro.anno_di_pubblicazione.giorno,libro.anno_di_pubblicazione.mese,libro.anno_di_pubblicazione.anno,
        libro.titolo, libro.autore,libro.genere,
        libro.casa_editrice,libro.valutazione,libro.id);
}

void stampa_libro_by_valutazione(struct Libro libro,int valutazione)
{
    if(libro.valutazione == valutazione)
    {
     printf("%d-%d-%d %d-%d-%d %s %s %s %s %d %d\n",libro.data_di_lettura.giorno,libro.data_di_lettura.mese,libro.data_di_lettura.anno,
        libro.anno_di_pubblicazione.giorno,libro.anno_di_pubblicazione.mese,libro.anno_di_pubblicazione.anno,
        libro.titolo, libro.autore,libro.genere,
        libro.casa_editrice,libro.valutazione,libro.id);   
    }
    return;
}

void rimuovi_libro(List *lista)
{
    printf("inserisci il titolo del libro che vuoi rimuovere\n");
    char *titolo;
    ReadString(&titolo);
    iterator_init(lista);
    
    while(iterator_forward(lista))
    {
        if(strcmp(lista->iterator.current_node->data.titolo,titolo) == 0)
        {
            node_remove(lista,lista->iterator.current_index); 
            printf("libro rimosso\n");
        }
        
    } 
    return;
}

void stampa_libri(List *lista)
{
    struct Libro *libri = list_to_array(lista);
    int size = get_length(lista);
    int i = 0;
    
    for(i = 0; i < size; i++)
    {
        printf("libro n.%d ",i);
        stampa_libro(libri[i]);
    }

}

void stampa_libri_by_valutazione(List *lista)
{
    int valutazione = 0;
    struct Libro *libri = list_to_array(lista);
    int size = get_length(lista);
    int i = 0;

    printf("inserisci la valutazione che i libri devono avere\n");
    scanf("%d",&valutazione);
    
    for(i = 0; i < size ; i++)
    {
        stampa_libro_by_valutazione(libri[i],valutazione);
    }

}


int main()
{
    List lista_di_libri = new_list();
    
    /* stampa_libri(&lista_di_libri);
    printf("fatto"); */
    int input = 1;
            
    while(input != 0)
    {
        fflush(stdin);
        printf("scegli dal menu:\n");
        printf("[0] per uscire dal programma\n [1] per caricare i libri dal file libri.txt\n [2] per visualizzare tutti i libri\n [3] per inserire un libro\n [4] per rimuovere un libro\n [5] filtra libri per valutazione\n");
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