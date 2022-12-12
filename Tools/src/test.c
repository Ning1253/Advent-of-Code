#include <stdio.h>

#include "map.h"

MAP(IntString, int, char*, 1*, 0, "");

int main() {
    IntStringMap m = initIntStringMap();
    m->data = NULL; m->used = 0; m->size = 0;

    addIntStringMap(m, 3, "hi");
    addIntStringMap(m, 69, "bye");
    addIntStringMap(m, 69+256, "yee");
    addIntStringMap(m, 69+512, "ahh");

    for (int i = 0; i < 600; i++) {
        printf("%s\n", readIntStringMap(m, i));
    }

    printf("%ld, %ld\n", m->size, m->used);
    popIntStringMap(m, 69+512);

    for (int i = 0; i < 600; i++) {
        printf("%s\n", readIntStringMap(m, i));
    }

    freeIntStringMap(m);

}