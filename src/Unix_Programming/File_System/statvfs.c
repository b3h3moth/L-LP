#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <errno.h>
#include <sys/statvfs.h>

/* Lo scopo del programma e' di ottenere informazioni su un file system montato.
Il device relativo al file siystem viene fornito in input. */

int main(int argc, char *argv[]) {
    char *pathname = NULL;
    size_t len = 0;
    int my_err = 0;
    errno = 0;
    struct statvfs device;

    if (argc != 2) {
        fprintf(stdout, "Usage: %s 'pathname'\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    len = strlen(argv[1]) + 1;
    pathname = malloc(len * sizeof(char));
    strncpy(pathname, argv[1], len);

    if (statvfs(pathname, &device) == -1) {
        my_err = errno;
        fprintf(stdout, "Err.%d statvfs(); %s\n", my_err, strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("%31s: %s\n", "file system", pathname);
    printf("%31s: %lu (byte)\n", "fs block size", device.f_bsize);
    printf("%31s: %lu (byte)\n", "fundamental fs block size", device.f_frsize);
    printf("%31s: %lu\n", "total number of blocks", device.f_blocks);
    printf("%31s: %lu\n", "total number of free blocks", device.f_bfree);
    printf("%31s: %lu\n", "number of free blocks available", device.f_bavail);
    printf("%31s: %lu\n", "total number of i-nodes", device.f_files);
    printf("%31s: %lu\n", "total number of free i-nodes", device.f_ffree);
    printf("%31s: %lu\n", "number of i-nodes available", device.f_favail);
    printf("%31s: %lu\n", "File System ID", device.f_fsid);
    printf("%31s: %lu\n", "Maximum length of filenames", device.f_namemax);
    printf("%31s: %s\n", "flags (Read only)",
            (device.f_flag & ST_RDONLY) == ST_RDONLY ? "yes" : "no");
    printf("%31s: %s\n", "flags (No Suid)",
            (device.f_flag & ST_NOSUID) == ST_NOSUID ? "yes" : "no");

    free(pathname);

    return(EXIT_SUCCESS);
}
