#include <limits.h>
#include <sys/param.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Point {
    int x;
    int y;
} Point;

bool between(int num, int x, int y) {
    if (x < y) {
        return x <= num && num <= y;
    } else if (x > y) {
        return y <= num && num <= x;
    } else {
        return x == y == num;
    }
}

bool intersect(Point self0, Point self1, Point other0, Point other1, Point *intersection_out) {
    if (!between(self0.x, self0.y, other0.x)) {
        return false;
    }

    int a1 = self1.y - self0.y;
    int b1 = self0.x - self1.x;
    int c1 = a1 * self0.x + b1 * self0.y;

    int a2 = other1.y - other0.y;
    int b2 = other0.x - other1.x;
    int c2 = a2 * other0.x + b2 * other0.y;

    int delta = a1 * b2 - a2 * b1;

    if (delta == 0) {
        return false;
    }

    intersection_out->x = (b2 * c1 - b1 * c2) / delta;
    intersection_out->y = (a1 * c2 - a2 * c1) / delta;
    return true;
}

int main(void) {
    FILE *file = fopen("./day3.sample", "r");
    char *line = NULL;
    size_t line_size = 0;

    /////////////////////////
    // start handling line 1
    /////////////////////////
    getline(&line, &line_size, file);
    Point points_visited_line_1[10000];
    size_t num_points_line_1 = 0;

    int x = 0;
    int y = 0;

    char *inst_str;
    char *strtok_cursor = line;
    while ((inst_str = strtok(strtok_cursor, ","))) {
        char dir = inst_str[0];
        int num_steps = atoi(inst_str + 1);

        switch (dir) {
            case 'L':
                x -= num_steps;
                break;
            case 'U':
                y += num_steps;
                break;
            case 'R':
                x += num_steps;
                break;
            case 'D':
                y -= num_steps;
                break;
        }
        Point p = {.x = x, .y = y};
        points_visited_line_1[num_points_line_1++] = p;

        strtok_cursor = NULL;
    }


    /////////////////////////
    // start handling line 2
    /////////////////////////
    getline(&line, &line_size, file);
    strtok_cursor = line;
    x = y = 0;

    Point points_visited_line_2[10000];
    size_t num_points_line_2 = 0;
    while ((inst_str = strtok(strtok_cursor, ","))) {
        char dir = inst_str[0];
        int num_steps = atoi(inst_str + 1);

        switch (dir) {
            case 'L':
                x -= num_steps;
                break;
            case 'U':
                y += num_steps;
                break;
            case 'R':
                x += num_steps;
                break;
            case 'D':
                y -= num_steps;
                break;
        }
        Point p = {x = x, y = y};
        points_visited_line_2[num_points_line_2++] = p;

        strtok_cursor = NULL;
    }

    Point prev_point_wire_1 = { .x = 0, .y = 0 };
    int min_distance = INT_MAX;
    for (int i = 0; i < num_points_line_1; i++) {
        Point next_point_wire_1 = points_visited_line_1[i];

        Point prev_point_wire_2 = { .x = 0, .y = 0 };
        for (int j = 0; j < num_points_line_2; j++) {
            Point next_point_wire_2 = points_visited_line_2[j];

            // check for intersection
            Point intersection;
            if (intersect(prev_point_wire_1, next_point_wire_1,
                          prev_point_wire_2, next_point_wire_2, &intersection)) {
                int this_distance = abs(intersection.x) + abs(intersection.y);
                if (this_distance > 0) {
                    printf("intersect distance: %d\n", this_distance);
                    min_distance = MIN(min_distance, this_distance);
                }
                printf("intersection: (%d,%d)\n", intersection.x, intersection.y);
            }

//            printf("wire 1: (%d,%d) -> (%d,%d)\n", prev_point_wire_1.x, prev_point_wire_1.y, next_point_wire_1.x, next_point_wire_1.y);
//            printf("wire 2: (%d,%d) -> (%d,%d)\n", prev_point_wire_2.x, prev_point_wire_2.y, next_point_wire_2.x, next_point_wire_2.y);


            prev_point_wire_2 = next_point_wire_2;
        }

        prev_point_wire_1 = next_point_wire_1;
    }


    printf("part 1: %d\n", min_distance);
    free(line);
    fclose(file);
}

