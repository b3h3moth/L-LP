#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#define MAX_STR 32

struct rec {
    int id;
    char alias[MAX_STR];
    char email[MAX_STR];
};

typedef struct rec Record;

/* The program's purpose is to write a full structure inside a binary file, 
read the binary file and store data inside a new structure, and then print out
the result. 

Rember we are working with binary file, 'cat' commant doesn't work on it */

int main(void) {
    Record *address_book, *address_book_backup;
    FILE *fin, *fout;
    char *filedata = "db.bin";
    char *my_alias = "b3h3m0th";
    char *my_mail = "mymail@email.org";

    // It allocates the proper amount of memory
    address_book = malloc(sizeof(Record));

    // Structure initialization
    address_book->id = 1973;
    strncpy(address_book->alias, my_alias, strlen(my_alias));
    strncpy(address_book->email, my_mail, strlen(my_mail));

    // Open a 'binary' file
    if ((fout = fopen(filedata, "wb+")) == NULL) {
        fprintf(stderr, "Err.(%d) fopen(out) - %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    // It writes the structure to the file and then close stream
    fwrite(address_book, sizeof(Record), 1, fout);
    fclose(fout);

    // It allocates memory for new 'Record'
    address_book_backup = malloc(sizeof(Record));
    // It opens the input file
    fin = fopen(filedata, "rb");

    if (fin == NULL) {
        fprintf(stderr, "Err.(%d) fopen(in) - %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    // It reads from binary file
    fread(address_book_backup, sizeof(Record), 1, fin);
    fclose(fin);

    printf("   id: %d\n", address_book_backup->id);
    printf("alias: %s\n", address_book_backup->alias);
    printf("email: %s\n", address_book_backup->email);

    return(EXIT_SUCCESS);
}
