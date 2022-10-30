#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>   //libreria che contiene la funzione sleep()
#define N 10          //dimensione orizzontale e verticale della matrice
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

struct Coordinate
{
    int x;
    int y;
};

char boundcheck(int matrixSize,int pseudoX, int pseudoY)//controlla che le nuove ipotetiche coordinate siano all'interno dei limiti
{
    if((pseudoX<matrixSize && pseudoY<matrixSize)&&(pseudoX>-1 && pseudoY>-1)) 
    return "0";

    return "1";
}

char performStep(int matrix[N][N],int direction, struct Coordinate coordinate,char lettera)
{
    int pseudoX = coordinate.x;
    int pseudoY = coordinate.y;

    char state;

    switch (direction)//applica direction alle pseudo cordinate
    {
        case 0:// è un passo verso sinistra quindi -1 alla x 

            pseudoX += -1;
            break;

        case 1:// è un passo verso il basso quindi -1 alla y

            pseudoY += -1;
            break;
        
        case 2:// è un passo verso destra quindi +1 alla x
           
            pseudoX += 1;
            break;

        case 3:// è un passo in altro quindi un +1 alla y

            pseudoY += 1;
            break;
    }

    if(boundcheck(N,pseudoX,pseudoY) == "0")//se è dentro i bordi
    {

        if(matrix[pseudoX][pseudoY] == "." )//se il posto è libero
        {
            matrix[pseudoX][pseudoY] = lettera;
            coordinate.x = pseudoX;
            coordinate.y = pseudoY; 
            // lettera assegnata al posto
            lettera++;// lettera sucessiva per il prossimo giro
            state = "0"; // passo effettuato!
        }
        else{state = "1";}//il posto è occupato

    }
    else{state = "1";}//le coordinate non sono dentro i bordi

    return state;
}

char DirectionChooser(int matrix[N][N],struct Coordinate coordinate,char lettera)
{
    char state;//lo stato indica se il passo è stato eseguito o no;  0:passo  eseguito, 1:passo non eseguito
    int direction;
    char directions[4]={"0","0","0","0"};//0 significa che la direzione non è stata ancora provata
    int directionsCounter=0;//questo counter conta ogni volta che una strada diversa è stata provata
                            //quando il contatore arriva a 4 è risulta che la strada scelta è bloccata il programma termina
    do
    {
        direction=rand()%4; //generazione del passo 
        if(directions[direction] == "0")//se non è ancora stato fatto
        {
            directionsCounter++;
            directions[direction] = 1;
            state = performStep(matrix,direction,coordinate,lettera) ;
            if(state == "0")//vengono resettati gli eventuali tentativi e il counter
            { 
                directions[0] = "0";
                directions[1] = "0";
                directions[2] = "0";
                directions[3] = "0";

                directionsCounter = 0;
            }
            else{ state = "1"; }
            
        }
    } 
    while (state == "1" && directionsCounter < 4 );//se è bloccato e le direzioni non sono state provate tutte allora continua
    
    //viene generata la direzione
    //si controlla che non è gia stata provata in directions
    //se è gia stata provata si ripete il ciclo e lo stato viene messo a blocked
    //altrimenti si segna il tentativo in directions e si aumenta il counter
    //Se è possibile fare il passo allora lo stato passa a libero ed esce dal while
    //a quel punto lo stato viene restituito
    
}

void Update( struct Coordinate coordinate,char matrix[N][N],char lettera)//funzione loop
{
    do
    {
       RefreshScreen(matrix,"a");//stampo la matrice 
    } 
    while (DirectionChooser(matrix,coordinate,lettera) == "0" && lettera != "[" );
    //il programma continua se il passo è stato fatto e le lettere non sono finite( il carattere dopo la Z è [ nell'asciicode)
                                                                                  
}


void RefreshScreen(int matrix[N][N],char flag)
{
    if(flag=="R")
    {
        for(int x=0;x<N;x++)//rest della matrice e stampa
        {      
            printf("\n");     
            for (int y=0;y<N;y++)
            {
                matrix[x][y]='.';
                printf("%c ", matrix[x][y]);
            }
        }  
        gotoxy(0,0);//porto il cursore alla posizione iniziale
        return;
    }

    for(int x=0;x<N;x++)//stampa della matrice
    {        
        printf("\n");   
        for(int y=0;y<N;y++)
        {
            printf("%c ", matrix[x][y]);
        }
    } 
    gotoxy(0,0);//porto il cursore alla posizione iniziale
}

int main() 
{

    printf("\e[?25l");//nascondo il cursore 
    system("cls");//pulisco lo schermo

    char lettera='A'; 
    char matrix[N][N]; //spazio di movimento
    struct Coordinate coordinate;//posizione corrente dentro la matrice
    srand(time(NULL));//selezione del seed per la generazione randomica

    coordinate.x=rand()%N; //genero una posizione randomica per la casella iniziale e le assegno il valore 'A'
    coordinate.y=rand()%N;
    //matrix[coordinate.x][coordinate.y]=lettera; deprecato in quanto l'incremento della lettera avviene dopo

    RefreshScreen(matrix,"R");//stampo la matrice azzerata
    Update(coordinate,matrix,lettera);
}
