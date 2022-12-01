#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
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
    dest[3] = '\0';
}

void SeparetorUnifier(char *string)
{
    int i = 0;
    int j = 0;
    char *string2;
    char spacer = '\n';

    do
    {

        if(string[i] != ' ' && isalpha(string[i]))//se non inclontriamo un carattere spaziatore
        {
            
            j = i;//salviamo l'inizio della prima parola
            if(i>0)
                spacer = string[i-1];//salviamo il carattere spaziatore
            while (string[i] != ' ' && isalpha(string[i]) && string[i] != '\0')//avanziamo fino alla fine della parola o al carattere terminatore
            {
                i++;
            }
            if(i>0)
            string2 = malloc(sizeof(char)*((i -1 ) - j));//quando il while finisce i si ferma 1 carattere oltre la parola per questo -1
            StringCopy(string,string2,j,i);
            printf("%d",i-j);
            //StringEditor(&string2,i-j);
            //stampa della stringa modificata
            free(string2);

        }
        else{i++;}
        
       //separeates the phrases with !isalpha characters and white spaces 
       //with the i counter take a portion of array an edit in an external funcion
       //return the new phrase edited and concatenaite it to the final string 
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

