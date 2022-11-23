#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void robConnect();

struct Stanza {
    char nome[20];
    int larghezza;
    int lunghezza;
    int area;
    int ostacoli;
    int priorita;
};

int main() {

    int numero_stanze = 5;
    //robConnect();    // connettiti al robot (loading)


    return 0;
}

void robConnect() { // Funzione che simula l'effetto di caricamento
    printf("\t\tConnessione a Rob8");
    printf("\n\t\t");

    int percentage = 0;
    char loading[] = "--------------------";
    printf("%s %d%%", loading, percentage);
    for(int i = 0; i < strlen(loading); i++) {
        //printf("\33[2K\r");
        loading[i] = 'o';
        percentage = (i + 1) * 5;
        printf("\n\t\t");
        printf("%s %d%%", loading, percentage);
        usleep(50*1000);    // 50 milisecondi (50*1000 microsecondi)
    }
}

void aggiungiStanza() {

}

void mostraInfoStanza(char nomeStanza[]) {

}
