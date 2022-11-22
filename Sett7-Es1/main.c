#include <stdio.h>
#include <string.h>
void robConnect();

int main() {

    robConnect();


    return 0;
}

struct Stanza {
    char nome[20];
    int larghezza;
    int lunghezza;
    int area;
    int ostacoli;
    int priorita;
};

void robConnect() {
    printf("\t\tConnessione a Rob8");
    printf("\n\t\t");

    char loading[] = "--------------------";
    printf("%s", loading);
}