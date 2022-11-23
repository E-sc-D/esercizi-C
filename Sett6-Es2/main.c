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
char Movement(struct Coordinata*,int,int);
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
    return 0;
}

//converte le cordinate matriciali in coordinate per la stampa in console( consente spazi tra gli elementi della matrice )
struct Coordinata Dilatazione(struct Coordinata *coordinata,int colonnaOffset,
int rigaOffset,int colonnaMoltiplicatore,int rigaMoltiplicatore)
{
    struct Coordinata coordinataCursore = {colonnaOffset,rigaOffset};
    coordinataCursore.colonna += colonnaMoltiplicatore*coordinata->colonna;
    coordinataCursore.riga += rigaMoltiplicatore*coordinata->riga;

    return coordinataCursore;
}

void inizializza_gioco(int difficolta)
{
    int row = 10;
    int column = 10;
    int campo[row][column];
}

void GeneraMine(int difficolta,int colonne,int righe,char **campoMinato) 
{
    int numeroMine;     
    numeroMine = 10; 
    int minePos[numeroMine][2]; // array che contiene la posizione di ogni mina
    int flag = 0;

    for (int i = 0; i < numeroMine; i++) //ciclo che avanza nell'array di mine
    {
        do {
                flag = 0;

                //genero una mina con coordinate casuali

                minePos[i][0] = rand() % righe;        
                minePos[i][1] = rand() % colonne;         

                if (i == 0) // La prima mina generata non puo essere confrontata con altre (dato che non esistono), quindi possiamo prenderla per buona
                {
                     campoMinato[minePos[i][0]][minePos[i][1]] = '#';
                }
                        
                for (int j = i - 1; j > -1; j--) //torno indietro nell'array di mine per controllare se ho delle mine con la stessa posizione
                {   
                    
                    if ((minePos[i][0] == minePos[j][0]) && (minePos[i][1] == minePos[j][1]))//se ne trovo una uguale...
                    {
                       flag = 1;//si continua il while
                       j = -1;
                    }
                    
                }
                if(flag == 0)
                {
                    campoMinato[minePos[i][0]][minePos[i][1]] = '#';//piazzo le mine nel campo minato
                    printf("\n mina piazzata %d, %d",minePos[i][1],minePos[i][0]);
                }
                
            }
        while (flag == 1);  //...una nuova mina sovrascriverà questa ricominciando da capo
    }   
}

char** GeneraCampo(int colonne,int righe)
{

    char** campoMinato = (char**)malloc(colonne * sizeof(char*)); //alloco nella heap un array di puntatori
    for(int i = 0 ; i < colonne ; i++)
    {
        campoMinato[i] = (char*)malloc(righe * sizeof(char));//dentro l'array di puntatori alloco degli array di interi
    }
    printf("campo generato in teoria...\n");

    for(int i = 0; i < colonne ; i++)//pulisce la matrice... si potrebbe usare calloc
    {
        for(int j = 0; j < righe ; j++)
        {
            campoMinato[i][j] = 254;
        }
    }

   return campoMinato;
}

int cambiaDifficolta(int difficolta) 
{
    difficolta += 1;

    if(difficolta > 5)  // La difficolta massima è 5
        difficolta = 1;

    return difficolta;
}

void Refresh(int colonne,int righe, char **campoMinato,struct Coordinata coordinataCursore)//aggiungere offsett per generalizzare la stampa
{
    gotoxy(0,0);
    for(int i = 0; i < righe ; i++)
    {
        for(int j = 0; j < colonne ; j++)
        {
            printf("  %c",campoMinato[j][i]);
        }
        printf("\n\n");
    }
    gotoxy(coordinataCursore.colonna,coordinataCursore.riga);
}

char Movement(struct Coordinata *coordinataMatrice,int colonne,int righe)
{ 
    char input;
    struct Coordinata coordinataCursore;

    while((input = (char)getch()) != 't' && input !='m')
    {
        switch (input)
        {

            case 'w':
                if(coordinataMatrice->riga > 0)
                {
                    coordinataMatrice->riga -= 1; 
                } 
            break;
            
            case 's':
                if( coordinataMatrice->riga < righe - 1)
                {
                    coordinataMatrice->riga += 1;
                }
            break;

            case 'a':
                if(coordinataMatrice -> colonna > 0)
                {
                    coordinataMatrice->colonna -= 1; 
                } 
            break;

            case 'd':
                if( coordinataMatrice->colonna < colonne - 1)
                {
                    coordinataMatrice->colonna += 1; 
                }  
            break;
        
            default:
            break;
        }

        coordinataCursore =  Dilatazione(coordinataMatrice,3,1,3,2);
        gotoxy(coordinataCursore.colonna,coordinataCursore.riga);
        
    }
}

int Scout(struct Coordinata *coordinataMatrice ,char **campoMinato,int colonne,int righe)//x è riga ,riga è x ricordare che direction[x][1] è per leriga
{
    int mines = 0;
    int colonna = coordinataMatrice->colonna;
    int riga = coordinataMatrice->riga; 
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
        if((riga + directions[i][1] > -1 && riga + directions[i][1] < righe) && (colonna + directions[i][0] > -1 && colonna + directions[i][0] < colonne))//controllo per verificare che il punto sia dentro il campo
        {
            if( campoMinato[colonna + directions[i][0]][riga + directions[i][1]] == '#' )//controlla attorno la coordinata ricevuta se ce una mina
            {
                mines++;
            }
        }
    }

    return mines;
}

int Uncover(struct Coordinata *coordinataMatrice ,char **campoVisibile,char **campoMinato)//!sostituire x,y con coordinate
{
    int mineTrovate;
    List lista = NewList();
    int colonna = coordinataMatrice->colonna;
    int riga = coordinataMatrice->riga;

    if(campoMinato[colonna][riga] != '#')
    {
        struct Coordinata coord;
        AddElement(&lista,*coordinataMatrice);
       
           mineTrovate = Scout(coordinataMatrice,campoMinato,6,5);//!da convertire a lista.nodo->coordinate al posto di x,y
           if( mineTrovate > 0)
           {
               campoVisibile[colonna][riga] = '0' + mineTrovate;//conversione da int a char    
           }      

       
    }
    else{ return 1;}
    //return hai perso
} 

void Game()
{
    
    char **campoMinato = GeneraCampo(6,5);
    char **campoVisibile = GeneraCampo(6,5);
    char input = 'w';
    struct Coordinata coordinataMatrice = {0,0};
    int state = 0;
    gotoxy(0,20);
    GeneraMine(0,6,5,campoMinato);
    gotoxy(0,0);
    system("cls");
    Refresh(6,5,campoVisibile,Dilatazione(&coordinataMatrice,3,1,3,2)); 

    while(input != 'm')//game loop
    { 
        Refresh(6,5,campoVisibile,Dilatazione(&coordinataMatrice,3,1,3,2));
        input = Movement(&coordinataMatrice,6,5);

        if(input == 't')
        {
            state = Uncover(&coordinataMatrice,campoVisibile,campoMinato);
        }
        if(state == 1)
        {
            input = 'm';
            Refresh(6,5,campoMinato,Dilatazione(&coordinataMatrice,3,1,3,2));
            gotoxy(0,20);
            printf("GAMEOVER");
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
    