#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROGRAM_SIZE 80000

int run_program(int *program, int *pc);
void parse_input(char *filename, int *program, int *pc);

int main(void) {
    int parsed_program[MAX_PROGRAM_SIZE];
    int pc = 0;
    parse_input("./day2.input", parsed_program, &pc);

    int program[MAX_PROGRAM_SIZE];
    memcpy(program, parsed_program, sizeof(parsed_program));
    // part 1
    program[1] = 12;
    program[2] = 2;
    printf("part1: %d\n", run_program(program, &pc));

    // part 2
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            memcpy(program, parsed_program, sizeof(parsed_program));
            program[1] = i;
            program[2] = j;
            if (run_program(program, &pc) == 19690720) {
                printf("part2: %d\n", 100 * i + j);
            }
        }
    }

    return 0;
}

int run_program(int *program, int *pc) {
    int operand1 = program[program[*pc + 1]];
    int operand2 = program[program[*pc + 2]];
    int dest = program[*pc + 3];
    int this_op = program[*pc];

    switch (this_op) {
        case 1:
            program[dest] = operand1 + operand2;
            *pc += 4;
            break;
        case 2:
            program[dest] = operand1 * operand2;
            *pc += 4;
            break;
        case 99:
            *pc = 0;
            return program[0];
        default:
            printf("invalid opcode %d at PC %d\n", program[*pc], *pc);
            exit(1);
    }

    return run_program(program, pc);
}

void parse_input(char *filename, int *program, int *pc) {
    FILE *file = fopen(filename, "r");
    int this_intcode = 0;
    for (char c = fgetc(file); c != EOF; c = fgetc(file)) {
        // there's a newline at the end of the file
        if (c == ',' || c == '\n') {
            program[(*pc)++] = this_intcode;
            this_intcode = 0;
        } else {
            this_intcode = (this_intcode * 10) + c - '0';
        }
    }
    *pc = 0;
}

