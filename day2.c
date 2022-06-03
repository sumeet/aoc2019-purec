#include <stdio.h>
#include <stdlib.h>

#define MAX_PROGRAM_SIZE 80000

int run_program(int *program, int *pc);
void parse_input(char *filename, int *program, int *pc);

int main(void) {
    int program[MAX_PROGRAM_SIZE]; // TODO: initialize these to be -1?
    int pc = 0;
    parse_input("./day2.input", program, &pc);
    program[1] = 12;
    program[2] = 2;
    run_program(program, &pc);
    printf("%d\n", program[0]);
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
            return program[0];
        default:
            printf("invalid status code %d at PC %d\n", program[*pc], *pc);
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

