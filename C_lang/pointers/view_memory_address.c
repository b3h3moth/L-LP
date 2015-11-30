#include <stdio.h>
#include <stdlib.h>

typedef unsigned char BYTE;

int main(void) {
    unsigned int addr;
    int i, nbyte;
    BYTE *ptr;
    char str_addr[] = "Address of";

    printf("%9s %5s %#x\n", str_addr, "main", (unsigned int) main);
    printf("%9s %5s %#x\n", str_addr, "addr", (unsigned int) &addr);

    // Immissione di un indirizzo di memoria in formato esadecimale
    printf("\nHexadecimal address: ");
    scanf("%x", &addr);
    
    // Il numero di byte dell'indirizzo da visualizzare
    printf("How many bytes: ");
    scanf("%d", &nbyte);

    printf("%10s %20s %20s\n", "Address", "Byte", "Characters");

    ptr = (BYTE *) addr;

    for (; nbyte > 0; nbyte -= 10) {
        printf("%#8x ", (unsigned int) ptr);
    }

    return(EXIT_SUCCESS);
}
