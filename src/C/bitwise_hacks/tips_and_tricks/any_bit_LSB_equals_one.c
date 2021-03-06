#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void) {
    int val = 0xA1B1C1FF; // 10101010 01010101 10101010 11111111
    int mask = 0xFF;      // 00000000 00000000 00000000 11111111
    
    // if any bit in the LSB (Least Significant Byte) of 'val' is 1, returns 1
    int result = !(~val & mask);
    
    // Logical operator '!' detects whether there is any nonzero bit in a word
    int res = !!(val & mask);

    assert(result == 1);
    assert(res == 1);
    
    printf("result: %d\n", result);
    printf("result: %d\n", res);

    return(EXIT_SUCCESS);
}
