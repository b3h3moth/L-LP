#include <stdio.h>
#include <stdlib.h>

/*
    Lo scopo del programma e' di fornire la 'byte representation' di differenti
    programmi oggetto 
*/

typedef unsigned char *byte_pointer;

// Fornisce l'indirizzo della sequanza di byte di 'start'
void show_bytes(byte_pointer start, int len) {
    int i;
    for (i=0; i<len; i++)
        printf(" %.2x", start[i]);
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer) &x, sizeof(int));
}

int main(void) {

    return(EXIT_SUCCESS);
}
