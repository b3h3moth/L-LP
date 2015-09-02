#include <stdio.h>
#include <stdlib.h>

void bit_swap(int *x, int *y);

int main(void) {
    unsigned char num = 0;
    unsigned char num_a = 1;
    unsigned char num_b = 10;

    // ~
    // One's complement operator (Operatore di completamento a uno)
    // inverte tutti i bit dell'operando su cui agisce
    unsigned char not_num = ~num; // Diventa 0x11111111;

    unsigned char and_num = num_a & num_b;
    unsigned char or_num = num_a | num_b;
    unsigned char xor_num = num_a ^ num_b;

    printf("(NOT) ~num(0x%x) = 0x%x - Decimal: %d\n", num, not_num, not_num);
    printf("(AND) num_a(0x%x) & num_b(0x%x) = 0x%x\n", num_a, num_b, and_num);
    printf(" (OR) num_a(0x%x) | num_b(0x%x) = 0x%x\n", num_a, num_b, or_num);
    printf("(XOR) num_a(0x%x) ^ num_b(0x%x) = 0x%x\n", num_a, num_b, xor_num);

    return(EXIT_SUCCESS);
}
