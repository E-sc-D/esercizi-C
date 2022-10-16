#include <stdio.h>
#include <math.h>

int main() 
{
    int a = 10, b = 5, c;

    c = a + b; // Somma
    printf("Somma: %d + %d = %d\n", a, b, c);

    c = a - b; // Differenza
    printf("Differenza: %d - %d = %d\n", a, b, c);

    c = a * b; // Moltiplicazione
    printf("Moltiplicazione: %d * %d = %d\n", a, b, c);

    c = a / b; // Divisione
    printf("Divisione: %d / %d = %d\n", a, b, c);

    c = a % b; // Modulo
    printf("Modulo: %d %% %d = %d\n", a, b, c);

    // Incremento sul suffisso
    printf("Incremento: %d++ = %d\n", ++a, a);
    // Decremento sul suffisso
    printf("Decremento: %d-- = %d\n", --a, a);

    // Incremento sul prefisso
    printf("Incremento sul prefisso: ++%d = %d\n", a, ++a);
    // Decremento sul prefisso
    printf("Decremento sul prefisso: --%d = %d\n", a, --a);


    if (a == b) 
    {   // Se a è uguale a b
        printf("%d e uguale a %d\n", a, b);
    }

    if (a != b) 
    {   // Se a è diverso da b
        printf("%d e diverso da %d\n", a, b);
    }

    if (a > b) 
    {
        printf("%d e maggiore di %d\n", a, b);
    }

    if (a < b)
    {
        printf("%d e minore di %d\n", a, b);
    }

    if (a >= b) 
    {
        printf("%d e maggiore o uguale a %d\n", a, b);
    }

    if (a <= b)
    {
        printf("%d e minore o uguale %d\n", a, b);
    }



    c = a;
    c += c;
    printf("%d += %d corrisponde a %d\n", a, a, c);

    c = a;
    c -= c;
    printf("%d -= %d corrisponde a %d\n", a, a, c);

    c = a;
    c *= c;
    printf("%d *= %d corrisponde a %d\n", a, a, c);

    c = a;
    c /= c;
    printf("%d /= %d corrisponde a %d\n", a, a, c);

    c = a;
    c %= c;
    printf("%d %= %d corrisponde a %d\n", a, a, c);


    c = a++;
    printf("facendo c = a++ c ottiene il valore di a prima che gli venga sommato 1 infatti c = %d a= %d\n",c,a);
    
    c = --a;
    printf("facendo c = --a prima viene tolto 1 ad a poi il valore viene dato a c, infatti c = %d a= %d\n",c,a);

    c =2147483648;
    printf("inserendo un valore troppo alto all'interno di una variabile causiamo un overflow, in questo caso il numero restituito equivale al numero piu basso + l'overflow ovvero %d\n",c);

    c= 10.1853f;
    printf("cercando di inserire il valore 10.1853 dentro una variabile int otteniamo : %d",c);


    //funzioni di math.h

    double d;

    d = sqrt(4.0);
    printf("la funzione  sqrt(4) restituisce= %f\n",d);

    d = sin(1.0);
    printf("la funzione sin(1) restituisce  %f\n",d);

    d = cos(1.0);
    printf("la funzione cos(1) restituisce  %f\n",d);

    d = tan(1.0);
    printf("la funzione tan(1) restituisce  %f\n",d);

    d = asin(0.7);
    printf("la funzione asin(0.7)restituisce  %f\n",d);

    d = acos(0.0);
    printf("la funzione acos(0) restituisce  %f\n",d);

    d = atan(45.0);
    printf("la funzione atan(45) restituisce  %f\n",d);

    d = exp(1.0);
    printf("la funzione e(1) restituisce  %f\n",d);
    
    /*d = pow10(1.0);
    printf("la funzione pow10(1) restituisce  %f",d);*/

    d = log(1.0);
    printf("la funzione log(1) restituisce  %f\n",d);

    d = log10(1.0);
    printf("la funzione log10(1) restituisce  %f\n",d);

    d = fabs(-1.0);
    printf("la funzione fabs(-1) restituisce  %f\n",d);

    d = hypot(1.0,0.0);
    printf("la funzione hypot(1,0) restituisce  %f\n",d);

    d = atan2(1.0,1.0);
    printf("la funzione atan2(1,1) restituisce  %f\n",d);

    d = pow(5.0,1.0);
    printf("la funzione pow(5,1) restituisce  %f\n",d);

    d = frexp(2.0,&a);
    printf("la funzione frexp(2,&a) restituisce  %f\n",d);
    
    return 0;
    
    
    
}
