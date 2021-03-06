#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* Lo scopo del file e' di ottenere il peso di un file mediante la funzione
ftell() */

int main(int argc, char *argv[]) {
    FILE *fp;
    int fsize = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage; %s <filepath>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fp = fopen(argv[1], "rb");

    if (fp == NULL) {
        fprintf(stderr, "Err. Cannot open image: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Sposta il 'file position indicator' alla fine del file
    fseek(fp, 0, SEEK_END);

    if (ferror(fp)) {
        fprintf(stderr, "Err. fseek() failed.");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    /* La funzione ftell() ritorna la posizione del 'file position indicator',
    che corrisponde  al numero di byte del file stesso. */
    fsize = ftell(fp);

    if (fsize == -1) {
        fprintf(stderr, "Err. ftell() failed: %s", strerror(errno));
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    
    printf("The size of \'%s\' is: %d byte\n", argv[1], fsize);

    return(EXIT_SUCCESS);
}
