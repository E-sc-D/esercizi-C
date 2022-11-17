#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

//prototipi
void inizializza_gioco();
int cambiaDifficolta();
int** GeneraCampo(int,int);
void StampaCampo(int,int,int**);
void GeneraMine(int,int,int,int**);



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
   
   int **campoMinato = GeneraCampo(10, 5);//genero una matrice con malloc 
   StampaCampo(10,5,campoMinato);
   GeneraMine(3,10,5,campoMinato);
   StampaCampo(10,5,campoMinato);

   return 0;
}

void inizializza_gioco(int difficolta)
{
    int row = 10;
    int column = 10;
    int campo[row][column];
}

void GeneraMine(int difficoltà,int width,int height,int **campoMinato) 
{
    int numeroMine;     // quante mine ci saranno sul campo
    // assegnare il numeroMine in base alla difficolta
    numeroMine = 5; // per adesso assegno 5 (statico)

    int minePos[numeroMine][2]; // array che contiene la posizione di ogni mina
    // assegno 2 colonne perché avrò la posizione x e la posizione y della mina

    int flag = 0;

    //inizializzando la prima mina fuori do margine di controllo al for che altrimenti confronterebbe la prima mina con se stessa *
    //entrando quindi in un loop infinito     
    for (int i = 0; i < numeroMine; i++) //ciclo che avanza nell'array di mine
    {
        do {
                flag = 0;

                //genero una mina con coordinate casuali

                minePos[i][0] = rand() % height;        // colonna
                minePos[i][1] = rand() % width;         // riga

                printf("\ni = %d Mine position: col = %d, row = %d", i, minePos[i][0], minePos[i][1]);
                if (i == 0) // La prima mina generata non puo essere confrontata con altre (dato che non esistono), quindi possiamo prenderla per buona
                    campoMinato[minePos[i][0]][minePos[i][1]] = -1;
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
                       campoMinato[minePos[i][0]][minePos[i][1]] = -1;//piazzo le mine nel campo minato
                    }
                }
            }
        while (flag == 1);  //...una nuova mina sovrascriverà questa ricominciando da capo
    }   
}

int** GeneraCampo(int width,int height)
{

    int** campoMinato = (int**)malloc(height * sizeof(int*)); //alloco nella heap un array di puntatori
    for(int i = 0 ; i < width ; i++)
    {
        campoMinato[i] = (int*)malloc(width * sizeof(int));//dentro l'array di puntatori alloco degli array di interi
    }
    printf("campo generato in teoria...\n");

    for(int i = 0; i < height ; i++)//pulisce la matrice... si potrebbe usare calloc
    {
        for(int j = 0; j < width ; j++)
        {
            campoMinato[i][j] = 0;
        }
    }

   return campoMinato;
}

void StampaCampo(int width,int height, int **campoMinato)//funziona, ma perche?
{
    printf("\n");
    for(int i = 0; i < height ; i++)
    {
        for(int j = 0; j < width ; j++)
        {
            printf("\t%d",campoMinato[i][j]);
        }
        printf("\n");
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

void Game()
{
    //inizializzo il campo minato 
    //inizializzo la posizione del cursore a zero e le relative coordinate
    //ascolto per le freccette e per enter
    //premendo una freccetta le coordinate devono variare in base a un enum
    //il carattere che simboleggia il prato deve essere colorato nella posizione dove ci troviamo
    
    int **campoMinato;

    
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
    