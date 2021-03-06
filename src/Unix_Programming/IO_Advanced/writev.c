#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <sys/types.h>

enum { NBUF = 3 };

/* Lo scopo del programma e' di scrivere un buffer multiplo in un file mediante
la funzione writev() */

int main(void) {
    struct iovec iov[NBUF];
    ssize_t nbyte;
    char filename[] = "bob_marley_songs.txt";
    int flags = O_WRONLY | O_CREAT;
    int mode = S_IRWXU | S_IXGRP | S_IRWXG | S_IROTH | S_IXOTH;
    int fd, i;
    char *buf[] = {
        "Coming in from the cold.\n",
        "Could you be loved.\n",
        "Redemtion Song.\n"
    };

    fd = open(filename, flags, mode);
    if (fd == -1) {
        fprintf(stderr, "Err. open() failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Riempimento della struttura iov
    for (i=0; i<NBUF; i++) {
        iov[i].iov_base = buf[i];
        iov[i].iov_len = strlen(buf[i]) + 1;
    }

    // Scrittura del file
    nbyte = writev(fd, iov, NBUF);
    if (nbyte == -1) {
        fprintf(stderr, "Err. writev() failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } else
        printf("File \'%s written\'\n", filename);

    close(fd);

    return(EXIT_SUCCESS);
}
