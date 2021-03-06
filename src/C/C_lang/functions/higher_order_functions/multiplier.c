#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int somma(int (*f)(int), int start, int end);
int moltiplica(int x);

int main(void) {
    int n = somma(moltiplica, 1, 10);
    printf("\nThe result is: %d\n", n);

    return(EXIT_SUCCESS);
}

int moltiplica(int x) {
    return x * x;
}

/* La funzione somma() accetta 3 parametri:
- il primo parametro e' la funzione 'int (*p)(int par)', ovvero un puntatore a
funzione 'p' che accetta il parametro 'par' e che restituisce un intero.
- il secondo parametro e' l'intero 'start',
- il terzo parametro e' l'intero 'end'.
*/
int somma(int (*f)(int), int start, int end) {
    int val;
    int ris = 0;

    for (val=start; val<end; val++) {
        printf("%3d + %2d\n", ris, (*f)(val));
        ris = ris + (*f)(val);
    }

    return ris; 
}
