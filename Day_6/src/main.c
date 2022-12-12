#include <stdio.h>

typedef struct LL {
    char val;
    struct LL *next;
} LinkedList;

int main() {
    FILE *fp = fopen("input.txt", "r");
    char a = fgetc(fp), b = fgetc(fp), c = fgetc(fp), d = fgetc(fp);

    int counter = 4;

    while (!((a - b) && (a - c) && (b - c) && (a - d) && (b - d) && (c - d))) {
        a = b; b = c; c = d;
        d = fgetc(fp);
        counter += 1;
    }

    printf("%d\n", counter);

    fseek(fp, 0, SEEK_SET);

    char letters[14];
    counter = 14;

    for (int i = 0; i < 14; i++) letters[i] = fgetc(fp);

    int flag = 0;
    while (!flag) {
        flag = 1;
        for (int i = 0; i < 13; i++) {
            for (int j = i + 1; j < 14; j++) {
                if (letters[i] == letters[j]) {
                    flag = 0;
                    break;
                }
            }

            if (!flag) break;
        }

        if (flag) break;

        letters[counter % 14] = fgetc(fp);
        counter += 1;
    }

    printf("%d\n", counter);


}