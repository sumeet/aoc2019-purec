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

int parse_opcode(int intcode) {
   // for intcode = 1002, this returns just 2 (the last 2 digits)
   return intcode % 100;
}

typedef enum ParamMode {
    PARAM_MODE_POSITION = 0,
    PARAM_MODE_IMMEDIATE = 1,
} ParamMode;

// for intcode = 1002, 1 => 0 ; 2 => 1 ; 3 => 0
ParamMode get_param_mode(int intcode, int param_offset) {
    intcode /= 100;
    int param_mode = 0;
    for (int i = 0; i < param_offset; i++) {
        param_mode = intcode % 10;
        intcode /= 10;
    }
    return param_mode;
}

int *param_for_mode(Program *program, int intcode, int offset) {
    switch (get_param_mode(intcode, offset)) {
        case PARAM_MODE_POSITION:
            return &program->instructions[program->instructions[program->pc + offset]];
        case PARAM_MODE_IMMEDIATE:
            return &program->instructions[program->pc + offset];
    }
}

int run_program(Program *program) {
    int intcode;
    switch (intcode = program->instructions[program->pc]) {
        case 1:
            *param_for_mode(program, intcode, 3) = *param_for_mode(program, intcode, 1) + *param_for_mode(program, intcode, 2);
            program->pc += 4;
            break;
        case 2:
            *param_for_mode(program, intcode, 3) = *param_for_mode(program, intcode, 1) * *param_for_mode(program, intcode, 2);
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
