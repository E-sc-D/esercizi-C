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
    int n;//dimensione array
} emptyArray = { NULL , 0 };

void ReadString(struct Array *string)//legge una stringa è la salva nel puntatore che punta pointer
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
    string->array = (char*)malloc((sizeof(char) * console.count));//viene inizializzata la matrice in base al numero di elementi inseriti

    for(int j = 0;j < console.count ; j++)
    {
        (string->array)[j] = console.buffer[j];//viene riempita
    }
    string->n = console.count;
}

void StringEditor(struct Array *string)
{
    for(int i = 0 ; i < string->n ; i++)
    {
        printf("%c",(string->array)[i]);
    }
}

void StringCopy(struct Array *dest,struct Array *source, int i, int j)//copia dall'elemento i all'elemento j dentro dest
{
    if( j-i > dest ->n )
    {
        dest->n = dest->n + j;
        dest->array = realloc(dest->array,dest->n);//la riallocazione calzerebbe a pennello solo con j ma ci serve extra spazio per le future modifiche 
    }
    int f;
    for( f = 0,i ; i < j  ; i++,f++ )
    {
        dest->array[f] = (source->array)[i];
        printf("\ndest %s ,source %c",(dest->array),(source->array)[i]);
    }
}

void Stringclear(struct Array *string)
{
    int i;
    for( i = 0; i < string->n; i++)
    {
        (string->array)[i] = 0;
    }
}

int StringLen(char *string)
{
    int i;
    for(i = 0; string[i]!='\0';i++);

    return i + 1; //in questo modo il risultato conta anche il carattere terminatore: "ciao\0" sarà lunga 5
    
}

int SafeStrcat(struct Array *source,struct Array *dest)
{
    int dEnd = 0,sEnd = 0;
    dEnd = StringLen(dest->array);
    sEnd = StringLen(source->array);
    if((dest->n - dEnd) < sEnd)//se non ce spazio dentro l'array di destinazione
    {
        dest->n += sEnd;
        dest->array = realloc(dest->array,dest->n);//viene riallocato( aggiungere controllo null per realloc)
    }
    strcat(dest->array,source->array);
}

void SeparetorUnifier(struct Array *string)
{
    int i = 0;
    int j = 0;
    struct Array string2;//array di lavoro
    struct Array stringOut;//stringa finale
    struct Array spacer;
    spacer.n = 1;
    spacer.array = (char*)calloc(1,sizeof(char));
    stringOut.n = string->n;//la dimensione di default deve essere almeno grande quanto l'input
    stringOut.array = (char*)calloc(stringOut.n,sizeof(char));
    string2.n = string->n;
    string2.array = (char*)calloc(string2.n,sizeof(char));
    
    do
    {
        if((string->array)[i] != '\0')
        {
            if((string->array)[i] != ' ' && isalpha((string->array)[i]))//se non inclontriamo un carattere spaziatore
            {
                
                //dopo che l'if ha girato abbiamo raggiunto l'inizio della prima frase quindi salviamo
                //l'inizio nella variabile j
                j = i;
                //a questo punto dobbiamo far avanzare la variabile i fino a quando non arriviamo alla fine della parola.
                while((string->array)[i] != ' ' && isalpha((string->array)[i]) && (string->array)[i] != '\0')
                {
                    i++;
                }
                Stringclear(&string2);//la stringa viene ripulita da precedenti frasi
                StringCopy(&string2,string,j,i);
                //qua la stringa va modificata
                SafeStrcat(&string2,&stringOut);
                //una volta lavorata usiamo realloc per ingrandire la frase di output e ci mettiamo in fondo la frase modificata
            }
            else
            {
                
                spacer.array[0] = (string->array)[i];//viene salvato il carattere spaziatore
                SafeStrcat(&spacer,&stringOut);//dovrebbe concatenare (da verificare se la riallocazione funziona su elementi di struct)
                i++;
            }
            
        }  
    } 
    while ((string->array)[i] != '\0');

    printf("stringa : %s , i : %d,j : %d, striga2 : %d",stringOut.array,i,j,string2.n);
}

void PhraseEditor1()
{

}

int main()
{
    struct Array *string;
    ReadString(string);
    SeparetorUnifier(string);
}  

