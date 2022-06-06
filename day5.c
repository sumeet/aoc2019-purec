#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROGRAM_SIZE 80000

typedef struct Program {
    int instructions[MAX_PROGRAM_SIZE];
    int pc;
} Program;

int run_program(Program *program);
Program parse_input(char *filename);

int main(void) {
    Program parsed_program = parse_input("./day2.input");
    Program program = {0};
    program = parsed_program;
    program.instructions[1] = 12;
    program.instructions[2] = 2;
    printf("part1: %d\n", run_program(&program));

    return 0;
}

int imm_op(Program *program, int offset) {
    return program->instructions[program->pc + offset];
}

int pos_op(Program *program, int offset) {
    return program->instructions[program->instructions[program->pc + offset]];
}

int run_program(Program *program) {
    switch (imm_op(program, 0)) {
        case 1:
            program->instructions[imm_op(program, 3)] = pos_op(program, 1) + pos_op(program, 2);
            program->pc += 4;
            break;
        case 2:
            program->instructions[imm_op(program, 3)] = pos_op(program, 1) * pos_op(program, 2);
            program->pc += 4;
            break;
        case 99:
            program->pc = 0;
            return program->instructions[0];
        default:
            printf("invalid opcode %d at PC %d\n", program->instructions[program->pc], program->pc);
            exit(1);
    }

    return run_program(program);
}

Program parse_input(char *filename) {
    FILE *file = fopen(filename, "r");
    int this_intcode = 0;
    Program program = {0};
    int i = 0;
    for (char c = fgetc(file); c != EOF; c = fgetc(file)) {
        // there's a newline at the end of the file
        if (c == ',' || c == '\n') {
            program.instructions[i++] = this_intcode;
            this_intcode = 0;
        } else {
            this_intcode = (this_intcode * 10) + c - '0';
        }
    }
    return program;
}
