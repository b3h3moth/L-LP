#include <stdio.h>
#include <stdlib.h>

/*
Ogni programma ha a dispozione una "environment list", ovvero un puntatore ad un
vettore di stringhe, all'interno del quale ciascuna stringa (null-terminated) 
indica una variabile d'ambiente - nella forma "nome = valore" - ; ogni
variabile d'ambiente contiene specifiche informazioni sul sistema in uso, 
o meglio, sull'ambiente in cui il programma sta girando.

E' possibile accedere alla lista delle variabili d'ambiente "environment list"
mediante la variabile esterna 'environ', oppure utilizzando un terzo argomento
della funzione main(), ossia envp[], tuttavia altamente sconsigliato sia da ISO
C sia da POSIX.
*/

extern char **environ;

int main(void) {
   char **var;
  
   /* stampa tutte le variabili di ambiente definite */
   for (var = environ; *var != NULL; ++var) {
      printf("%s\n", *var);
   }

    return(EXIT_SUCCESS);
}

