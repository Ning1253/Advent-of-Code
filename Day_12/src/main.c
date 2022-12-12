#include <stdio.h>

#include "queue.h"
#include <limits.h>

Coord start, end;

int main() {
    FILE *fp = fopen("input.txt", "r");
    static char map[41][173] = {0};
    static int visited[41][173] = {0};

    Queue q = malloc(sizeof(struct Queue));


    int index = 0;
    while (fread(map[index++], 1, 173, fp)) {
        fgetc(fp);
    }

    
    for (int y = 0; y < 41; y++) {
        for (int x = 0; x < 173; x++) {
            if (map[y][x] == 'S')
                start = (Coord){0, x, y};
            if (map[y][x] == 'E')
                end = (Coord){0, x, y};
        }
    }


    addQueue(q, start);

    map[start.y][start.x] = 'a';
    map[end.y][end.x] = 'z';

    visited[start.y][start.x] = 1;

    while (q->used) {
        Coord cur = popQueue(q);
        if (cur.x == end.x && cur.y == end.y) {
            printf("%d\n", cur.score);
            break;
        }

        if (cur.y < 40 && !visited[cur.y + 1][cur.x] && map[cur.y][cur.x] + 1 - map[cur.y + 1][cur.x] >= 0) {
            visited[cur.y + 1][cur.x] = 1;
            addQueue(q, (Coord){cur.score + 1, cur.x, cur.y + 1});
        }

        if (cur.y > 0 && !visited[cur.y - 1][cur.x] && map[cur.y][cur.x] + 1 - map[cur.y - 1][cur.x] >= 0) {
            visited[cur.y - 1][cur.x] = 1;
            addQueue(q, (Coord){cur.score + 1, cur.x, cur.y - 1});
        }

        if (cur.x < 172 && !visited[cur.y][cur.x + 1] && map[cur.y][cur.x] + 1 - map[cur.y][cur.x + 1] >= 0) {
            visited[cur.y][cur.x + 1] = 1;
            addQueue(q, (Coord){cur.score + 1, cur.x + 1, cur.y});
        }

        if (cur.x > 0 && !visited[cur.y][cur.x - 1] && map[cur.y][cur.x] + 1 - map[cur.y][cur.x - 1] >= 0) {
            visited[cur.y][cur.x - 1] = 1;
            addQueue(q, (Coord){cur.score + 1, cur.x - 1, cur.y});
        }
    }

    for (int y = 0; y < 41; y++)
        for (int x = 0; x < 173; x++)
            visited[y][x] = 0;
    

    visited[end.y][end.x] = 1;
    addQueue(q, end);

    while (q->used) {
        Coord cur = popQueue(q);
        if (map[cur.y][cur.x] == 'a') {
            printf("%d\n", cur.score);
            break;
        }

        if (cur.y < 40 && !visited[cur.y + 1][cur.x] && map[cur.y + 1][cur.x] + 1 - map[cur.y][cur.x] >= 0) {
            visited[cur.y + 1][cur.x] = 1;
            addQueue(q, (Coord){cur.score + 1, cur.x, cur.y + 1});
        }

        if (cur.y > 0 && !visited[cur.y - 1][cur.x] && map[cur.y - 1][cur.x] + 1 - map[cur.y][cur.x] >= 0) {
            visited[cur.y - 1][cur.x] = 1;
            addQueue(q, (Coord){cur.score + 1, cur.x, cur.y - 1});
        }

        if (cur.x < 172 && !visited[cur.y][cur.x + 1] && map[cur.y][cur.x + 1] + 1 - map[cur.y][cur.x] >= 0) {
            visited[cur.y][cur.x + 1] = 1;
            addQueue(q, (Coord){cur.score + 1, cur.x + 1, cur.y});
        }

        if (cur.x > 0 && !visited[cur.y][cur.x - 1] && map[cur.y][cur.x - 1] + 1 - map[cur.y][cur.x] >= 0) {
            visited[cur.y][cur.x - 1] = 1;
            addQueue(q, (Coord){cur.score + 1, cur.x - 1, cur.y});
        }
    }
}