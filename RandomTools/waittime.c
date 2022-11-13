#include <time.h>
void WaitSeconds(float secondi)
{
    time_t now = clock();
    for(; (clock() - now) < (secondi * CLOCKS_PER_SEC) ;) // Waits for 3 seconds 
    {

    } 
}
//servirebbe un thread, con le aperte graffe fa della roba per x secondi