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

bool between(float num, float x, float y) {
    if (x < y) {
        return x <= num && num <= y;
    } else if (x > y) {
        return y <= num && num <= x;
    } else {
        return x == y == num;
    }
}
//
bool intersects(Point self0, Point self1, Point other0, Point other1, Point *intersection_out) {
    float x0 = (float) self0.x;
    float y0 = (float) self0.y;
    float x1 = (float) self1.x;
    float y1 = (float) self1.y;
    float x2 = (float) other0.x;
    float y2 = (float) other0.y;
    float x3 = (float) other1.x;
    float y3 = (float) other1.y;
    float x_cross = ((x0 * y1 - y0 * x1) * (x2 - x3) - (x0 - x1) * (x2 * y3 - y2 * x3)) / ((x0 - x1) * (y2 - y3) - (y0 - y1) * (x2 - x3));
    float y_cross = ((x0 * y1 - y0 * x1) * (y2 - y3) - (y0 - y1) * (x2 * y3 - y2 * x3)) / ((x0 - x1) * (y2 - y3) - (y0 - y1) * (x2 - x3));
    if ((between(x_cross, x0, x1) || between(x_cross, x2, x3))
        &&
        (between(y_cross, y0, y1) || between(y_cross, y2, y3))) {
        intersection_out->x = (int) x_cross;
        intersection_out->y = (int) y_cross;
        return true;
    }
    return false;
}

int main(void) {
    FILE *file = fopen("./day3.input", "r");
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
            if (intersects(prev_point_wire_1, next_point_wire_1,
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

