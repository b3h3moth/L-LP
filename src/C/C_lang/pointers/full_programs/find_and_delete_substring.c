#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char *match(char *source, char *str);
char *delete_substring(char *source,  char *substr);

/* Lo scopo del programma e' di creare una funzione che cerchi una
sottostringa all'interno di una stringa, individuarla e stamparla dal 
carratere successivo dell'individuazione fino alla fine e solo la 
prima occorrenza. */

int main(void) {
    char *buf = "Get up Stand up, Stand up for your rights, Bob Marley";
    char *str = "our";

    char *res = delete_substring(buf, str);
    printf("Default string: %s\n", buf);
    printf("Substring to search: %s\n", str);
    printf("The result: %s\n", res);

    return(EXIT_SUCCESS);
}

// Controlla la corrispondenza 'char by char' di 'str' in source
char *match(char *source, char *str) {
    while (*str != '\0')
        if (*source++ != *str++)
            return NULL;

    return source;
}

// Rimuove i caratteri non necessari
char *delete_substring(char *source,  char *substr) {
    char *next;

    // Cerca la prima occorrenza della sottostringa
    while (*source != '\0') {
        next = match(source, substr);
        
        if (next != NULL)
            break;
        source++;
    }

    // La sottostringa non e' stata individuata
    if (*source == '\0')
        return NULL;

    // La sottostringa e' stata individuata 
    while ((*source++ == *next++)) {
        ;
    }

    return source;
}
