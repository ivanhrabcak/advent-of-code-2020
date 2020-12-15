#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define NOP 0
#define JMP 1
#define ACC 2

typedef struct instruction {
    int value;
    int instr;
} instruction;

int string_to_instruction(char *string) {
    if (strcmp(string, "jmp") == 0) {
        return JMP;
    }
    else if (strcmp(string, "acc") == 0) {
        return ACC;
    }
    else if (strcmp(string, "nop") == 0) {
        return NOP;
    }
    else {
        return -1;
    }
}

bool string_contains(char *token, char *string) {
    return strstr(string, token) != NULL;
}

bool does_program_terminate(instruction *program, int program_len) {
    instruction current_instuction;
    int instruction_number = 0;

    bool executed_instructions[program_len];
    for (int i = 0; i < program_len; i++) {
        executed_instructions[i] = false;
    }

    while (executed_instructions[instruction_number] != true) {
        if (instruction_number == program_len) {
            return true;
        }

        executed_instructions[instruction_number] = true;

        current_instuction = program[instruction_number];

        if (current_instuction.instr == JMP) {
            instruction_number += current_instuction.value;
        }
        else {
            instruction_number++;
        }
    }
    return false;
}

int get_accumulator_for_program(instruction *program, int program_len) {
    int accumulator = 0;
    int instruction_number = 0;

    instruction current_instruction;
    while (instruction_number != program_len) {
        current_instruction = program[instruction_number];

        if (current_instruction.instr == JMP) {
            instruction_number += current_instruction.value;
        }
        else if (current_instruction.instr == ACC) {
            accumulator += current_instruction.value;
            instruction_number++;
        }
        else {
            instruction_number++;
        }
    }

    return accumulator;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        return 1;
    }

    int lines = 0;

    char current_char = ' ';
    while (current_char != EOF) {
        current_char = fgetc(file);

        if (current_char == '\n') {
            lines++;
        }
    }
    lines++;
    fclose(file);

    instruction instructions[lines];

    file = fopen("input.txt", "r");

    for (int i = 0; i < lines; i++) {
        char tok[3];
        int value;

        fscanf(file, "%3s %d\n", &tok, &value);
        instructions[i] = (instruction) {.instr = string_to_instruction(tok), .value = value};
    }
    fclose(file);

    for (int i = 0; i < lines; i++) {
        instruction current_instruction = instructions[i];
        if (current_instruction.instr == JMP) {
            instructions[i] = (instruction) {.instr = NOP, .value = current_instruction.value};
            if (does_program_terminate(instructions, lines)) {
                break;
            }
            else {
                instructions[i] = current_instruction;
            }
        }
        else if (current_instruction.instr == NOP) {
            instructions[i] = (instruction) {.instr = JMP, .value = current_instruction.value};
            if (does_program_terminate(instructions, lines)) {
                break;
            }
            else {
                instructions[i] = current_instruction;
            }
        }
    }

    printf("%d\n", get_accumulator_for_program(instructions, lines));
    return 0;
}