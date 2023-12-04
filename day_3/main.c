#include <stdio.h>
#include <stdlib.h>

#define SIZE 140

struct CellInfo {
    int count;
    long prod;
    int is_symbol;
    int is_gear;
};

struct CellInfo symbols[SIZE][SIZE];

int check(int left, int right, int row, int num) {
    if (left>=0 && symbols[row][left].is_symbol) {
        if (symbols[row][left].is_gear) {
            symbols[row][left].count++;
            symbols[row][left].prod*=num;
        }
        return 1;
    }

    if (right < SIZE && symbols[row][right].is_symbol) {
        if (symbols[row][right].is_gear) {
            symbols[row][right].count++;
            symbols[row][right].prod*=num;
        }
        return 1;
    }

    if (left < 0) {
        left = 0;
    }

    if (right >= SIZE) {
        right = SIZE-1;
    }

    if (row - 1 >= 0) {
        for (int i = left; i <= right; i++) {
            if (symbols[row-1][i].is_gear) {
                symbols[row-1][i].count++;
                symbols[row-1][i].prod*=num;
            }
            if (symbols[row-1][i].is_symbol) {
                return 1;
            }
        }
    }

    if (row + 1 < SIZE) {
        for (int i = left; i <= right; i++) {
            if (symbols[row+1][i].is_gear) {
                symbols[row+1][i].count++;
                symbols[row+1][i].prod*=num;
            }
            if (symbols[row+1][i].is_symbol) {
                return 1;
            }
        }
    }

    return 0;
}

int main() {
    // initialize the symbols array
    for (int i=0; i < SIZE; i++) {
        for (int j=0; j < SIZE; j++) {
            symbols[i][j] = (struct CellInfo) {
                .count = 0,
                .prod = 1,
                .is_symbol = 0,
                .is_gear = 0,
            };
        }   
    }

    // open the input file
    FILE* file = fopen("./input", "r");

    int line_number = 0;

    char buf[256];
    // read each line
    while (fgets(buf, 256, file)) {
        // go thru each character till we reach the end of line
        for (int x=0; x <256; x++) {
            if (buf[x] == 0 || buf[x] == '\n') {
                break;
            }

            // record the cells that are non-numbers and dots - a.k.a. useful
            if (!(buf[x] >= '0' && buf[x] <= '9') && buf[x] != '.') {
                symbols[line_number][x].is_symbol = 1;

                // if the cell is a gear cell, note that down
                if (buf[x] == '*') {
                    symbols[line_number][x].is_gear = 1;
                }
            }
        }
        line_number++;
    }

    // move to the beginning of the file
    // because we need to read stuff again
    fseek(file, 0, SEEK_SET);
    
    long sum_of_valid_parts = 0;
    // reset the line counter
    line_number = 0;
    
    // for each line
    while (fgets(buf, 256, file)) {
        int i = 0;

        while (i < SIZE) {
            // if the char is a number
            if (buf[i] >= '0' && buf[i] <= '9') {
                int left, right;
                left = i-1;

                // atoi will try to read the chars into a number
                // starting from the provided position
                // so: '599...$%' will be 599
                int num = atoi(buf+i);

                // skip the numeric chars so that we can find the bounding box
                while (i < SIZE && (buf[i] >= '0' && buf[i] <= '9')) {
                    i++;
                }

                right = i;

                // check if the number is valid to be added to the sum
                if (check(left, right, line_number, num)) {
                    sum_of_valid_parts += num;
                }
            }
            i++;
        }
        line_number++;
    }

    long sum_of_gears_ratio = 0;
    for (line_number=0; line_number < SIZE; line_number++) {
        for (int x=0; x<SIZE; x++) {
            // if the gear is right next to exactly 2 numbers, add the gear ratio to the sum
            if (symbols[line_number][x].count == 2) {
                sum_of_gears_ratio += symbols[line_number][x].prod;
            }
        }
    }


    printf("Part 1 answer: %ld\n", sum_of_valid_parts);
    printf("Part 2 answer: %ld\n", sum_of_gears_ratio);

    fclose(file);
    return 0;
}