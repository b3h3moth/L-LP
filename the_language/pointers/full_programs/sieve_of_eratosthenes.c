#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 100

/* Lo scopo del programma e' la realizzazione dell'algoritmo detto il crivello
di Eratostene per il calcolo di numeri primi. */

int main(void) {
    char sieve[SIZE]; // Il crivello e' un array
    char *sp;
    int num;

    // setta ciascun elemento del crivello a 1
    for (sp = sieve; sp < &sieve[SIZE]; sp++) 
        *sp = 1;

    // Inizia la rimozione dei multipli del
    for (num = 3; num += 2; )
    return(EXIT_SUCCESS);
}
