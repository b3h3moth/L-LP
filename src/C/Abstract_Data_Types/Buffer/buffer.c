#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"

/* Dynamic memory alliocation of the Buffer */
Buffer *buf_alloc(int size, const char *name) {
    Buffer *buf = (Buffer *)malloc(sizeof(Buffer));

    buf->data = (char*)malloc(size * sizeof(char));
    buf->size = size;
    buf->pos = 0;
    set_name(buf, name);
    
    return buf;
}

/* Releases the Buffer memory */
void buf_dealloc(Buffer *buf) {
    free(buf->data);
    free(buf);
}

/* Move the index at the initial position within the Buffer */
void reset(Buffer *buf) {
    buf->pos = 0;
}

/* Setup the Buffer name */
void set_name(Buffer *buf, const char *name) {
    strncpy(buf->name, name, MAX_NAME_DIM);
}

/* Returns a random character 
   A + [0,25] = random character with a range from 0 to 25 */
char random_ch() {
    return rand()%26 + 'A';
}

/* Buffer initialization through random characters.
   It writes random characters within the Buffer. */
void init_random(Buffer *buf) {
    char ch = buf_putc(buf, random_ch());

    if (ch != EOB) /* If the Buffer is not full, we can fill it */
        init_random(buf);
}


/* Buffer initialization through a string */
void init_str(Buffer *buf, const char *str) {
    if (str[0] == '\0')
        buf->pos = 0;
    else {
        char ch = buf_putc(buf, str[0]);

        if (ch != EOB) /* If the Buffer is not full, we can fill it */
            init_str(buf, str + 1);
    }
}


/* Read next character within the Buffer, increment by one the index,
   It Returns EOB if the End Of Buffer has been reached. */
char buf_getc(Buffer *buf) {
    char cr = EOB;
    
    if (buf->pos < buf->size) {
        cr = buf->data[buf->pos];
        buf->pos++;
    } else if (buf->pos == buf->size) { /* End of the Buffer */
        buf->pos = 0;
        cr = EOB;
    }
    return cr;
}

/* Write next character within the Buffer, increment by one the index,
   It Returns EOB if the End Of Buffer has been reached. */
char buf_putc(Buffer *buf, char c) {
    char cw = EOB;

    if (buf->pos < buf->size) {
        buf->data[buf->pos] = c;
        cw = c;
        buf->pos++;
    } else if (buf->pos == buf->size) { /* End of the Buffer */
        buf->pos = 0;
        cw = EOB;
    }
    return cw;
}

/* Print the contents of the Buffer */
void buf_print(Buffer *buf) {
    char ch = buf_getc(buf);

    if (ch != EOB) {
        printf("%c", ch);
        buf_print(buf);
    }
}

void print(Buffer *buf) {
    printf("%s - ", buf->name);
    buf_print(buf);
    printf("\n");
}

/* Copy the contents of the Buffer from source to the destination */
void buf_copy(Buffer *bdst, Buffer *bsrc) {
    char ch = buf_getc(bsrc);

    if (ch != EOB) {
        buf_putc(bdst, ch);
        buf_copy(bdst, bsrc);
    }
}

/* Copy the contents of the Buffer from source to the destination
   inverse order. */
void buf_inverse_copy(Buffer *bdst, Buffer *bsrc) {
    char ch = buf_getc(bsrc);

    if (ch != EOB) {
        buf_inverse_copy(bdst, bsrc);
        buf_putc(bdst, ch);
    }
}

/* Count how many occurence of the ASCII character there are within the 
   Buffer */
int count(Buffer *buf, char c) {
    char ch = buf_getc(buf);

    if (ch == EOB)
        return 0;
    else if (ch == c)
        return 1 + count(buf, c);
    else
        return count(buf, c);
}

/* Concatenate two Buffer into new one with its own name */
Buffer *buf_concatenate(Buffer *bufa, Buffer *bufb, const char *name) {
    Buffer *bnew = buf_alloc((bufa->size + bufb->size), name);
    concatenate(bnew, bufa, bufb);
    return bnew;
}

void concatenate(Buffer *bnew, Buffer *bufa, Buffer *bufb) {
    char ch = buf_getc(bufa);

    if (ch != EOB) {
        buf_putc(bnew, ch);
        concatenate(bnew, bufa, bufb);
    } else 
        buf_copy(bnew, bufb);
}

/* Check if the Buffer is palindrome */
int palindrome(Buffer *buf) {
    int n = 1;

    char ch_before = buf_getc(buf);
    
    if (buf->pos < buf->size / 2)
        n = n && palindrome(buf);
    
    char ch_after = buf_getc(buf);
    
    n = n && ch_before == ch_after;

    /* Note: write character on the activation record before and after the 
     invocation of the recursive function palindrome() */

    return 0;
}
