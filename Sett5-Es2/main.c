#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void stringReader(int lenght,char *stringa)
{
    char buffer;
    int i;
    for(i = 0 ;  i < lenght-1  &&   (buffer = getchar()) != '\n'  ; i++)//nel momento che premi enter nella tastiera l'input viene mandato al buffer 
    {                                                                      //per ogni giro getchar legge un carattere dal buffer
       stringa[i] = buffer;                             //ricordando che enter non solo manda l'input, ma è anch'esso un carattere
    }

    stringa[i] = '\n';//aggiungo il terminatore all'ultimo elemento della stringa

    printf("%c\n",stringa[10]);
}
int main() 
{
    char stringa[10+1];
    stringReader(10+1,stringa);
    printf("ecco la stringa %s",stringa);
    return 0;
}

