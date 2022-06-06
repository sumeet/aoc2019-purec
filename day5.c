#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PROGRAM_SIZE 80000

typedef struct Program {
    int instructions[MAX_PROGRAM_SIZE];
    int pc;
} Program;

void run_program(Program *program, int input);
Program parse_input(char *filename);

int main(void) {
    Program parsed_program = parse_input("./day5.input");
    Program program = {0};
    program = parsed_program;
    printf("part1: ");
    run_program(&program, 1);
    printf("\n");

    program = parsed_program;
    printf("part2: ");
    run_program(&program, 5);
    printf("\n");
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

void run_program(Program *program, int input) {
    int intcode = program->instructions[program->pc];
    switch (parse_opcode(intcode)) {
        case 1: // add
            *param_for_mode(program, intcode, 3) = *param_for_mode(program, intcode, 1) + *param_for_mode(program, intcode, 2);
            program->pc += 4;
            break;
        case 2: // multiply
            *param_for_mode(program, intcode, 3) = *param_for_mode(program, intcode, 1) * *param_for_mode(program, intcode, 2);
            program->pc += 4;
            break;
        case 3: // input
            *param_for_mode(program, intcode, 1) = input;
            program->pc += 2;
            break;
        case 4: // output
            printf("%d\n", *param_for_mode(program, intcode, 1));
            program->pc += 2;
            break;
        case 5: // jump-if-true
            if (*param_for_mode(program, intcode, 1) != 0) {
                program->pc = *param_for_mode(program, intcode, 2);
            } else {
                program->pc += 3;
            }
            break;
        case 6: // jump-if-false
            if (*param_for_mode(program, intcode, 1) == 0) {
                program->pc = *param_for_mode(program, intcode, 2);
            } else {
                program->pc += 3;
            }
            break;
        //Opcode 7 is less than: if the first parameter is less than the second parameter, it stores 1 in the position given by the third parameter. Otherwise, it stores 0.
        case 7: // less-than
            bool is_less = *param_for_mode(program, intcode, 1) < *param_for_mode(program, intcode, 2);
            *param_for_mode(program, intcode, 3) = is_less ? 1 : 0;
            program->pc += 4;
            break;
        case 8: // equals
            bool is_equal = *param_for_mode(program, intcode, 1) == *param_for_mode(program, intcode, 2);
            *param_for_mode(program, intcode, 3) = is_equal ? 1 : 0;
            program->pc += 4;
            break;
        case 99:
            return;
        default:
            printf("invalid opcode %d at PC %d\n", program->instructions[program->pc], program->pc);
            exit(1);
    }

    return run_program(program, input);
}

Program parse_input(char *filename) {
    FILE *file = fopen(filename, "r");
    int this_intcode = 0;
    Program program = {0};
    int i = 0;
    int is_negative = false;
    for (char c = fgetc(file); c != EOF; c = fgetc(file)) {
        // there's a newline at the end of the file
        if (c == ',' || c == '\n') {
            program.instructions[i++] = is_negative ? this_intcode * -1 : this_intcode;
            this_intcode = 0;
            is_negative = false;
        } else if (c == '-') {
            is_negative = true;
        } else {
            this_intcode = (this_intcode * 10) + c - '0';
        }

    }
    return program;
}
