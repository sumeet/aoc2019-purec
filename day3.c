#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    FILE *file = fopen("./day3.sample", "r");
    char *line = NULL;
    size_t line_size = 0;
    getline(&line, &line_size, file);

    // tokenize wire 1
    strtok()

    getline(&line, &line_size, file);

    // tokenize wire 2


    free(line);
    fclose(file);
    return 0;
}

