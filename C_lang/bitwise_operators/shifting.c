#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* In tutti e 3 i casi ci sara' un messaggio di warning del compilatore,
    inoltre ciascun risultato sara' 0x00. Il motivo e' la lunghezza della word
    a 32 bit. */
    int      num1 = 0xFEDCBA98  << 32; // 32 bit
    int      num2 = 0xFEDCBA98  >> 36; // 32 bit
    unsigned num3 = 0xFEDCBA98  >> 40; // 32 bit

    printf("%#x\n", num1);
    printf("%#x\n", num2);
    printf("%#x\n", num3);

    return(EXIT_SUCCESS);
}
