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

void WaitSeconds(int secondi)
{
    time_t now = clock();
    for(; (clock() - now) < (secondi * CLOCKS_PER_SEC) ;); // Waits for 3 seconds  
}

void stringReader(int lenght,char *stringa)
{
    char buffer;
    int i;
    for(i = 0 ;  i < lenght-1  &&   (buffer = getchar()) != '\n'  ; i++)//nel momento che premi enter nella tastiera l'input viene mandato al buffer 
    {                                                                      //per ogni giro getchar legge un carattere dal buffer
        stringa[i] = buffer;                                              //ricordando che enter non solo manda l'input, ma è anch'esso un carattere
    }
    stringa[i] = '\0';
}

void CriptedlineSim(int stringlen)
{
    srand(time(NULL));//nuovo seme per la generazione di numeri casuali
    time_t now = clock();

    for(; (clock() - now) < (3 * CLOCKS_PER_SEC) ;) // Waits for 3 seconds 
    {
        
        for(int i = 0 ; i < stringlen ; i++)
        {
            printf("%c",(rand()%256));
        } 
        gotoxy(0,0);  
        
    } 
 
}
int main() 
{
    int len;
    printf("%d",GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).Y);
    printf("\nInserisci la lunghezza massima della stringa\n");
    scanf("%d",&len);
    fflush(stdin);//il \n dell'enter rimane in buffer e causa la uscita prematura dalla funzione stringreader

    char stringa[len+1];//la lunghezza +1 serve per il carattere terminatore

    stringReader(len+1,stringa);
    CriptedlineSim(len+1);
    return 0;
}

