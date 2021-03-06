#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct person Person;
typedef struct node_lls NodeLLS; /* LLS stands for Linear Linked Structure */
typedef struct type_lls TypeLLS;

struct person {
    char firstname[16];
    char lastname[16];
    int age;
};

struct node_lls {
    Person info;
    NodeLLS *next;
};

struct type_lls {
    NodeLLS *head;  /* Pointer to the first element of the LLS */
    int size;       /* How many nodes the LLS contains */
};

/* Constant PersonError is useful when an error occurs */
Person PersonError = {"","",0};

/* Function prototypes */
void printPerson(Person p);
int equalPerson(Person p1, Person p2);
TypeLLS *init(void);
int empty(TypeLLS *l);
TypeLLS *add(TypeLLS *l, Person p);
TypeLLS *del(TypeLLS *l);
Person printFirst(TypeLLS *l);
void print(TypeLLS *l);
TypeLLS *copy(TypeLLS *l);
NodeLLS *clone_r(NodeLLS *n);
TypeLLS *clone(TypeLLS *l);
int equalNode_r(NodeLLS *n1, NodeLLS *n2);
int equalList(TypeLLS *l1, TypeLLS *l2);
int findLastname_r(NodeLLS *n, const char *str);

int main(void) {
    TypeLLS *t = init();
    Person newperson1 = { "Richard", "Stallman", 65};
    Person newperson2 = { "Dennis", "Ritchie", 70};

    if (empty(t))
        printf("The LLS is empty\n");

    printf("\t### add() 1 person\n");
    t = add(t, newperson1);
    print(t);
    printf("\t### del() 1 person\n");
    t = del(t);
    print(t);
    printf("\t### add() 2 person\n");
    t = add(t, newperson1);
    t = add(t, newperson2);
    print(t);
    TypeLLS *tcpy = init();
    printf("\t### save() the first node\n");
    Person pfirst = printFirst(t);
    printPerson(pfirst);
    printf("\t### copy() the whole list (with memory sharing)\n");
    tcpy = copy(t);
    print(tcpy);
    printf("\t### (deep) copy() the whole list (without memory sharing)\n");
    TypeLLS *dp = clone(t);
    print(dp);
    printf("\t### Check if two LLS are equals\n");
    Person np1 = { "Dennis", "Stallman", 65};
    Person np2 = { "Richard", "Ritchie", 70};
    TypeLLS *l1 = init();
    l1 = add(l1, np1);
    l1 = add(l1, np2);
    if (equalList(dp, t))
        printf("dp and t are equals\n");
    else
        printf("dp and t are not equals\n");
    if (equalList(dp, l1))
        printf("dp and l1 are equals\n");
    else
        printf("dp and l1 are not equals\n");
    printf("\t### Find lastname (1 true, 0 false)\n");
    if (findLastname_r(l1->head, "Stallman") == 1)
        printf("true\n");
    else
        printf("false\n");
    if (findLastname_r(l1->head, "Starman") == 1)
        printf("true\n");
    else
        printf("false\n");

    return(EXIT_SUCCESS);
}

/* Print full person */
void printPerson(Person p) {
    printf("%s %s, %d years old\n", p.firstname, p.lastname, p.age);
}

/* Two structure person (or two persons) are equals */
int equalPerson(Person p1, Person p2) {
    return (strcmp(p1.firstname, p2.firstname) == 0) &&
           (strcmp(p1.lastname, p2.lastname) == 0) && (p1.age == p2.age);
}

/* LLS initialization */
TypeLLS *init(void) {
    TypeLLS *h = (TypeLLS *) malloc(sizeof(TypeLLS));
    h->head = NULL;
    h->size = 0;
    return h;
}

/* Check if the LLS is empty */
int empty(TypeLLS *l) {
    return l->size == 0;    /* or: return l->head == NULL; */
}

/* Add a Person on the head of the list */
TypeLLS *add(TypeLLS *l, Person p) {
    TypeLLS *new = init();
    new->head = (NodeLLS*) malloc(sizeof(NodeLLS));
    new->head->info = p;                            /* copy each member of p */
    new->head->next = l->head;                      /* link previous node */
    new->size = l->size + 1;
    return new;
}

/* Remove a Person from the head of the list */
TypeLLS *del(TypeLLS *l) {
    if (l->size == 0)
        return l;
    else {
        TypeLLS *temp = init();
        temp->head = l->head->next;
        temp->size = l->size - 1;
        return temp;
    }
}

/* Returns the first element */
Person printFirst(TypeLLS *l) {
    if (l->size == 0)
        return PersonError;
    else
        return l->head->info;
}

/* Print each node (iterative) */
void print(TypeLLS *l) {
    NodeLLS *n = l->head;
    while (n != NULL) {
        printPerson(n->info);
        n = n->next;
    }
}

/* Copy LLS with memory sharing */
TypeLLS *copy(TypeLLS *l) {
    if (l->size == 0)
        return l;
    else {
        TypeLLS *lcpy = init();
        lcpy->head = l->head;
        lcpy->size = l->size;
        return lcpy;
    }
}

/* Auxiliary function to copy node by node in recursive manner */
NodeLLS *clone_r(NodeLLS *p) {
    if (p == NULL)
        return NULL;
    else {
        NodeLLS *newnode = (NodeLLS *) malloc(sizeof(NodeLLS));
        newnode->info = p->info;
        newnode->next = clone_r(p->next);
        return newnode;
    }
}


/* Copy LLS without memory sharing (deep copy) */
TypeLLS *clone(TypeLLS *l) {
    TypeLLS *n = init();
    n->head = clone_r(l->head);
    n->size = l->size;
    return n;
}

/* Auxiliary function to check if the nodes of the list n1 are equals to node
 * of the list n2, in recursive manner */
int equalNode_r(NodeLLS *n1, NodeLLS *n2) {
    if (n1 == NULL && n2 == NULL)
        return 1;

    if (!equalPerson(n1->info, n2->info))   /* Working on the first node */
        return 0;
    else
        return equalNode_r(n1->next, n2->next);
}

/* Check if two lists are equals */
int equalList(TypeLLS *l1, TypeLLS *l2) {
    if (l1->size != l2->size)
        return 0;
    else
        return equalNode_r(l1->head, l2->head);
}

/* Find the lastname in the nodes */
int findLastname_r(NodeLLS *n, const char *str) {
    if (n == NULL)
        return 0;
    else if (strcmp(n->info.lastname, str) == 0)
        return 1;
    else return findLastname_r(n->next, str);
}
