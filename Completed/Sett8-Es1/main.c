#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
struct consoleBuffer
{
    int count;
    char buffer[100];
};

int readString(char type,void *pointer)
{
    struct consoleBuffer buffer;
    int i = 0;
    buffer.buffer[i] = getche();  
    while(buffer.buffer[i]!='\n')
    {
        i++;
        buffer.buffer[i] = getche();
    }
    
   
}
int main()
{
    char *pointer;
    
}  

//Metodi per la lettura di una stringa
/* scanf("%s",pointer);
printf("%s ",pointer); */