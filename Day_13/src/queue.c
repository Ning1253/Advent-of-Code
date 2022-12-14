#include "queue.h"

void addQueue(Queue q, Node n) {
    Node *new = calloc(1, sizeof(Node));
    *new = n;

    if (q->last) q->last->next = new;
    q->last = new;
    if (!q->first) q->first = new;
}

Node popQueue(Queue q) {
    Node temp = *q->first;
    
    if (!temp.next) q->last = NULL;

    free(q->first);
    q->first = temp.next;
    return temp;
}