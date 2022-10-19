#include <stdio.h>
#include <math.h>

int main() 
{
    int a = 10, b = 5, c;
    int binA = 1010, binB = 101, binC;
    double d;

    // Operatori base
    c = a + b;
    printf("Somma: %d + %d = %d\n", a, b, c);
    c = a - b;
    printf("Differenza: %d - %d = %d\n", a, b, c);
    c = a * b;
    printf("Moltiplicazione: %d * %d = %d\n", a, b, c);
    c = a / b;
    printf("Divisione: %d / %d = %d\n", a, b, c);
    c = a % b;
    printf("Modulo: %d %% %d = %d\n", a, b, c);

    //Operatori bitwise
    binC = binA & binB;
    printf("Operatore AND: %d & %d = %d\n", binA, binB, binC);
    binC = binA | binB;
    printf("Operatore OR: %d & %d = %d\n", binA, binB, binC);
    binC = binA ^ binB;
    printf("Operatore XOR: %d & %d = %d\n", binA, binB, binC);
    binC = ~binA;
    printf("Complemento ad 1: ~%d = %d\n", binA, binC);
    binC = binA << binB;
    printf("Shift a sinistra: %d & %d = %d\n", binA, binB, binC);
    binC = binA >> binB;
    printf("Shift a destra: %d & %d = %d\n", binA, binB, binC);

    // Confronti
    if (a == b) 
    {
        printf("%d e' uguale a %d\n", a, b);
    }
    if (a != b) 
    {
        printf("%d e' diverso da %d\n", a, b);
    }
    if (a > b) 
    {
        printf("%d e' maggiore di %d\n", a, b);
    }
    if (a < b)
    {
        printf("%d e' minore di %d\n", a, b);
    }
    if (a >= b) 
    {
        printf("%d e' maggiore o uguale a %d\n", a, b);
    }
    if (a <= b)
    {
        printf("%d e' minore o uguale %d\n", a, b);
    }

    // Operatori logici
    if(!(a > b))
    {
        printf("%d non e' maggiore di %d\n", a, b);
    }
    if(a > b && b < a)
    {
        printf("%d e' maggiore di %d e, ovviamente, %d e' minore di %d\n", a, b, b, a);
    }
    if(a > b || b > a)
    {
        printf("Uno è maggiore dell'altro\n");
    }

    // Assegnazione con operazioni
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
    printf("%d %%= %d corrisponde a %d\n", a, a, c);

    // Side effects
    c = a++;
    printf("Con c = a++, c ottiene il valore di a prima che gli venga sommato 1, infatti c = %d, a = %d\n", c, a);
    c = ++a;
    printf("Con c = ++a, c ottiene il valore di a dopo che gli viene sommato 1, infatti c = %d, a = %d\n", c, a);
    c = a--;
    printf("Con c = a--, c ottiene il valore di a prima che gli venga sottratto 1, infatti c = %d, a = %d\n", c, a);
    c = --a;
    printf("Con c = --a, c ottiene il valore di a dopo che gli viene sottratto 1, infatti c = %d, a = %d\n", c, a);

    // Superamento range di valori
    c = 2147483648;
    printf("In caso di overflow la variabile conterra' il limite minimo piu' il valore in eccesso ovvero %d\n", c);

    // Conversione implicita
    c = 10.1853f;
    printf("Cercando di inserire il valore 10.1853 dentro una variabile intera otteniamo %d\n", c);


    // Funzioni di math.h
    d = sqrt(4.0);
    printf("La funzione sqrt(4) restituisce %f\n", d);

    d = sin(1.0);
    printf("La funzione sin(1) restituisce %f\n", d);

    d = cos(1.0);
    printf("La funzione cos(1) restituisce %f\n", d);

    d = tan(1.0);
    printf("La funzione tan(1) restituisce %f\n", d);

    d = asin(0.7);
    printf("La funzione asin(0.7) restituisce %f\n", d);

    d = acos(0.0);
    printf("La funzione acos(0) restituisce %f\n", d);

    d = atan(45.0);
    printf("La funzione atan(45) restituisce %f\n", d);

    d = exp(1.0);
    printf("La funzione e(1) restituisce %f\n", d);
    
    d = pow10(2.0);
    printf("La funzione pow10(1) restituisce %f\n", d);

    d = log(1.0);
    printf("La funzione log(1) restituisce %f\n", d);

    d = log10(1.0);
    printf("La funzione log10(1) restituisce %f\n", d);

    d = fabs(-1.0);
    printf("La funzione fabs(-1) restituisce %f\n", d);

    d = hypot(1.0,0.0);
    printf("La funzione hypot(1,0) restituisce %f\n", d);

    d = atan2(1.0,1.0);
    printf("La funzione atan2(1,1) restituisce %f\n", d);

    d = pow(5.0,1.0);
    printf("La funzione pow(5,1) restituisce %f\n", d);

    d = frexp(2.0, &a);
    printf("La funzione frexp(2,%d) restituisce %f\n", a, d);
    
    return 0;    
}
