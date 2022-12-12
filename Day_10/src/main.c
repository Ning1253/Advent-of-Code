#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("input.txt", "r");
    char buffer[50];

    int X = 1;
    int cycle = 0;

    int total = 0;

    char crt[6][40] = {0};

    while (fgets(buffer, 50, fp)) {
        if (buffer[0] == 'n') {
            cycle += 1;
            if ((cycle + 20) % 40 == 0) {
                total += cycle * X;
            }

            if (X - 1 <= (cycle - 1) % 40 && (cycle - 1) % 40 <= X + 1) crt[(cycle - 1) / 40][(cycle - 1) % 40] = '#';
            else crt[(cycle - 1) / 40][(cycle - 1) % 40] = '.';
        } 
        else {
            cycle += 1;
            if ((cycle + 20) % 40 == 0) {
                total += cycle * X;
            }

            if (X - 1 <= (cycle - 1) % 40 && (cycle - 1) % 40 <= X + 1) crt[(cycle - 1) / 40][(cycle - 1) % 40] = '#';
            else crt[(cycle - 1) / 40][(cycle - 1) % 40] = '.';

            cycle += 1;
            if ((cycle + 20) % 40 == 0) {
                total += cycle * X;
            }

            if (X - 1 <= (cycle - 1) % 40 && (cycle - 1) % 40 <= X + 1) crt[(cycle - 1) / 40][(cycle - 1) % 40] = '#';
            else crt[(cycle - 1) / 40][(cycle - 1) % 40] = '.';

            X += atoi(buffer + 5);
        }
    }

    printf("%d\n", total);

    for (int y = 0; y < 6; y++) {
        for (int x = 0; x < 40; x++) {
            printf("%c", crt[y][x]);
        }
        printf("\n");
    }
}
