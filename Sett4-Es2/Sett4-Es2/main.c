#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>   //libreria che contiene la funzione sleep()

#define N 10          //dimensione orizzontale e verticale della matrice

int main() {
    char lettera='A' /*variabile che serve a vistare le caselle visitate*/, array[N][N]; //matrice
    int riga, colonna, direzione, controlloDirezioni[4]={0,0,0,0}; //0=in alto, 1=a destra, 2=in basso, 3=a sinistra

    srand(time(NULL));

    for(riga=0;riga<N;riga++){ //popolo la matrice con il carattere '.' e la stampo
        printf("\n");
        for (colonna=0;colonna<N;colonna++){
            array[riga][colonna]='.';
            printf("%c ", array[riga][colonna]);
        }
    }

    riga=rand()%N; //genero una posizione randomica per la casella iniziale e le assegno il valore 'A'
    colonna=rand()%N;
    array[riga][colonna]=lettera;

    while(lettera<='Z'){
        if(controlloDirezioni[0]==1 && controlloDirezioni[1]==1 && controlloDirezioni[2]==1 && controlloDirezioni[3]==1) {
            printf("Non è possibile continuare"); //se dalle iterazioni precedenti tutte le direzioni risultano bloccate il programma si ferma
            break;
        }
        sleep(1); //prende come argomento un unsigned int che indica il numero di secondi da aspettare prima di continuare a eseguire
        system("cls"); //cancella tutto quello che c'è sullo schermo, funzione della libreria stdlib.h

        for(int i=0;i<N;i++) { //stampa della matrice
            printf("\n");

            for (int j = 0; j < 10; j++) {
                printf("%c ", array[i][j]);
            }

        }

        direzione=rand()%4; //segue la regola precedente, quindi 0=in alto, 1=a destra, 2=in basso, 3=a sinistra

        switch (direzione) {

            case (0):

                if (riga==0 || controlloDirezioni[0]==1 || array[riga-1][colonna]!='.' ){ //il primo controllo vede se è attaccata a una parete, il secondo se una iterazione precedente ha già provato ad andare lì
                    controlloDirezioni[0]=1;                                              //e il terzo vede se c'è una lettera nella posizione dove vuole andare
                    continue; //se la direzione non è disponibile riprova l'iterazione senza aumentare la lettera
                }else{
                    for(int i=0;i<4;i++){ //quando va avanti il controllo delle direzioni riparte da zero
                        controlloDirezioni[i]=0;
                    }
                    lettera++;
                    riga--;
                    array[riga][colonna]=lettera;

                }
                break;

            case (1):

                if (colonna==9 || controlloDirezioni[1]==1 || array[riga][colonna+1]!='.'){ //tutti gli altri case funzionano esattamente come il primo, ma con tutte le altre direzioni
                    controlloDirezioni[1]=1;
                    continue;
                }else{
                    for(int i=0;i<4;i++){
                        controlloDirezioni[i]=0;
                    }
                    lettera++;
                    colonna++;
                    array[riga][colonna]=lettera;
                }
                break;

            case (2):

                if (riga==9 || controlloDirezioni[2]==1 || array[riga+1][colonna]!='.' ){
                    controlloDirezioni[2]=1;
                    continue;
                }else{
                    for(int i=0;i<4;i++){
                        controlloDirezioni[i]=0;
                    }
                    lettera++;
                    riga++;
                    array[riga][colonna]=lettera;
                }
                break;

            case (3):

                if (colonna==0 || controlloDirezioni[3]==1 || array[riga][colonna-1]!='.' ){
                controlloDirezioni[1]=1;
                continue;
                }else{
                    for(int i=0;i<4;i++){
                        controlloDirezioni[i]=0;
                    }
                lettera++;
                colonna++;
                array[riga][colonna]=lettera;
                }
                break;

        }

    }
    return 0;
}
