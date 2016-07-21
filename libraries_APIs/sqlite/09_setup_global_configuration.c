#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

/* Allorquando si lavora con un programma che contiene la libreria SQLite e in 
altri contesti dove serve una configurazione della libreria specifica, 
puo' risultare utile avere una settaggio globale della libreria stessa. 
A tale scopo e' stata implemenata l'interfaccia sqlite3_config(int, ...).

Nota: Nella maggior parte dei casi la configurazione di default risulta essere
      piu' che sufficiente.
 
L'interfaccia sqlite3_config() deve essere invocata prima dell'inizializzazione
della libreria con sqlite3_initialize() e dopo lo shutdown della stessa 
mediante sqlite3_shutdown(), altrimenti sara' resituito l'errore SQLITE_MISUSE.

Il primo argomento dell'interfaccia e' un intero che determina le opzioni di
configurazione della libreria SQLite, i successivi argomenti invece dipendono
dal primo, ovvero dal valore intero che e' stato inserito. 

Valore di ritorno: Allorquando l'opzione di configurazione dovesse andare a 
buon fine ritornebbe SQLITE_OK, altrimenti un codice d'errore diverso da zero.
*/

int main(void) {
    return(EXIT_SUCCESS);
}
