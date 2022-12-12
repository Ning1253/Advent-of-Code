#include <stdio.h>

#include "set.h"

int main() {
    FILE *fp = fopen("input.txt", "r");
    int head[2] = {0, 0};
    int tail[2] = {0, 0};

    int tails[9][2] = {{0, 0}, {0, 0}, {0, 0},
                       {0, 0}, {0, 0}, {0, 0},
                       {0, 0}, {0, 0}, {0, 0}};

    Set coords1 = malloc(sizeof(struct Set));
    Set coords2 = malloc(sizeof(struct Set));

    addSet(coords1, 0, 0);
    addSet(coords2, 0, 0);

    char dir;
    int num;
    while (fscanf(fp, "%c %d", &dir, &num)) {
        while (num) {
            if (dir == 'L') head[0] -= 1;
            if (dir == 'R') head[0] += 1;
            if (dir == 'U') head[1] += 1;
            if (dir == 'D') head[1] -= 1;

            num -= 1;

            int addx = 0, addy = 0;

            if (head[0] > tail[0] + 1 || 
               (head[0] > tail[0] && ((head[1] > tail[1] + 1) || (head[1] < tail[1] - 1)))) addx = 1;
            else if (head[0] < tail[0] - 1 || 
                    (head[0] < tail[0] && ((head[1] > tail[1] + 1) || (head[1] < tail[1] - 1)))) addx = -1;
            
            if (head[1] > tail[1] + 1 || 
               (head[1] > tail[1] && ((head[0] > tail[0] + 1) || (head[0] < tail[0] - 1)))) addy = 1;
            else if (head[1] < tail[1] - 1 || 
                    (head[1] < tail[1] && ((head[0] > tail[0] + 1) || (head[0] < tail[0] - 1)))) addy = -1;

            tail[0] += addx;
            tail[1] += addy;

            tails[0][0] = tail[0]; tails[0][1] = tail[1];

            for (int i = 1; i < 9; i++) {
                addx = 0, addy = 0;

                if (tails[i - 1][0] > tails[i][0] + 1 || 
                   (tails[i - 1][0] > tails[i][0] && ((tails[i - 1][1] > tails[i][1] + 1) || (tails[i - 1][1] < tails[i][1] - 1)))) addx = 1;
                else if (tails[i - 1][0] < tails[i][0] - 1 || 
                        (tails[i - 1][0] < tails[i][0] && ((tails[i - 1][1] > tails[i][1] + 1) || (tails[i - 1][1] < tails[i][1] - 1)))) addx = -1;
                
                if (tails[i - 1][1] > tails[i][1] + 1 || 
                   (tails[i - 1][1] > tails[i][1] && ((tails[i - 1][0] > tails[i][0] + 1) || (tails[i - 1][0] < tails[i][0] - 1)))) addy = 1;
                else if (tails[i - 1][1] < tails[i][1] - 1 || 
                        (tails[i - 1][1] < tails[i][1] && ((tails[i - 1][0] > tails[i][0] + 1) || (tails[i - 1][0] < tails[i][0] - 1)))) addy = -1;

                tails[i][0] += addx;
                tails[i][1] += addy;
            }

            addSet(coords1, tail[0], tail[1]);
            addSet(coords2, tails[8][0], tails[8][1]);
        }

        fgetc(fp);

        if (feof(fp)) break;
    }

    printf("%ld\n", coords1->used);
    printf("%ld\n", coords2->used);
}