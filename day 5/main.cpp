#include <iostream>
#include <fstream>
#include <cmath>

typedef char byte;

using namespace std;

struct seat {
    int row;
    int seat_number;
    int seat_id;
};

struct vec {
    int x;
    int y;
};


vec partition(int low, int high, bool upper) {
    int half = 1 + (high - low) / 2;
    if (!upper) {
        return (vec) {.x = low, .y = high - half};
    }
    else {
        return (vec) {.x = low + half, .y = high};
    }
} 

seat solve_seat(string &partitioning) {
    seat output;
    int low = 1, high = 128;
    for (char const &character : partitioning) {
        if (character == 'L' || character == 'R') {
            break;
        }
        vec next_partitioning = partition(low, high, character == 'B');
        low = next_partitioning.x;
        high = next_partitioning.y;
    }
    output.row = high - 1;

    low = 1; high = 8;
    for (char const &character : partitioning) {
        if (character == 'L' || character == 'R') {
            vec next_partitioning = partition(low, high, character == 'R');
            low = next_partitioning.x;
            high = next_partitioning.y;
        }
    }
    output.seat_number = high - 1;

    output.seat_id = output.row * 8 + output.seat_number;

    return output;
}

int main() {
    ifstream input_file("input.txt");

    string current_line;
    int lines = 0;

    while (getline(input_file, current_line)) lines++;

    seat seats[lines];

    input_file = ifstream("input.txt");
    for (int i = 0; i < lines; i++) {
        getline(input_file, current_line);
        seats[i] = solve_seat(current_line);
    }
    input_file.close();

    int highest = 0;
    for (int i = 0; i < lines; i++) {
        int current_seat_id = seats[i].seat_id;
        if (current_seat_id > highest) {
            highest = current_seat_id;
        }
    }

    cout << "the highest seat id is: " << highest << endl;

    byte airplane[128][8] = {0};

    // part 2
    for (seat s : seats) {
        airplane[s.row][s.seat_number] = s.seat_id;
    }

    for (int i = 0; i < 128; i++) {
        for (int j = 1; j < 7; j++) {
            if (airplane[i][j] == 0 && airplane[i][j - 1] != 0 && airplane[i][j + 1] != 0) {
                cout << "Found empty seat with 2 neighbors: " << i * 8 + j << endl;
                break;
            }
        }
    }
}
