#include <stdio.h>

#include "array.h"

ARRAY(, char);

int main() {
    char buffer[50];

    FILE *fp = fopen("input.txt", "r");

    Array arrays[9] = {0};
    Array arrays2[9] = {0};
    for (int i = 0; i < 9; i++) {
        arrays[i] = initArray();
        arrays2[i] = initArray();
    }


    int line = 0;

    while (fgets(buffer, 50, fp)) {
        for (int i = 0; i < 50; i++) {
            if (buffer[i] == '[') {
                setArray(arrays[i/4], buffer[i + 1], 7 - line);
                setArray(arrays2[i/4], buffer[i + 1], 7 - line);
            }
        }

        line += 1;

        if (line == 8) break;
    }

    if (!fgets(buffer, 50, fp)) exit(1);

    int a = 0, b = 0, c = 0;

    while (fgets(buffer, 50, fp)) {
        sscanf(buffer, "move %d from %d to %d\n", &a, &b, &c);

        for (int i = 0; i < a; i++) {
            appendArray(arrays[c - 1], popArray(arrays[b - 1]));
            appendArray(arrays2[c - 1], readArray(arrays2[b - 1], i - a));
        }

        for (int i = 0; i < a; i++) popArray(arrays2[b - 1]);
    }

    for (int i = 0; i < 9; i++) {
        printf("%c", readArray(arrays[i], -1));
    }

    printf("\n");

    for (int i = 0; i < 9; i++) {
        printf("%c", readArray(arrays2[i], -1));
    }

    printf("\n");

}