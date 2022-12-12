#include <stdio.h>

int main() {
    FILE* fp = fopen("input.txt", "r");
    char line[10];
    int temp;


    int best[3] = {0, 0, 0};
    int count = 0;

    fseek(fp, 0, SEEK_SET);

    while (!feof(fp)) {
        if (fgets(line, 10, fp)) {

            if (line[0] != '\n') {
                sscanf(line, "%d", &temp);
                count += temp;
            } 
            
            else {
                int minindex = -1;

                for (int i = 0; i < 3; i++) {
                    if (best[i] < count)
                        if (minindex == -1 || best[i] < best[minindex]) minindex = i;
                }

                if (minindex != -1) best[minindex] = count;
                count = 0;
            }
        }
    }

    int sum = 0, max = 0;
    for (int i = 0; i < 3; i++) {
        sum += best[i];
        if (best[i] > max) max = best[i];
    }

    printf("%d\n", max);
    printf("%d\n", sum);
}