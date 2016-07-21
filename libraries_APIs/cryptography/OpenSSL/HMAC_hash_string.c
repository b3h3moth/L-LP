#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/hmac.h>

enum { LEN = 20 };

// The program's purpose is how to hash a string through OpenSSL hash function.

int main(void) {
    char key[] = "A1B2C3B4C5";
    char data[] = "OpenSSL Hash function";
    unsigned char *dgst = NULL;

    dgst = HMAC(EVP_sha1(), key, strlen(key), (unsigned char *)data, \
                strlen(data), NULL, NULL);

    char mdstr[LEN];
    for (int i=0; i<LEN; i++)
    return(EXIT_SUCCESS);
}
