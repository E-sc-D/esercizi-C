#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
    {
        return cbsi.dwCursorPosition;
    }
    else
    {
        // The function failed. Call GetLastError() for details.
        COORD invalid = { 0, 0 };
        return invalid;
    }
}

void WaitSeconds(float secondi)
{
    time_t now = clock();
    for(; (clock() - now) < (secondi * CLOCKS_PER_SEC) ;); // Waits for 3 seconds  
}

int stringReader(int lenght,char *stringa)
{
    char buffer;
    int i;
    for(i = 0 ;  i < lenght - 1  &&   (buffer = getchar()) != '\n'  ; i++)  //nel momento che premi enter nella tastiera l'input viene mandato al buffer 
    {                                                                      //per ogni giro getchar legge un carattere dal buffer
        stringa[i] = buffer;                                              //premendo enter non solo invii il buffer ma prima invii il carattere \n al buffer
    }
    stringa[i] = '\0';
    return i;//gli effettivi caratteri scritti nell'array
}

void CriptedlineSim(int stringlen,short *y,short *x)
{

    srand(time(NULL));//nuovo seme per la generazione di numeri casuali
    time_t now = clock();
    *y = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).Y;//posizione corrente del cursore
    *x = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).X;
    char randm;

    for(; (clock() - now) < (3 * CLOCKS_PER_SEC) ;) // Waits for 3 seconds 
    {
        
        for(int i = 0 ; i < stringlen ; i++)
        {
            if( !iscntrl( randm = rand() % 256 ) )//randomizzo un numero da 0 a 255( codice ascii ) e verifico che non sia un carattere di 
            printf("%c",randm);             //controllo (\n \r ecc)
        } 
        gotoxy(*x,*y);  
        
    } 
 
}

void RandomWriting(char *stringa,int stringlen,short *Y)
{
    int direction;
    char directions[stringlen] ;//0 significa che la direzione non è stata ancora provata
    int directionsCounter = 0;//questo counter conta ogni volta che una strada diversa è stata provata
                            //quando il contatore arriva a 4 è risulta che la strada scelta è bloccata il programma termina
    do
    {
        direction = rand() % stringlen; //generazione del passo 
        if(directions[direction] != '1')//se non è ancora stato fatto
        {
            directionsCounter++;
            directions[direction] = '1'; 
            gotoxy(direction + 1,*Y);
            printf("%c",stringa[direction]);   
            WaitSeconds(0.1f); 
        }
    }
    while(directionsCounter < stringlen);
}

int main() 
{   
    short x,y;
    int len;
    //printf("%d",GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).Y);
    printf("\nInserisci la lunghezza massima della stringa\n");
    scanf("%d",&len);
    fflush(stdin);//il \n dell'enter rimane in buffer e causa la uscita prematura dalla funzione stringreader

    char stringa[len+1];//la lunghezza +1 serve per il carattere terminatore

    len = stringReader(len+1 , stringa);
    CriptedlineSim(len, &y , &x);
    RandomWriting(stringa,len,&y);
    return 0;
}

