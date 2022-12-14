#include <stdio.h>
#include <stdlib.h>

#define X 563
#define Y 174

int main() {
    FILE *fp = fopen("input.txt", "r");
    static char grid[Y + 2][2 * X] = {0};

    int x, y, xnew, ynew;
    if (!fscanf(fp, "%d,%d", &x, &y)) 
        exit(1);

    fgetc(fp);fgetc(fp);fgetc(fp);fgetc(fp);

    while (!feof(fp)) {
        if (!fscanf(fp, "%d,%d", &xnew, &ynew))
            break;


        int xdiff, ydiff;

        if (x < xnew) xdiff = 1;
        else if (x > xnew) xdiff = -1;
        else xdiff = 0;

        if (y < ynew) ydiff = 1;
        else if (y > ynew) ydiff = -1;
        else ydiff = 0;



        if (xdiff && !ydiff) {
            for (int xvar = x; xvar != xnew + xdiff; xvar += xdiff) {
                grid[y][xvar] = '#';
            }
        }

        else {
            for (int yvar = y; yvar != ynew + ydiff; yvar += ydiff)
                grid[yvar][x] = '#';
        }
        
        char c = fgetc(fp);

        if (c == ' ') {
            x = xnew;
            y = ynew;
            fgetc(fp); fgetc(fp); fgetc(fp);
        }
        else if (c == '\n') {
            if (!fscanf(fp, "%d,%d", &x, &y))
                break;

            fgetc(fp);fgetc(fp);fgetc(fp);fgetc(fp);
        }
        else break;
    }

    int spawnx = 500, spawny = 0;
    int counter = 0;

    int doneflag = 1;
    int sandx = spawnx, sandy = spawny;
    while (doneflag) {
        sandx = spawnx; sandy = spawny;


        for (;;) {
            if (sandy + 1 < Y) {
                if (!grid[sandy + 1][sandx]) {
                    sandy += 1;
                    continue;
                }

                if (sandx - 1 >= 0) {
                    if (!grid[sandy + 1][sandx - 1]) {
                        sandy += 1; sandx -= 1;
                        continue;
                    }

                    if (sandx + 1 < X) {
                        if (!grid[sandy + 1][sandx + 1]) {
                            sandy += 1; sandx += 1;
                        }
                        else {
                            break;
                        }
                    }
                    else {
                        doneflag = 0;
                        break;
                    }
                }
                else {
                    doneflag = 0;
                    break;
                }

            }
            else {
                doneflag = 0;
                break;
            }
        }

        grid[sandy][sandx] = 'o';

        counter += 1;
    }

    printf("%d\n", counter - 1);

    for (int y = Y + 1; y; y--) {
        for (int x = 0; x < 2 * X; x++) {
            if (grid[y][x] == 'o') {
                int sandx = x, sandy = y;
                while (sandy < Y) {
                    if (!grid[sandy + 1][sandx])
                        sandy += 1;
                    else if (!grid[sandy + 1][sandx - 1]) {
                        sandx -= 1; sandy += 1;
                    }
                    else if (!grid[sandy + 1][sandx + 1]) {
                        sandx += 1; sandy += 1;
                    }
                    else break;
                }

                grid[y][x] = 0;
                grid[sandy][sandx] = 'o';
            }
        }
    }


    sandx = spawnx, sandy = spawny;
    for (;;) {
        sandx = spawnx; sandy = spawny;


        while (sandy < Y) {
            if (!grid[sandy + 1][sandx]) {
                sandy += 1;
            }

            else if (!grid[sandy + 1][sandx - 1]) {
                sandy += 1; sandx -= 1;
            }

            else if (!grid[sandy + 1][sandx + 1]) {
                sandy += 1; sandx += 1;
            }
            else {
                break;
            }
        }


        grid[sandy][sandx] = 'o';
        counter += 1;

        if (sandx == spawnx && sandy == spawny) break;
    }

    printf("%d\n", counter);
}