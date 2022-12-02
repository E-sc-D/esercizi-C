#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
struct consoleBuffer
{
    int count;
    char buffer[100];
};

int ReadString(char **pointer)//legge una stringa è la salva nel puntatore che punta pointer
{
    struct consoleBuffer console;
    console.count = 0;
    do
    {
        console.buffer[console.count] = getchar();
        console.count++;
    }
    while(console.buffer[console.count - 1] != '\n'); //vengono salvati dentro un buffer di 100 elementi i char inseriti
    console.buffer[console.count - 1] = '\0';//l'ultimo elemento sarà il terminatore
    (*pointer) = (char*)malloc((sizeof(char) * console.count));//viene inizializzata la matrice in base al numero di elementi inseriti

    for(int j = 0;j < console.count ; j++)
    {
        (*pointer)[j] = console.buffer[j];//viene riempita
    }
    return console.count ; //viene restituito il numero di char dentro il vettore
}

void StringEditor(char **string,int len)
{
    for(int i = 0 ; i < len ; i++)
    {
        printf("%c",(*string)[i]);
    }
}

void StringCopy(char *source, char *dest, int i, int j)//copia dall'elemento i all'elemento j dentro dest
{
    for( int f = 0,i ; i < j + 1 ; i++,f++ )
    {
        dest[f] = source[i];
    }
}

void SeparetorUnifier(char *string)
{
    int i = 0;
    int j = 0;
    char *string2;
    char *stringoutput;
    char spacer = '\n';

    do
    {

        if(string[i] != ' ' && isalpha(string[i]) && string[i] != '\0')//se non inclontriamo un carattere spaziatore
        {
            
           //dopo che l'if ha girato abbiamo raggiunto l'inizio della prima frase quindi salviamo
           //l'inizio nella variabile j

           //a questo punto dobbiamo far avanzare la variabile i fino a quando non arriviamo alla fine della parola.

           //copiamo ora la parola selezionata dentro uno spazio per poterla lavorare

           //una volta lavorata usiamo realloc per ingrandire la frase di output e ci mettiamo in fondo la frase modificata

        }
        else{i++;}//ogni volta che il programma va qua significa che abbiamo incontrato un carattere di spazio quindi lo 
                 //trasferiamo direttamente dentro l'array di output( prima va ridimensionato )
        
       
    } 
    while (string[i] != '\0');
}

void PhraseEditor1()
{

}

int main()
{
    char *string;
    ReadString(&string);
    SeparetorUnifier(string);
    printf("programma terminato");
    
}  

