#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_THREAD 5

/* Se un thread all'interno di un processo dovesse invocare exit(), _Exit(), 
oppure _exit(), l'intero processo sarebbe terminato, e questo non va bene
perche' thread e processi dovrebbero essere indipendenti per cio' che concerne
lo stato di uscita.

I thread comtemplano un meccanismo di terminazaione meno invasivo rispetto alle
funzioni precedenti, supportano infatti tre modalita' di terminazione del loro 
flusso di esecuzione, senza peraltro terminare anche il processo:

1 - Un thread semplicemente ritorna dalla routine di avvio;
2 - Un thread puo' essere cancellato da un altro thread nello stesso processo;
3 - Un thread puo' invocare la funzione pthread_exit().

La funzione pthread_exit() termina il thread chiamante, ritornando, volendo, lo
stato di terminazione.

HEADER    : <pthread.h>
PROTOTYPE : void pthread_exit(void *ret_val);
SEMANTICS : La funzione pthread_exit() termina il thread chiamante e ritorna il
            relativo valore mediante la variabile 'retval'.
RETURNS   : Questa funzione non ritorna
--------------------------------------------------------------------------------
*/

void *thr_func(void *arg);

int main(void) {
    pthread_t thr[MAX_THREAD];
    int i, thr_err;

    /* Si provvede alla creazione di MAX_THREAD thread */
    for (i=0; i<MAX_THREAD; i++) {
        
        printf("Creazione thread %d: ", i);
        
        if ((thr_err = pthread_create(&thr[i],NULL, thr_func, (void*)i)) != 0) {
            fprintf(stderr, "Err. pthread_create() %s\n", strerror(thr_err));
            exit(EXIT_FAILURE);
        }

        if (pthread_join(thr[i], NULL) != 0) {
            fprintf(stderr, "Err. pthread_join() %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    pthread_exit(NULL);
    
    return(EXIT_SUCCESS);
}

void *thr_func(void *arg)
{
    pthread_t tid = pthread_self();
    printf("Thread '%d' - TID %lu - Address %x\n", 
            (int*)arg, tid, pthread_self());

}
