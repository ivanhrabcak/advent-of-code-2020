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

    int current_line = 0;
    int accumulator = 0;

    instruction current_instuction;

    bool executed_instructions[lines];
    for (int i = 0; i < lines; i++) {
        executed_instructions[i] = false;
    }

    while (executed_instructions[current_line] != true) {
        executed_instructions[current_line] = true;

        current_instuction = instructions[current_line];

        if (current_instuction.instr == ACC) {
            accumulator += current_instuction.value;
            current_line++;
        }
        else if (current_instuction.instr == JMP) {
            current_line += current_instuction.value;
        }
        else {
            current_line++;
        }   
    }

    printf("%d\n", accumulator);

    return 0;
}