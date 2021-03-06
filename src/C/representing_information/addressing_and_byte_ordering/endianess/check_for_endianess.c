#include <stdio.h>
#include <stdlib.h>

// Creazione di un array di memoria statica
char vec[4] = {'a', 'b', 'c', 'd'};

// Function Prototypes
char *bits(char ch);
int big_endian(void);


int main(void) {
    // Puntatori all'inizio di 'vec'
    char    *pc = vec;
    short   *ps = (short *)vec;
    int     *pi = (int *)vec;
    float   *pf = (float *)vec;

    if (big_endian())
        puts("Big-Endian Architecture.");
    else
        puts("Little-Endian Architecture.");

    printf("%s", bits(vec[0]));
    printf("%s", bits(vec[1]));
    printf("%s", bits(vec[2]));
    printf("%s", bits(vec[3]));

    // Stampa l'array mediante i vari tipi di dato utilizzati
    printf("\n\'%c\' \'%c\' \'%c\' \'%c\'\n", *pc, *(pc+1), *(pc+2), *(pc+3));
    printf("%d %d\n", *ps, *(ps+1));
    printf("%d\n", *pi);
    printf("%f\n", *pf);

    return(EXIT_SUCCESS);
}


char *bits(char ch) {
    static char arr[9];
    int i = (int) ch;

    if (!big_endian())
        i = i >> 24;

    arr[0] = ((ch & 128) == 128) + '0';
    arr[1] = ((ch &  64) ==  64) + '0';
    arr[2] = ((ch &  32) ==  32) + '0';
    arr[3] = ((ch &  16) ==  16) + '0';
    arr[4] = ((ch &   8) ==   8) + '0';
    arr[5] = ((ch &   4) ==   4) + '0';
    arr[6] = ((ch &   2) ==   2) + '0';
    arr[7] = ((ch &   1) ==   1) + '0';
    arr[8] = '\0';

    return arr;
}

int big_endian(void) {
    long val = 1;

    return !(*((char *)(&val)));
}
