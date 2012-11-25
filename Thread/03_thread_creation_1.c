#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

/*
Thread addizionali possono essere creati mediante la funzione pthread_create():

HEADER    : <pthread.h>
PROTOTYPE : int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                               void *(*start_routine) (void *), void *arg);
SEMANTICS : La funzione pthread_create() prende 4 argomenti:
            - pthread_t *thread, e' un puntatore a pthread_t;
            - pthread_attr_t *attr, gli attributi del nuovo thread, qualora non
              si volessero modificare, sara' sufficiente inserire NULL;
            - void *(*start_routine) (void *), il codice da eseguire. Trattasi 
              di un puntatore a funzione che prende un puntatore a void e
              restituisce un puntatore a void;
            - void *arg, sono gli eventuali argomenti da passare, qualora non
              si volessero passare argomenti, sara' sufficiente inserire NULL.
RETURNS   : 0 in caso di successo, numero di errore in caso di errore
--------------------------------------------------------------------------------
*/

void *thr_func(void *arg);

int main() {
    pthread_t new_thr;
    char str[] = "POSIX thread";

    /* Si invoca la funzione pthread_create() per creare un nuovo thread:
    - Il primo parametro e' un puntatore a new_thr;
    - il secondo parametro e' definito NULL, per cui saranno utilizzati gli
      attributi di default;
    - Il terzo paramero thr_func() e' la funzione che il thread eseguira' 
      allorquando sara' avviato, non appena la funzione terminera' vorra' dire
      che anche il thread sara' terminato. In questo caso la funzione stampa
      semplicemente un messaggio;
    - Il quarto parametro e' l'argomento passato alla funzione, e' possibile
      inviare una quantita' arbitraria di dati, in questo caso si utilizza una
      semplice stringa.

    Il nuovo thread creato inizia la propria esecuzione dall'indirizzo della
    funzione, nel caso specifico da thr_func.
    */
    if ((pthread_create(&new_thr, NULL, thr_func, str)) != 0) {
        fprintf(stderr, "Err. pthread_create() %s\n", strerror(errno));
        exit(EXIT_SUCCESS);
    }
    /* NOTA: 
    Da notare che se non fosse stato creato un nuovo thread il programma 
    sarebbe stato composto comunque da un singolo thread, poiche' ogni programma
    corrisponde ad un thread, detto anche "thread principale", per cui mediante
    la funzione pthread_create() si sarebbe creato secondo. */

    sleep(1);

    printf("Main thread\n");

    return(EXIT_SUCCESS);
}

void *thr_func(void *arg)
{
    printf("New Thread: %s\n", arg);
}

/* COMPILAZIONE: $ gcc programma.c -lpthread */
