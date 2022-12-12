#ifndef c_set_h
#define c_set_h

#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    char isfilled;
    int xy[2];
} Node;

typedef struct Set {
    size_t size;
    size_t used;
    Node *data;
} *Set;

void addSet(Set s, int a, int b);
bool inSet(Set s, int a, int b);
#endif