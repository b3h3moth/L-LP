#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

/* Lo scopo del programma e' di associare, mediante le funzioni della
famiglia sqlite3_bind_*(), alcuni parametri ad altre variabili statiche, e 
infine incapsularli nella stringa SQL da passare al database. */

int main(int argc, char *argv[]) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int flags = SQLITE_OPEN_READWRITE;
    int rc = 0;
    int idx = -1;

    /* I 'bound parameters' sono dei token inseriti all'interno della stringa
    SQL, sono come una sorta di segnaposto, collocati nella stringa stessa 
    prima della preparazione della dichiarazione. Successivamente, dopo che la
    dichiarazione e' stata preparata e prima dell'esecuzione, e' possibile
    associare (bind) un valore al parametro.

    SQLite supporta cinque stili di 'Statement parameters':
    ?           parametro anonimo con indice automatico. L'indice e' unico,
                sequenziale e inizia da 1;
    ?<index>    parametro con indice numerico esplicito;
    :<name>     parametro denominato con indice automatico;
    @<name>     parametro denominato con indice automatico;
    $<name>     parametro denominato con indice automatico.
    */
    char *sql_str = "INSERT INTO addressbook (fullname, alias, email)"
                    "VALUES(?, ?, ?)";

    // Stringhe da associare ai parametri
    char *str_fullname = "foobar";
    char *str_alias = "foo";
    char *str_email = "foo@bar.baz";

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <database name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Library initialization
    if (sqlite3_initialize() != SQLITE_OK) {
        fprintf(stderr, "Err. Unable to initialize the library.\n");
        exit(EXIT_FAILURE);
    }

    // Open database connection
    rc = sqlite3_open_v2(argv[1], &db, flags, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Err. can't create database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    // Prepare the statement
    rc = sqlite3_prepare_v2(db, sql_str,-1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Err. Can't prepare the statement.\n");
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    /* Prima di eseguira la dichiarazione, i parametri possono essere associati
    (bind) a un valore mediante una delle funzioni della famiglia 
    sqlite3_bind_*(). Come accennato in precedenza, tali funzioni devono essere
    invocate dopo la preparazione della dichiarazione ma prima dell'
    esecuzione della dichiarazione stessa, ovvero antecedentemente all'
    invocazione della funzione sqlite3_step().
    Ad ogni riga possono essere associati valori diversi. */
    
    /* Bind the first value
    Si utilizza la funzione sqlite3_bind_text() poiche' si sta lavorando con
    delle stringhe */
    rc = sqlite3_bind_text(stmt, 1, str_fullname, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Err. Binding the value (%i).\n", rc);
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    // Bind the second value
    rc = sqlite3_bind_text(stmt, 2, str_alias, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Err. Binding the value (%i).\n", rc);
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    // Bind the third value
    rc = sqlite3_bind_text(stmt, 3, str_email, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Err. Binding the value (%i).\n", rc);
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
        fprintf(stderr, "Err. Stepping through the statement.\n");

    // Release prepared statement resources
    sqlite3_finalize(stmt);
    // Close database connection
    sqlite3_close_v2(db);
    // Shutdown library initialization
    sqlite3_shutdown();

    return(EXIT_SUCCESS);
}
