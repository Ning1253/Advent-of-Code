#ifndef c_queue_h
#define c_queue_h

#include <stdlib.h>

typedef struct Coord {
    int score;
    int x;
    int y;
} Coord;

typedef struct Queue {
    size_t size;
    size_t used;
    Coord *data;
} *Queue;

void addQueue(Queue q, Coord item);
Coord popQueue(Queue q);


#endif