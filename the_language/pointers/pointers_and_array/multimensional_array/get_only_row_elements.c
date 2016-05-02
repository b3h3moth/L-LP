#include <stdio.h>
#include <stdlib.h>

/* Lo scopo del programma e' di stampare a video solo il primo elemento di
ciascuna riga della matrice, utilizzando solo i puntatori */

int main(void) {
    int matrix[4][4] = { 
        {10,  20,  30,   40},
        {50,  60,  70,   80},
        {90,  100, 110, 120},
        {130, 140, 150, 160}
    };

    // Dichiarazione di un puntatore ad array
    int (*mp)[4];

    for (mp = matrix; mp<&matrix[4]; mp++)
        printf("%d\n", *(*mp) );

    return(EXIT_SUCCESS);
}
