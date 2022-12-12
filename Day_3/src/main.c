#include <stdio.h>
#include <string.h>

#include "map.h"

MAP(SI, char, int, 1*, 0, -1);

int main() {
    FILE *fp = fopen("input.txt", "r");
    char buffer[50], buffer2[50], buffer3[50];

    int charcount;
    int score = 0;
    int linecount = 0;


    while (fgets(buffer, 50, fp)) {
        linecount += 1;
        int flag = 0;
        charcount = strlen(buffer);

        for (int i = 0; i < charcount / 2; i++) {
            for (int j = charcount / 2; j < charcount; j++) {
                if (buffer[j] == buffer[i]) {
                    score += buffer[i] - (buffer[i] > 96 ? 96 : 38);
                    flag = 1;
                    break;
                }
            }

            if (flag) break;
        }
    }

    printf("%d\n", score);


    fseek(fp, 0, SEEK_SET);
    score = 0;
    

    for (int i = 0; i < linecount / 3; i++) {
        // Create String->Int Map (definition above made these defaultdicts, default=0)
        SIMap m = initSIMap();

        if (!(fgets(buffer, 50, fp) && fgets(buffer2, 50, fp) && 
              fgets(buffer3, 50, fp))) break;

        int c1 = strlen(buffer), c2 = strlen(buffer2), c3 = strlen(buffer3);

        // For each char in str2 add char to map, give it value 1
        for (int i = 0; i < c2 - 1; i++) {
            addSIMap(m, buffer2[i], 1);
        }

        // For each char in str3 if char in map, set val to 2, otherwise set it to 0
        for (int i = 0; i < c3 - 1; i++) {
            addSIMap(m, buffer3[i], readSIMap(m, buffer3[i]) >= 1 ? 2 : 0);
        }

        // For each char in str1 if char in map has val 2 then it is in all 3 strings, we are done. 
        for (int i = 0; i < c1; i++) {
            if (readSIMap(m, buffer[i]) == 2) {
                score += buffer[i] - (buffer[i] > 96 ? 96 : 38);
                break;
            }
        }
    }

    printf("%d\n", score);
}