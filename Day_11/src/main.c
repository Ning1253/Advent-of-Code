#include <stdio.h>

#include "queue.h"

typedef struct {
    Queue q;
    size_t count;
} Monkey;

int main() {
    Monkey monkeys[8] = {{calloc(1, sizeof(struct Queue)), 0}, {calloc(1, sizeof(struct Queue)), 0}, {calloc(1, sizeof(struct Queue)), 0},
                         {calloc(1, sizeof(struct Queue)), 0}, {calloc(1, sizeof(struct Queue)), 0}, {calloc(1, sizeof(struct Queue)), 0},
                         {calloc(1, sizeof(struct Queue)), 0}, {calloc(1, sizeof(struct Queue)), 0}};
    

    addQueue(monkeys[0].q, 93); addQueue(monkeys[0].q, 54); 
    addQueue(monkeys[0].q, 69); addQueue(monkeys[0].q, 66); addQueue(monkeys[0].q, 71);

    addQueue(monkeys[1].q, 89); addQueue(monkeys[1].q, 51);
    addQueue(monkeys[1].q, 80); addQueue(monkeys[1].q, 66);

    addQueue(monkeys[2].q, 90); addQueue(monkeys[2].q, 92);
    addQueue(monkeys[2].q, 63); addQueue(monkeys[2].q, 91);
    addQueue(monkeys[2].q, 96); addQueue(monkeys[2].q, 63); addQueue(monkeys[2].q, 64);

    addQueue(monkeys[3].q, 65); addQueue(monkeys[3].q, 77);

    addQueue(monkeys[4].q, 76); addQueue(monkeys[4].q, 68); addQueue(monkeys[4].q, 94);

    addQueue(monkeys[5].q, 86); addQueue(monkeys[5].q, 65); 
    addQueue(monkeys[5].q, 66); addQueue(monkeys[5].q, 97); 
    addQueue(monkeys[5].q, 73); addQueue(monkeys[5].q, 83);

    addQueue(monkeys[6].q, 78);

    addQueue(monkeys[7].q, 89); addQueue(monkeys[7].q, 57);
    addQueue(monkeys[7].q, 59); addQueue(monkeys[7].q, 61);
    addQueue(monkeys[7].q, 87); addQueue(monkeys[7].q, 55);
    addQueue(monkeys[7].q, 55); addQueue(monkeys[7].q, 88);

    for (int i = 0; i < 20; i++) {
        while (monkeys[0].q->used) {
            int item = popQueue(monkeys[0].q);
            if (item % 7 == 0) addQueue(monkeys[7].q, item);
            else addQueue(monkeys[1].q, item);
            monkeys[0].count += 1;
        }

        while (monkeys[1].q->used) {
            int item = popQueue(monkeys[1].q);
            item = (item * 17) / 3;
            if (item % 19 == 0) addQueue(monkeys[5].q, item);
            else addQueue(monkeys[7].q, item);
            monkeys[1].count += 1;
        }

        while (monkeys[2].q->used) {
            int item = popQueue(monkeys[2].q);
            item = (item + 1) / 3;
            if (item % 13 == 0) addQueue(monkeys[4].q, item);
            else addQueue(monkeys[3].q, item);
            monkeys[2].count += 1;
        }

        while (monkeys[3].q->used) {
            int item = popQueue(monkeys[3].q);
            item = (item + 2) / 3;
            if (item % 3 == 0) addQueue(monkeys[4].q, item);
            else addQueue(monkeys[6].q, item);
            monkeys[3].count += 1;
        }

        while (monkeys[4].q->used) {
            int item = popQueue(monkeys[4].q);
            item = (item * item) / 3;
            if (item % 2 == 0) addQueue(monkeys[0].q, item);
            else addQueue(monkeys[6].q, item);
            monkeys[4].count += 1;
        }

        while (monkeys[5].q->used) {
            int item = popQueue(monkeys[5].q);
            item = (item + 8) / 3;
            if (item % 11 == 0) addQueue(monkeys[2].q, item);
            else addQueue(monkeys[3].q, item);
            monkeys[5].count += 1;
        }

        while (monkeys[6].q->used) {
            int item = popQueue(monkeys[6].q);
            item = (item + 6) / 3;
            if (item % 17 == 0) addQueue(monkeys[0].q, item);
            else addQueue(monkeys[1].q, item);
            monkeys[6].count += 1;
        }

        while (monkeys[7].q->used) {
            int item = popQueue(monkeys[7].q);
            item = (item + 7) / 3;
            if (item % 5 == 0) addQueue(monkeys[2].q, item);
            else addQueue(monkeys[5].q, item);
            monkeys[7].count += 1;
        }
    }

    size_t max1 = 0, max2 = 0;
    for (int i = 0; i < 8; i++) {
        if (monkeys[i].count > max1) {
            max2 = max1;
            max1 = monkeys[i].count;
        }
        else if (monkeys[i].count > max2) max2 = monkeys[i].count;
    }

    printf("%ld\n", max1 * max2);




    // Part 2:

    for (int i = 0; i < 8; i++)
        monkeys[i] = (Monkey){calloc(1, sizeof(struct Queue)), 0};
    

    addQueue(monkeys[0].q, 93); addQueue(monkeys[0].q, 54); 
    addQueue(monkeys[0].q, 69); addQueue(monkeys[0].q, 66); addQueue(monkeys[0].q, 71);

    addQueue(monkeys[1].q, 89); addQueue(monkeys[1].q, 51);
    addQueue(monkeys[1].q, 80); addQueue(monkeys[1].q, 66);

    addQueue(monkeys[2].q, 90); addQueue(monkeys[2].q, 92);
    addQueue(monkeys[2].q, 63); addQueue(monkeys[2].q, 91);
    addQueue(monkeys[2].q, 96); addQueue(monkeys[2].q, 63); addQueue(monkeys[2].q, 64);

    addQueue(monkeys[3].q, 65); addQueue(monkeys[3].q, 77);

    addQueue(monkeys[4].q, 76); addQueue(monkeys[4].q, 68); addQueue(monkeys[4].q, 94);

    addQueue(monkeys[5].q, 86); addQueue(monkeys[5].q, 65); 
    addQueue(monkeys[5].q, 66); addQueue(monkeys[5].q, 97); 
    addQueue(monkeys[5].q, 73); addQueue(monkeys[5].q, 83);

    addQueue(monkeys[6].q, 78);

    addQueue(monkeys[7].q, 89); addQueue(monkeys[7].q, 57);
    addQueue(monkeys[7].q, 59); addQueue(monkeys[7].q, 61);
    addQueue(monkeys[7].q, 87); addQueue(monkeys[7].q, 55);
    addQueue(monkeys[7].q, 55); addQueue(monkeys[7].q, 88);

    for (int i = 0; i < 10000; i++) {
        while (monkeys[0].q->used) {
            size_t item = popQueue(monkeys[0].q);
            item = (item * 3) % 9699690;
            if (item % 7 == 0) addQueue(monkeys[7].q, item);
            else addQueue(monkeys[1].q, item);
            monkeys[0].count += 1;
        }

        while (monkeys[1].q->used) {
            size_t item = popQueue(monkeys[1].q);
            item = (item * 17) % 9699690;
            if (item % 19 == 0) addQueue(monkeys[5].q, item);
            else addQueue(monkeys[7].q, item);
            monkeys[1].count += 1;
        }

        while (monkeys[2].q->used) {
            size_t item = popQueue(monkeys[2].q);
            item = (item + 1) % 9699690;
            if (item % 13 == 0) addQueue(monkeys[4].q, item);
            else addQueue(monkeys[3].q, item);
            monkeys[2].count += 1;
        }

        while (monkeys[3].q->used) {
            size_t item = popQueue(monkeys[3].q);
            item = (item + 2) % 9699690;
            if (item % 3 == 0) addQueue(monkeys[4].q, item);
            else addQueue(monkeys[6].q, item);
            monkeys[3].count += 1;
        }

        while (monkeys[4].q->used) {
            size_t item = popQueue(monkeys[4].q);
            item = (item * item) % 9699690;
            if (item % 2 == 0) addQueue(monkeys[0].q, item);
            else addQueue(monkeys[6].q, item);
            monkeys[4].count += 1;
        }

        while (monkeys[5].q->used) {
            size_t item = popQueue(monkeys[5].q);
            item = (item + 8) % 9699690;
            if (item % 11 == 0) addQueue(monkeys[2].q, item);
            else addQueue(monkeys[3].q, item);
            monkeys[5].count += 1;
        }

        while (monkeys[6].q->used) {
            size_t item = popQueue(monkeys[6].q);
            item = (item + 6) % 9699690;
            if (item % 17 == 0) addQueue(monkeys[0].q, item);
            else addQueue(monkeys[1].q, item);
            monkeys[6].count += 1;
        }

        while (monkeys[7].q->used) {
            size_t item = popQueue(monkeys[7].q);
            item = (item + 7) % 9699690;
            if (item % 5 == 0) addQueue(monkeys[2].q, item);
            else addQueue(monkeys[5].q, item);
            monkeys[7].count += 1;
        }
    }

    max1 = 0, max2 = 0;
    for (int i = 0; i < 8; i++) {
        if (monkeys[i].count > max1) {
            max2 = max1;
            max1 = monkeys[i].count;
        }
        else if (monkeys[i].count > max2) max2 = monkeys[i].count;
    }

    printf("%ld\n", max1 * max2);
}