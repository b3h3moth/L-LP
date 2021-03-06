#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void) {
    int val = ~0;  // 11111111 11111111 11111111 11111111
    int mask = ~0; // 11111111 11111111 11111111 11111111
    
    // if any bit of 'val' is 1, returns 1
    int result = !(val ^ mask);

    // Logical operator '!' detects whether there is any nonzero bit in a word
    int res = !!(val);

    assert(result == 1);
    assert(res == 1);
    
    printf("result: %d\n", result);
    printf("result: %d\n", res);

    return(EXIT_SUCCESS);
}
