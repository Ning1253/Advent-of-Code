#include "queue.h"

void addQueue(Queue q, Coord item) {
    if (q->used >= q->size)
        q->data = realloc(q->data, sizeof(Coord) * (q->size = (q->size ? 2 * q->size : 8)));
    
    q->data[q->used] = item;

    size_t index = q->used;
    while (index) {
        if (q->data[index].score < q->data[(index - 1) / 2].score) {
            Coord temp = q->data[index];
            q->data[index] = q->data[(index - 1) / 2];
            q->data[(index - 1) / 2] = temp;

            index = (index - 1) / 2;
        }
        else break;
    }

    q->used += 1;
}

Coord popQueue(Queue q) {
    q->used -= 1;

    Coord ans = q->data[0];
    q->data[0] = q->data[q->used];
    q->data[q->used] = (Coord){0, 0, 0};

    size_t index = 0;
    while (2 * index + 1 < q->used) {
        size_t lowest = index;
        if (q->data[2 * index + 1].score < q->data[lowest].score) lowest = 2 * index + 1;
        if (2 * index + 2 < q->used && q->data[2 * index + 2].score < q->data[lowest].score) lowest = 2 * index + 2;

        Coord temp = q->data[index];
        q->data[index] = q->data[lowest];
        q->data[lowest] = temp;

        if (index == lowest) break;
        else index = lowest;
    }

    return ans;
}