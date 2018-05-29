#include <stdio.h>
#include <stdlib.h>
#include "linlinklst.h"

int main(void) {
    char *myfile = "lll.txt";
    int i;
    typeList llst = NULL;

    addNode(&llst, 3);
    addNode(&llst, 2);
    addNode(&llst, 1);
    writeNode(llst);
    delNode(&llst);
    delNode(&llst);
    if (emptyList(llst))
        fprintf(stdout, "A. The list is empty\n");
    else
        fprintf(stdout, "A. The list is not empty\n");
    delNode(&llst);
    if (emptyList(llst))
        fprintf(stdout, "B. The list is empty\n");
    addNode(&llst, 10);
    addNode(&llst, 1);
    addNode(&llst, 9);
    addNode(&llst, 7);
    writeNodeF(myfile, llst);
    /* $ cat lll.txt */
    for (i=0; i<=10; i++) 
        printf("find %.2d: %d\n", i, findinList(llst, i));
    typeList res;
    findList(llst, 7, &res);
    writeNode(res);
    printf("%d\n", res->data);
    return(EXIT_SUCCESS);
}
