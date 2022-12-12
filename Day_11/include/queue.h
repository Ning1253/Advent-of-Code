#ifndef c_queue_h
#define c_queue_h

#include <stdlib.h>

typedef struct Node {
    size_t value;
    struct Node *prev;
} Node;

typedef struct Queue {
    size_t used;
    Node *start;
    Node *end;
} *Queue;

void addQueue(Queue q, size_t item);
int popQueue(Queue q);

#endif