#include "set.h"

void addSet(Set s, int a, int b) {
    if (inSet(s, a, b)) return;

    size_t hash = 7 * a * a + b * b;

    if (2 * s->used >= s->size) {
        Node *data = calloc((s->size = (s->size ? 2 * s->size : 8)), sizeof(Node));

        if (s->data) {
            for (int i = 0; i < s->size / 2; i++) {
                if (s->data[i].isfilled) {
                    size_t index = 7 * s->data[i].xy[0] * s->data[i].xy[0] + s->data[i].xy[1] * s->data[i].xy[1];

                    while (data[index % s->size].isfilled) index += 1;
                    data[index % s->size] = s->data[i];
                }
            }

            free(s->data);
        }
        s->data = data;
    }


    size_t index = hash % s->size;
    while (s->data[index % s->size].isfilled) {
        index += 1;
    }
    s->data[index % s->size] = (Node){1, {a, b}};
    s->used += 1;
}

bool inSet(Set s, int a, int b) {
    if (!s->data) return false;

    size_t index = 7 * a * a + b * b;
    while (s->data[index % s->size].isfilled && 
           (s->data[index % s->size].xy[0] != a || s->data[index % s->size].xy[1] != b))
        index += 1;
    
    if (s->data[index % s->size].isfilled) return true;
    else return false;
}