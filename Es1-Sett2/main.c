#include <stdio.h>
#include <math.h>

int main() {
    int a = 10, b = 5, c;

    c = a + b; // Somma
    printf("%d + %d = %d\n", a, b, c);

    c = a - b; // Differenza
    printf("%d - %d = %d\n", a, b, c);

    c = a * b; // Moltiplicazione
    printf("%d * %d = %d\n", a, b, c);

    c = a / b; // Divisione
    printf("%d / %d = %d\n", a, b, c);

    c = a % b; // Modulo
    printf("%d %% %d = %d\n", a, b, c);

    /*// Incremento sul suffisso
    printf("%d++ = %d\n", a, a++);
    //Decremento sul suffisso
    printf("%d-- = %d\n", a, a);*/


    if (a == b) {   // Se a è uguale a b
        printf("%d e uguale a %d\n", a, b);
    }

    if (a != b) {   // Se a è diverso da b
        printf("%d e diverso da %d\n", a, b);
    }

    if (a > b) {
        printf("%d e maggiore di %d\n", a, b);
    }

    if (a < b){
        printf("%d e minore di %d\n", a, b);
    }

    if (a >= b) {
        printf("%d e maggiore o uguale a %d\n", a, b);
    }

    if (a <= b){
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





    return 0;
}
