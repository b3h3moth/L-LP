#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_LEN  50

/* Lo scopo del programma e' di inizializzare un array di MAX_LEN elementi 
con un numero casuale, dopodiche' scrivere l'intero array in file binario 
mediante la funzione fwrite(). Infine leggere i dati scritti.  */

int main(void) {
    FILE *fout, *fin;
    char *binfile = "data.bin";
    int data[MAX_LEN], datacopy[MAX_LEN], n;

    /*
    const char *unix_os[] = { 
        "Debian GNU/Linux", "OpenBSD", "FreeBSD", 
        "HP-UX", "Solaris", "Mac OS X", "NetBSD", 
        "OpenSolaris", "AIX", "Minix"
    };
    */

    fout = fopen(binfile, "wb");

    if (fout == NULL) {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }

    for (int i=0; i<MAX_LEN; i++)
        *(data + i) = rand() % 100;

    n = fwrite(data, sizeof(data[0]), sizeof(data)/sizeof(data[0]), fout);
    fclose(fout);

    printf("Written \'%d\' elements and \'%d\' byte to file: \'%s\'\n", \
            n, n * sizeof(int), binfile);

    // Lettura dal file binario appena creato 'binfile'
    fin = fopen(binfile, "r");

    if (fout == NULL) {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }

    n = fread(datacopy, sizeof(int), MAX_LEN, fin);
    for(int i=0; i<MAX_LEN; i++)
        printf("data[%d] = %d\n", i, datacopy[i]);

    fclose(fin);

    return(EXIT_SUCCESS);
}
