#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>

enum types {CHAR, UCHAR, SHORT, USHORT, INT, UINT, LONG, ULONG};

union data_val {
    char valchar;
    short valshort;
    int valint;
    long valong;
};

void check_error(int data_type, char *val, char *arg, void(*print)(union data_val *, char *));
void print(union data_val *d, char *fmt);

int main(void) {
    check_error(4, "1532", "%d", &print);
    return(EXIT_SUCCESS);
}

void check_error(int data_type, char *val, char *arg, void(*print)(union data_val *, char *)) {
    union data_val value = val;

    if (data_type == INT) {
        value->valint = atol(val);
        printf("%d\n", value->valint);
        print(value, arg);
    }
}

void print(union data_val *d, char *fmt) {
    char *format = (void *)fmt;

    printf(format, d->valint);
}

/*
void check_error(const char *data_type, char *value, int min, int max) {
    printf("%lu\n", (long int)strtoimax(value, NULL, 10));

    if (strtoimax(value, NULL, 10) == 0) {
        fprintf(stderr, "0 is not a valid value, please\n");
    } 
    
    if (strtoimax(value, NULL, 10) > max) {
        fprintf(stderr, "[Error]: Integer Overflow on type '%s'.\n"
                "Available numeric range: from '%d' to '%d'\n", 
                data_type, min, max);
    } 
    
    if (strtoimax(value, NULL, 10) < min) {
        fprintf(stderr, "[Error]: Integer Underflow on type '%s'.\n"
                "Available numeric range: from '%d' to '%u'\n", 
                data_type, min, max);
    }
}
*/
