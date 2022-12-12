#include <stdio.h>

int main() {
    FILE* fp = fopen("input.txt", "r");

    int a1, a2, b1, b2;
    int score1 = 0, score2 = 0;

    while (fscanf(fp, "%d-%d,%d-%d\n", &a1, &a2, &b1, &b2) != EOF) {
        if ((a1 <= b1 && b2 <= a2) || (b1 <= a1 && a2 <= b2)) {
            score1 += 1;
        }

        if ((a1 <= b1 && b1 <= a2) || (b1 <= a1 && a1 <= b2)) {
            score2 += 1;
        }
    }

    printf("%d\n", score1);
    printf("%d\n", score2);
}