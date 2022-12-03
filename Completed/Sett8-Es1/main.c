#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <string.h>
struct consoleBuffer
{
    int count;
    char buffer[100];
};
struct Array
{
    char* array;
    int n;
} emptyArray = { NULL , 0 };

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

void StringCopy(char *source, char **dest,int *d, int i, int j)//copia dall'elemento i all'elemento j dentro dest
{
    if(j-i > *d)
    {
        *d = *d + j;
        (*dest) = realloc((*dest),*d);//la riallocazione calzerebbe a pennello solo con j ma ci serve extra spazio per le future modifiche 
        
    }

    for( int f = 0,i ; i < j  ; i++,f++ )
    {
        (*dest)[f] = source[i];
        printf("\ndest %c ,source %c",(*dest)[f],source[i]);
    }
}
void Stringclear(char *string, int len)
{
    for(int i = 0; i < len; i++)
    {
        string[i] = 0;
    }
}

int StringLen(char *string)
{
    int i;
    for(i = 0; string[i]!='\0';i++);

    return i + 1; //in questo modo il risultato conta anche il carattere terminatore: "ciao\0" sarà lunga 5
    
}
int SafeStrcat(char **dest, int *d, char*source)
{
    int dEnd = 0,sEnd = 0;
    dEnd = StringLen((*dest));
    sEnd = StringLen(source);
    if((*d-dEnd) < sEnd)//se non ce spazio dentro l'array di destinazione
    {
        *d += sEnd;
        (*dest) = realloc((*dest),*d);//viene riallocato( aggiungere controllo null per realloc)
    }
    strcat((*dest),source);
}

void SeparetorUnifier(char *string)
{
    int i = 0;
    int j = 0;
    struct Array string2;//array di lavoro
    struct Array stringOut;//stringa finale
    char *spacer = (char*)calloc(1,sizeof(char));
    stringOut.n = StringLen(string);
    stringOut.array = (char*)calloc(StringLen(string),sizeof(char));
    string2.n = StringLen(string);
    string2.array = (char*)calloc(StringLen(string),sizeof(char));
    
    do
    {
        if(string[i] != '\0')
        {
            if(string[i] != ' ' && isalpha(string[i]))//se non inclontriamo un carattere spaziatore
            {
                
                //dopo che l'if ha girato abbiamo raggiunto l'inizio della prima frase quindi salviamo
                //l'inizio nella variabile j
                j = i;
                //a questo punto dobbiamo far avanzare la variabile i fino a quando non arriviamo alla fine della parola.
                while(string[i] != ' ' && isalpha(string[i]) && string[i] != '\0')
                {
                    i++;
                }
                Stringclear(string2.array,string2.n);//la stringa viene ripulita da precedenti frasi
                printf("\n here");
                StringCopy(string,&(string2.array),&(string2.n),j,i);
                //qua la stringa va modificata
                SafeStrcat(&(stringOut.array),&(stringOut.n),spacer);
                //una volta lavorata usiamo realloc per ingrandire la frase di output e ci mettiamo in fondo la frase modificata
            }
            else
            {
                
                *spacer = string[i];//viene salvato il carattere spaziatore
                SafeStrcat(&(stringOut.array),&(stringOut.n),spacer);//dovrebbe concatenare (da verificare se la riallocazione funziona su elementi di struct)
                i++;
            }
            
        }  
    } 
    while (string[i] != '\0');

    printf("stringa : %d , i : %d,j : %d, striga2 : %d",stringOut.n,i,j,string2.n);
}

void PhraseEditor1()
{

}

int main()
{
    char *string;
    ReadString(&string);
    SeparetorUnifier(string);
}  

