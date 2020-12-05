#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

#define len(x) (sizeof(x) / sizeof(x[0])) 

typedef struct position {
    int x;
    int y;
} position; 

bool file_exists(const char *filename) {
    return access(filename, F_OK) == 0; 
}

void add_slope(position *position1, position *position2, int array_len) {
    position1->x = position1->x + position2->x;
    position1->y = (position1->y + position2->y) % array_len; // is this right?
}

int get_trees_encountered_for_slope(position* slope, char **input, position *input_size) {
    position current_position = {.x = 0, .y = 0};

    int counter = 0;

    while (!(current_position.x >= input_size->x) && !(current_position.y >= input_size->y)) {
        char current_char = input[current_position.x][current_position.y];
        if (current_char == '#') {
            counter++;
        }
        add_slope(&current_position, slope, input_size->y);
    }
    return counter;
}

int main() {
    if (!file_exists("input.txt")) {
        printf("File input.txt doesn't exist!");
        return 1;
    }

    FILE *input_file = fopen("input.txt", "r");
    
    // count number of newlines and characters between newlines
    int newline_counter = 0;
    int chars_between_newlines = 0;
    bool has_encountered_newline = false;
    for (char c = getc(input_file); c != EOF; c = getc(input_file)) {
        if (c == '\n' && !has_encountered_newline) {
            has_encountered_newline = true;
            newline_counter++;
            continue;
        }
        else if (c == '\n'){
            newline_counter++;
        }

        if (!has_encountered_newline) {
            chars_between_newlines++;
        }
    }
    fclose(input_file);

    char **field = malloc(sizeof(char *) * newline_counter);

    for (int i = 0; i < newline_counter; i++) {
        field[i] = malloc(sizeof(char) * chars_between_newlines);
    }

    // read the file one more time to fill the field array
    int i = 0;
    int j = 0;

    input_file = fopen("input.txt", "r");
    for (char c = getc(input_file); c != EOF; c = getc(input_file)) {
        if (c == '\n') {
            i++;
            j = 0;
            continue;
        }
        field[i][j] = c;
        j++;
    }

    position slope = {.x = 1, .y = 3};
    position input_size = {.x = newline_counter, .y = chars_between_newlines};
    printf("part 1 trees encountered: %d\n", get_trees_encountered_for_slope(&slope, field, &input_size));

    position slopes[5] = {{.x = 1, .y = 1},
                             {.x = 1, .y = 3},
                             {.x = 1, .y = 5},
                             {.x = 1, .y = 7},
                             {.x = 2, .y = 1}};
    long result = 1;
    for (int k = 0; k < 5; k++) {
        result *= get_trees_encountered_for_slope(&slopes[k], field, &input_size);
    }

    printf("part 2 result: %ld\n", result);
    return 0;
}