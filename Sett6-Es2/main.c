#include <stdio.h>

#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "list.c"
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

//prototipi
void inizializza_gioco();
int cambiaDifficolta();
char** GeneraCampo(int,int);
void StampaCampo(int,int,char**);
void GeneraMine(int,int,int,char**);
char Movement(int*,int*,int*,int*,int,int);
void Game();


int main() 
{
    srand(time(NULL));
    /*

    int scelta = 0;
    int difficolta = 1;

    do {
        system("cls");
        printf("1) Gioca");
        printf("\n\tDifficolta: %d", difficolta);
        printf("\n2) Cambia difficolta");
        printf("\n3) Esci\r\n");

        scanf("%d", &scelta);

        if (scelta == 2) 
        {
            difficolta = cambiaDifficolta(difficolta);
            scelta = 0;
        }
    }
    while (scelta > 3 || scelta < 1);

    switch (scelta) 
    {
        case 1: gioca(difficolta);
        case 3: exit(0);
    } */
   
    List lista = NewList(); //c# feeling!!! // Il problema era che l'head della lista non è necessariamente settato a NULL, 
    struct Coordinata coordinata = {5, 4};
/*
    printf("lol\n");
    AddElement(&lista, emptyCoordinata);
    printf("%d lala %d\n",GetLastElement(&lista)->coordinata.x,length(&lista));
    AddElement(&lista,coordinata);
    printf("%d lala %d\n",GetLastElement(&lista)->coordinata.x,length(&lista));
    DeleteLastElement(&lista);
    printf("%d lala \n",GetLastElement(&lista)->coordinata.x);
    
*/
    Game();
    printf("gioco finito");
    return 0;
}
/* struct Coordinata Dilatazione(struct Coordinata coordinata,int xoffset,int y offset)//converte le cordinate matriciali in coordinate per la stampa in console( consente spazi tra gli elementi della matrice)
{

} */

void inizializza_gioco(int difficolta)
{
    int row = 10;
    int column = 10;
    int campo[row][column];
}

void GeneraMine(int difficolta,int width,int height,char **campoMinato) 
{
    int numeroMine;     // quante mine ci saranno sul campo
    // assegnare il numeroMine in base alla difficolta
    numeroMine = 5; // per adesso assegno 5 (statico)

    int minePos[numeroMine][2]; // array che contiene la posizione di ogni mina
    // assegno 2 colonne perché avrò la posizione x e la posizione y della mina

    int flag = 0;
  
    for (int i = 0; i < numeroMine; i++) //ciclo che avanza nell'array di mine
    {
        do {
                flag = 0;

                //genero una mina con coordinate casuali

                minePos[i][0] = rand() % height;        // colonna
                minePos[i][1] = rand() % width;         // riga

                printf("\ni = %d Mine position: col = %d, row = %d", i, minePos[i][0], minePos[i][1]);

                if (i == 0) // La prima mina generata non puo essere confrontata con altre (dato che non esistono), quindi possiamo prenderla per buona
                    campoMinato[minePos[i][0]][minePos[i][1]] = '#';

                for (int j = i; j > 0; j--) //torno indietro nell'array di mine per controllare se ho delle mine con la stessa posizione
                {   
                    if ((minePos[j][0] == minePos[j - 1][0]) && (minePos[j][1] == minePos[j - 1][1]))//se ne trovo una uguale...
                    {
                        printf("\nTrovata una mina gia generata. Ripetiamo la generazione");
                        flag = 1;
                        break;
                    }
                    else
                    {
                       campoMinato[minePos[i][0]][minePos[i][1]] = '#';//piazzo le mine nel campo minato
                    }
                }
            }
        while (flag == 1);  //...una nuova mina sovrascriverà questa ricominciando da capo
    }   
}

char** GeneraCampo(int width,int height)
{

    char** campoMinato = (char**)malloc(height * sizeof(char*)); //alloco nella heap un array di puntatori
    for(int i = 0 ; i < width ; i++)
    {
        campoMinato[i] = (char*)malloc(width * sizeof(char));//dentro l'array di puntatori alloco degli array di interi
    }
    printf("campo generato in teoria...\n");

    for(int i = 0; i < height ; i++)//pulisce la matrice... si potrebbe usare calloc
    {
        for(int j = 0; j < width ; j++)
        {
            campoMinato[i][j] = 254;
        }
    }

   return campoMinato;
}

void StampaCampo(int width,int height, char **campoMinato)
{
    printf("\n\n");
    for(int i = 0; i < height ; i++)
    {
        for(int j = 0; j < width ; j++)
        {
            printf("  %c",campoMinato[i][j]);
        }
        printf("\n\n");
    }
    //free(campoMinato);
}

int cambiaDifficolta(int difficolta) 
{
    difficolta += 1;

    if(difficolta > 5)  // La difficolta massima è 5
        difficolta = 1;

    return difficolta;
}

void Refresh(int width,int height, char **campoMinato,int *x, int *y)//aggiungere offsett per generalizzare la stampa
{
    gotoxy(0,0);
    for(int i = 0; i < height ; i++)
    {
        for(int j = 0; j < width ; j++)
        {
            printf("  %c",campoMinato[i][j]);
        }
        printf("\n\n");
    }
    gotoxy(*x,*y);
}

char Movement(int *x,int *y,int *X,int *Y,int width,int height)
{ 
    char inp;
    while((inp = (char)getch()) != 't' && inp !='m')
    {
        switch (inp)
        {

            case 'w':
            if(*Y > 0)
            {
                *y -= 2;
                *Y -= 1; 
            } 
            break;
            
            case 's':
            if( *Y < height - 1)
            {
                *y += 2;
                *Y += 1;
            }
            break;

            case 'a':
             if(*X > 0)
            {
                *x -= 3;
                *X -= 1; 
            } 
            
            break;

            case 'd':
             if( *X < width - 1)
            {
                *x += 3;
                *X += 1; 
            }
            
            break;
        
            default:
            break;
        }

        gotoxy(*x,*y);
        
    }
}

int Scout(int X,int Y,char **campoMinato,int width,int height)//x è y , y è x ricordare che direction[x][1] è per le y
{
    int mines = 0;
    int directions[8][2] =
    {
        {0,1},  //top
        {1,1},  //top-right
        {1,0},  //right
        {1,-1}, //bottom-right
        {0,-1}, //bottom
        {-1,-1},//bottom-left
        {-1,0}, //left
        {-1,1}  //top-left
    };

    for(int i = 0 ; i < 8; i++)
    {
        if((X + directions[i][1] > -1 && X + directions[i][1] < width) && (Y + directions[i][0] > -1 && Y + directions[i][0] < height))//controllo per verificare che il punto sia dentro il campo
        {
            if( campoMinato[X + directions[i][1]][Y + directions[i][0]] == '#' )//controlla attorno la coordinata ricevuta se ce una mina
            {
                mines++;
            }
        }
    }

    return mines;
}

int Uncover(int *X,int *Y,char **campoVisibile,char **campoMinato)//!sostituire x,y con coordinate
{
    int mineTrovate;
    List lista;
    if(campoMinato[*Y][*X] != '#')
    {
        struct Coordinata coord;
        coord.x = *X;
        coord.y = *Y;
        AddElement(&lista,coord);
       
           mineTrovate = Scout(*Y,*X,campoMinato,5,5);//!da convertire a lista.nodo->coordinate al posto di x,y
           if( mineTrovate > 0)
           {
               campoMinato[*Y][*X] = '0' + mineTrovate;//conversione da int a char 
               gotoxy(0,20);
               printf("%d,%d\n",*X,*Y);
               
           }
       
    }
    //return hai perso
} 

void Game()
{
    //inizializzo il campo minato 
    //inizializzo la posizione del cursore a zero e le relative coordinate
    //ascolto per le freccette e per enter
    //premendo una freccetta le coordinate devono variare in base a un enum
    //il carattere che simboleggia il prato deve essere colorato nella posizione dove ci troviamo
    
    char **campoMinato = GeneraCampo(5,5);
    char **campoVisibile = GeneraCampo(5,5);
    char input = 'w';
    int x = 3,y = 1; //posizione del cursore 
    int X = 0,Y = 0;
    int state = 0;
    GeneraMine(0,5,5,campoMinato);
    system("cls");

    while(input != 'm')//game loop
    {
        

        Refresh(5,5,campoMinato,&x,&y);//aggiorna il campoMinato, ha bigogno delle coordinate per la stampa
        input = Movement(&x,&y,&X,&Y,5,5);//ascolta per input del giocatore gli servono le coordinate per muovere il cursore e per aggiornare le coordinate della matrice

        if(input == 't')//scopri casella
        {
            Uncover(&X,&Y,campoVisibile,campoMinato);
        }
    }
    
}

/*  //esempio con puntatori multipli

    int value = 5;
    int *pt1;
    int **pt2;
    int ***pt3;
    
    pt1 = &value;
    pt2 = &pt1;
    pt3 = &pt2;
    printf("%d , %d , %d valore di value \n",*pt1,**pt2,***pt3);//valore di value
    printf("%p , %p , %p indirizzo di value\n", pt1,*pt2,**pt3);//indirizzo di value
    printf("%p , %p  boh\n",&(*pt2),pt2); //chiamando il nome    
    
    
*/
    