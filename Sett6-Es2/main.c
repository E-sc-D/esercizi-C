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
char Movement(int*,int*);
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

void Refresh(int width,int height, char **campoMinato,int *x, int *y)
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

char Movement(int *x,int *y)
{ 
    char inp;
    while((inp = (char)getch()) != 't' && inp !='m')
    {
        switch (inp)
        {

            case 'w':
            *y -= 2;
            break;
            
            case 's':
            *y += 2;
            break;

            case 'a':
            *x -= 3;
            break;

            case 'd':
            *x += 3;
            break;
        
            default:
            break;
        }

        gotoxy(*x,*y);
        
    }
}

int Scout(int x,int y,char **campoMinato)
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
        if( campoMinato[x + directions[i][0]][y + directions[i][1]] == '#' )//controlla attorno la coordinata ricevuta se ce una mina
        {
            mines++;
        }
    }

    return mines;
}

int Uncover(int *x,int *y,char **campoVisibile,char **campoMinato)
{
    int mineTrovate;
    List lista;
    if(campoMinato[*x][*y] != '#')
    {
        struct Coordinata coord;
        coord.x = *x;
        coord.y = *y;
        AddElement(&lista,coord);
        int mineTrovate;
       
           mineTrovate = Scout(*x,*y,campoMinato);
           if( mineTrovate > 0)
           {
               printf("%d",mineTrovate);
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
    int state = 0;
    GeneraMine(0,5,5,campoMinato);
    system("cls");

    while(input != 'm')//game loop
    {
        

        Refresh(5,5,campoMinato,&x,&y);//aggiorna il campoMinato
        input = Movement(&x,&y);//ascolta per input del giocatore

        if(input == 't')//scopri casella
        {
            Uncover()
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
    