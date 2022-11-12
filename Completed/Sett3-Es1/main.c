#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int continentTable[5][5] =
    {
        { 1, 1, 1, 3, 3 },
        { 1, 1, 1, 3, 3 },
        { 2, 2, 2, 3, 3 },
        { 2, 2, 2, 3, 3 },
        { 2, 2, 2, 3, 3 }
    };

    int tableWidth = sizeof(continentTable) / sizeof(continentTable[0]);
    int tableHeight = sizeof(continentTable[0]) / sizeof(continentTable[0][0]);

    int randomX;
    int randomY;
    int chosenContinent = 0;
    char chosenContinue = 'n';
    int score = 0;

    printf("Legenda continenti\n1) Eurasia\n2) Estasia\n3) Oceania\n"); // Prints all possible continents with their number
    printf("Prova ad indovinare in quale continente sono situate le coordinate!\n");
    printf("Avrai un tempo limitato per visualizzarle, premi un tasto per continuare.");
    getchar(); // Waits for user input

    do
    {
        do
        {
            score++;

            srand(time(NULL));
            randomX = 1 + (rand() % tableWidth);
            randomY = 1 + (rand() % tableHeight);

            // Prints coordinates and saves number of printed chars
            int coordsChars = printf("Coordinate: (%d, %d)", randomX, randomY);
            fflush(stdout); // Flush stdout content to terminal

            time_t now = clock();
            for(; (clock() - now) < (3 * CLOCKS_PER_SEC) ;); // Waits for 3 seconds

            printf("\r"); // Moves cursor to the beginning
            int messageChars = printf("Il tempo e' finito, coordinate nascoste!"); // Prints a message on the coordinates and saves number of chars
            for(int i = 0; i < coordsChars - messageChars; i++) // If message wasn't long enough, prints spaces
            {
                printf(" "); // Prints a "coordsChars - messageChars" number of spaces, if negative or zero doesn't print anything
            }
            printf("\n");
            
            do
            {
                printf("Continente [1, 2, 3]: ");
                scanf("\n%d", &chosenContinent);

                if(chosenContinent != 1 && chosenContinent != 2 && chosenContinent != 3)
                {
                    printf("Puoi inserire solo 1, 2 o 3!\n");
                }
            }
            while(chosenContinent != 1 && chosenContinent != 2 && chosenContinent != 3);
        }
        while(continentTable[randomY - 1][randomX - 1] == chosenContinent);

        printf("Congratulazioni, hai sbagliato!\n");
        printf("Il tuo punteggio e' %d.\n", score);
    
        printf("Premi un tasto per continuare [0 = non continuare]: ");
        scanf("\n%c", &chosenContinue);
    }
    while(chosenContinue != '0');
}
