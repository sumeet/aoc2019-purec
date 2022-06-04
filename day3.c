#include <limits.h>
#include <sys/param.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define GRID_SIZE 20000

static int grid[GRID_SIZE][GRID_SIZE];

int main(void) {
    FILE *file = fopen("./day3.sample", "r");
    char *line = NULL;
    size_t line_size = 0;
    getline(&line, &line_size, file);

    int x = GRID_SIZE / 2;
    int y = GRID_SIZE / 2;

    // tokenize wire 1
    printf("line 1:\n");
    char *inst_str;
    char *strtok_cursor = line;
    while ((inst_str = strtok(strtok_cursor, ","))) {
        char dir = inst_str[0];
        int num_steps = atoi(inst_str + 1);

        switch (dir) {
            case 'L':
                for (int i = 0; i < num_steps; i++) {
                    x--;
                    grid[y][x]++;
                    printf("visited (%d,%d)\n", x, y);
                }
                break;
            case 'U':
                for (int i = 0; i < num_steps; i++) {
                    y++;
                    grid[y][x]++;
                    printf("visited (%d,%d)\n", x, y);
                }
                break;
            case 'R':
                for (int i = 0; i < num_steps; i++) {
                    x++;
                    grid[y][x]++;
                    printf("visited (%d,%d)\n", x, y);
                }
                break;
            case 'D':
                for (int i = 0; i < num_steps; i++) {
                    y--;
                    grid[y][x]++;
                    printf("visited (%d,%d)\n", x, y);
                }
                break;
        }

//        printf("direction: %c, num_steps: %d\n", dir, num_steps);
        strtok_cursor = NULL;
    }

    getline(&line, &line_size, file);

    int min_distance = INT_MAX;

    // tokenize wire 2
    printf("line 2:\n");
    strtok_cursor = line;
    x = y = GRID_SIZE / 2;
    while ((inst_str = strtok(strtok_cursor, ","))) {
        char dir = inst_str[0];
        int num_steps = atoi(inst_str + 1);

        switch (dir) {
            case 'L':
                for (int i = 0; i < num_steps; i++) {
                    x--;
                    printf("visited (%d,%d)\n", x, y);
                    if (grid[y][x] > 0) {
                        min_distance = MIN(min_distance, y * x);
                    }
                }
                break;
            case 'U':
                for (int i = 0; i < num_steps; i++) {
                    y++;
                    printf("visited (%d,%d)\n", x, y);
                    if (grid[y][x] > 0) {
                        min_distance = MIN(min_distance, y * x);
                    }
                }
                break;
            case 'R':
                for (int i = 0; i < num_steps; i++) {
                    x++;
                    printf("visited (%d,%d)\n", x, y);
                    if (grid[y][x] > 0) {
                        min_distance = MIN(min_distance, y * x);
                    }
                }
                break;
            case 'D':
                for (int i = 0; i < num_steps; i++) {
                    y--;
                    printf("visited (%d,%d)\n", x, y);
                    if (grid[y][x] > 0) {
                        min_distance = MIN(min_distance, (abs(y) - GRID_SIZE / 2) * (abs(x) - GRID_SIZE / 2));
                    }
                }
                break;
        }
        strtok_cursor = NULL;
    }

    printf("part 1: %d\n", min_distance);

    free(line);
    fclose(file);
}

