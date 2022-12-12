#include <stdio.h>

int main() {
    FILE *fp = fopen("input.txt", "r");

    char line[5];
    int winstate;

    int score1 = 0, score2 = 0;

    while (fgets(line, 5, fp)) {
        // Part 1:
        int diff = line[2] - line[0];

        if (diff == 'X' - 'A') winstate = 1;
        else if (diff == 'Y' - 'A' || diff == 'X' - 'C') winstate = 2;
        else winstate = 0;

        score1 += (line[2] - 'W') + 3 * winstate;

        // Part 2:
        int mustwin = line[2] - 'X';
        int toplay = 0;

        if (mustwin == 1) toplay = line[0] - 'A' + 1;
        else if (mustwin == 2) toplay = (line[0] == 'C' ? 1 : line[0] - 'A' + 2);
        else toplay = (line[0] == 'A' ? 3 : line[0] - 'A');

        score2 += toplay + 3 * mustwin;
    }

    printf("%d\n", score1);
    printf("%d\n", score2);
}