#include <stdio.h>
#include <string.h>

#define max(a, b) (a >= b ? a : b)
#define min(a, b) (a <= b ? a : b)

#define SIZE 99

int main() {
    FILE *fp = fopen("input.txt", "r");
    char forest[SIZE][SIZE];
    char maxheight[SIZE][SIZE][4] = {0}; // Not including current square. LRUD, (LRUD)Prod

    int counter = 0;
    while (fread(forest[counter++], SIZE, 1, fp))
        fgetc(fp);

    fclose(fp);

    int treecount = 0; // Row m: L, R; Col m: U, D
    for (int i = 1; i < SIZE; i++) {
        for (int j = 1; j < SIZE; j++) {
            maxheight[i][j][0] = max(maxheight[i][j - 1][0], forest[i][j - 1]);
            maxheight[i][SIZE - 1 - j][1] = max(maxheight[i][SIZE - j][1], forest[i][SIZE - j]);

            maxheight[i][j][2] = max(maxheight[i - 1][j][2], forest[i - 1][j]);
            maxheight[SIZE - 1 - i][j][3] = max(maxheight[SIZE - i][j][3], forest[SIZE - i][j]);
        }
    }

    int maxprod = 0; // For Part 2

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int height = forest[i][j];
            if (height > maxheight[i][j][0] || height > maxheight[i][j][1] || 
                height > maxheight[i][j][2] || height > maxheight[i][j][3])
                    treecount += 1;

            int li = max(0, j - 1), ri = min(SIZE - 1, j + 1), ui = max(0, i - 1), di = min(SIZE - 1, i + 1);
            
            while (li > 0 && forest[i][li] < forest[i][j]) li -= 1;
            while (ri < SIZE - 1 && forest[i][ri] < forest[i][j]) ri += 1;
            while (ui > 0 && forest[ui][j] < forest[i][j]) ui -= 1;
            while (di < SIZE - 1 && forest[di][j] < forest[i][j]) di += 1;

            maxprod = max(maxprod, (j - li) * (ri - j) * (i - ui) * (di - i));
        }
    }

    printf("%d\n", treecount);
    printf("%d\n", maxprod);
}