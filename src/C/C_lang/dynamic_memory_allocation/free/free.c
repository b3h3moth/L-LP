#include <stdio.h>
#include <stdlib.h>

/* L'allocazione dinamica della memoria consente il rilascio della memoria
stessa quando non piu' utilizzata, a tale scopo si usa la funzione free(), il
cui argomento deve essere un puntatore ad un indirizzo di memoria allocato con
malloc(), calloc() o realloc().

Nota: La memoria liberata sara' rilasciata sullo heap.

HEADER    : <stdlib.h>
PROTOTYPE : void free(void *ptr);
SEMANTICS : La funzione free() rilascia lo spazio di memoria puntato da 'ptr'.
RETURNS   : Non ritorna alcun valore.
--------------------------------------------------------------------------------
Se alla funzione free() dovesse essere passato NULL, non succedera' alcunche',
inoltre dereferenziare un puntatore appena rilasciato portera' a comportamenti
indefiniti, per cui sarebbe lecito assegnare NULL al puntatore rilasciato, tale
tecnica peraltro eviterebbe problemi di "dangling pointers".

Dangling pointer: Un puntatore che e' stato rilasciato ma che referenzia ancora
                  la memoria precedentente allocata, esso infatti punta ad un
                  oggetto non valido.
                  Un dangling pointer potrebbe essere causa di:
                  - un comportamento indefinito qualora vi si accedesse;
                  - segmentation fault;
                  - potenziali rischi per la sicurezza.
*/

int main(void) {
    int *ptr;
    
    /* Alloca la memoria per contenere un tipo di dato intero */
    ptr = (int*) malloc(sizeof(int));
    
    /* Lo spazio di memoria viene ora rilasciato */
    free(ptr);

    /* Nessun cambiamento nel programma */
    free(NULL);

    return(EXIT_SUCCESS);
}
