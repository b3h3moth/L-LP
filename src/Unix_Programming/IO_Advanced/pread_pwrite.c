#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *buf;
    int in_fd, out_fd, nread;
    off_t in_offst, out_offst;
    size_t in_size, out_size;

    if (argc != 7) {
        fprintf(stderr, "Usage: %s <input file, offset, size>"
                " <output file, offset, size>", argv[0]);
        exit(EXIT_FAILURE);
    }

    in_fd = open(argv[1], O_RDONLY);
    if (in_fd < 0) {
        fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
        exit(EXIT_FAILURE);
    }

    out_fd = open(argv[4], O_WRONLY);
    if (out_fd < 0) {
        fprintf(stderr, "Unable to write %s: %s\n", argv[4], strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Setup input output offset
    in_offst = strtol(argv[2], NULL, 10);
    out_offst = strtol(argv[5], NULL, 10);

    // Set up input output size
    in_size = strtol(argv[3], NULL, 10);
    out_size = strtol(argv[6], NULL, 10);

    buf = malloc(sizeof(in_size));

    if (in_size < out_size)
        out_size = in_size;


    return(EXIT_SUCCESS);
}