#include <stdio.h>

#include "queue.h"

Queue copyQueue(Queue q) {
    Queue new = calloc(1, sizeof(struct Queue));
    Queue temp = calloc(1, sizeof(struct Queue));

    while (q->first) {
        Node n = popQueue(q);
        addQueue(new, n);
        addQueue(temp, n);
    }

    while (temp->first)
        addQueue(q, popQueue(temp));
    
    free(temp);

    return new;
}

Queue getStuff(FILE *fp) {
    Queue q = calloc(1, sizeof(struct Queue));

    char c = fgetc(fp); // '['
    for (;;) {
        c = fgetc(fp);
        switch (c) {
            case '[':
                ungetc(c, fp);
                addQueue(q, (Node){getStuff(fp), 0, NULL});
                break;
            case ']':
                return q;
                break;
            case ',':
                break;
            default:
                ungetc(c, fp);
                int num;
                if (!fscanf(fp, "%d", &num)) {
                    printf("Error: Failed to scan int. \n");
                    exit(1);
                }
                addQueue(q, (Node){NULL, num, NULL});
                break;
        }
    }
}

int compare(Queue q1, Queue q2) { // 0 if different, 1 if ACTUALLY DONE, -1 if non-conclusive
    q1 = copyQueue(q1);
    q2 = copyQueue(q2);

    while (q1->first) {
        if (!q2->first) return 0;

        Node left = popQueue(q1);
        Node right = popQueue(q2);

        if (!(left.list || right.list)) {
            if (left.elem < right.elem) return 1;
            if (left.elem > right.elem) return 0;
        }
        else if (left.list && !right.list) {
            Queue temp = calloc(1, sizeof(struct Queue));
            addQueue(temp, (Node){NULL, right.elem, NULL});

            int result = compare(left.list, temp);

            free(temp);

            if (result == 1) return 1;
            else if (result == 0) return 0;
        }
        else if (!left.list && right.list) {
            Queue temp = calloc(1, sizeof(struct Queue));
            addQueue(temp, (Node){NULL, left.elem, NULL});

            int result = compare(temp, right.list);

            free(temp);

            if (result == 1) return 1;
            else if (result == 0) return 0;
        }
        else {
            int result = compare(left.list, right.list);

            if (result == 1) return 1;
            else if (result == 0) return 0;
        }
    }

    if (q2->first) return 1;
    else return -1;
}



int main() {
    FILE *fp = fopen("input.txt", "r");
    int total = 0;
    int index = 0;

    Queue q_of_2 = calloc(1, sizeof(struct Queue));
    Queue q_of_2_in = calloc(1, sizeof(struct Queue));
    addQueue(q_of_2_in, (Node){NULL, 2, NULL});
    addQueue(q_of_2, (Node){q_of_2_in, 0, NULL});

    Queue q_of_6 = calloc(1, sizeof(struct Queue));
    Queue q_of_6_in = calloc(1, sizeof(struct Queue));
    addQueue(q_of_6_in, (Node){NULL, 6, NULL});
    addQueue(q_of_6, (Node){q_of_6_in, 0, NULL});

    int q2index = 1, q6index = 2;

    while (!feof(fp)) {
        index += 1;

        Queue q1 = getStuff(fp);
        fgetc(fp); // New Line
        Queue q2 = getStuff(fp);
        fgetc(fp); // New Line

        if (compare(q1, q2))
            total += index;
        
        if (compare(q1, q_of_2))
            q2index += 1;
        if (compare(q2, q_of_2))
            q2index += 1;
        
        if (compare(q1, q_of_6))
            q6index += 1;
        if (compare(q2, q_of_6))
            q6index += 1;


        fgetc(fp); // Empty Line (or EOF at end)

        free(q1);
        free(q2);
    }

    printf("%d\n", total);
    printf("%d\n", q2index * q6index);
}