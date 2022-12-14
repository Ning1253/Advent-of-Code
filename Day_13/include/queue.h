#ifndef c_queue_h
#define c_queue_h

#include <stdlib.h>

typedef struct Queue *Queue;

typedef struct Node {
    Queue list;
    char elem;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *first;
    Node *last;
} *Queue;

void addQueue(Queue q, Node n);
Node popQueue(Queue q);

#endif