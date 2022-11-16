#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

void inizializza_gioco();
int cambiaDifficolta();
int** GeneraCampo(int,int);
void StampaCampo(int,int,int**);
int main() 
{
    /*srand(time(NULL));

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
   
   int **campoMinato = GeneraCampo(10, 5);//cerco di generare una matrice con malloc
   printf("Campo generato\n");//ok va
   //scanf("%d");//va
   campoMinato[1][1] = 0;
   printf("il valore alla pos 1,1 è %d",campoMinato[1][1]);//cazzo esplode 
   //StampaCampo(10,5,campoMinato);//anche questo esplode
   //fflush(stdin);//e salta questo
   //scanf("%d");//questo
   return 0;//forse anche questo boh
}

void inizializza_gioco(int difficolta)
{
    int row = 10;
    int column = 10;
    int campo[row][column];
}

void generaMine(int **matrix, int row, int column, int difficolta) 
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

                minePos[i][0] = rand() % row;   //genero una mina con coordinate casuali
                minePos[i][1] = rand() % column;

                for (int j = i; j > 0; j--)     //torno indietro nell'array di mine per controllare se ho delle mine con la stessa posizione
                {   
                    if ((minePos[i][0] == minePos[j][0]) && (minePos[i][1] == minePos[j][1]))//se ne trovo una uguale... 
                        flag = 1;
                }
                    
            }
        while (flag == 1);  //...una nuova mina sovrascriverà questa ricominciando da capo
    }

    //piazzo le mine nel campo minato
}

int** GeneraCampo(int length,int width)
{
    int** campoMinato = (int**)malloc(width * sizeof(int*)); //alloco nella heap un array di puntatori
    for(int i = 0 ; i < length ; i++)
    {
        campoMinato[i] = (int*)malloc(length * sizeof(int));//dentro l'array di puntatori alloco degli array di interi
    }
    printf("campo generato in teoria...\n");

    return campoMinato;
   
}

void StampaCampo(int length,int width,int **campoMinato)
{
     for(int i = 0; i < width ; i++)
    {
        for(int j = 0; j < length ; j++)
        {
            campoMinato[i][j] = j;
            printf("%d",campoMinato[i][j]);
        }
        printf("\n");
    }
    free(campoMinato);
    printf("campo stampato?...");
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