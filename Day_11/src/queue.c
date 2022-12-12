#include "queue.h"

void addQueue(Queue q, size_t item) {
    Node *n = malloc(sizeof(Node));
    *n = (Node){item, NULL};

    if (q->end)
        q->end->prev = n;

    q->end = n;

    if (!q->start)
        q->start = n;

    q->used += 1;
}

int popQueue(Queue q) {
    Node *temp = q->start;
    int ans = temp->value;

    q->start = temp->prev;
    free(temp);

    q->used -= 1;

    if (!q->used)
        q->end = NULL;

    return ans;
}