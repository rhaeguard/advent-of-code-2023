#include <stdio.h>
#include <stdlib.h>

#define SIZE 140

struct GearInfo {
    int count;
    long prod;
};

int coords[SIZE][SIZE] = {0};
struct GearInfo gears[SIZE][SIZE];

int check(int left, int right, int row, int num) {
    if (left>=0 && coords[row][left]) {
        if (coords[row][left] == -1) {
            gears[row][left].count++;
            gears[row][left].prod*=num;
        }
        return 1;
    }

    if (right < SIZE && coords[row][right]) {
        if (coords[row][right] == -1) {
            gears[row][right].count++;
            gears[row][right].prod*=num;
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
            int x = coords[row-1][i];
            if (x == -1) {
                gears[row-1][i].count++;
                gears[row-1][i].prod*=num;
            }
            if (x) {
                return 1;
            }
        }
    }

    if (row + 1 < SIZE) {
        for (int i = left; i <= right; i++) {
            int x = coords[row+1][i];
            if (x == -1) {
                gears[row+1][i].count++;
                gears[row+1][i].prod*=num;
            }
            if (x) {
                return 1;
            }
        }
    }

    return 0;
}

int main() {
    // initialize the gears array
    for (int i=0; i < SIZE; i++) {
        for (int j=0; j < SIZE; j++) {
            gears[i][j] = (struct GearInfo) {
                .count = 0,
                .prod = 1
            };
        }   
    }

    FILE* file = fopen("./input", "r");

    int y = 0;

    char buf[256];
    while (fgets(buf, 256, file)) {
        for (int x=0; x <256; x++) {
            if (buf[x] == 0 || buf[x] == '\n') {
                break;
            }

            if (!(buf[x] >= '0' && buf[x] <= '9') && buf[x] != '.') {
                coords[y][x] = 1;

                if (buf[x] == '*') {
                    coords[y][x] = -1; // gear symbol
                }
            }
        }
        y++;
    }

    fseek(file, 0, SEEK_SET);
    
    long sum_of_valid_parts = 0;

    y = 0;
    
    while (fgets(buf, 256, file)) {
        int i = 0;

        while (i < SIZE) {
            if (buf[i] >= '0' && buf[i] <= '9') {
                int left, right;
                left = i-1;

                int num = atoi(buf+i);

                while (i < SIZE && (buf[i] >= '0' && buf[i] <= '9')) {
                    i++;
                }

                right = i;

                if (check(left, right, y, num)) {
                    sum_of_valid_parts += num;
                }
            }
            i++;
        }
        y++;
    }

    long sum_of_gears = 0;
    for (y=0; y < SIZE; y++) {
        for (int x=0; x<SIZE; x++) {
            if (gears[y][x].count == 2) {
                sum_of_gears += gears[y][x].prod;
            }
        }
    }


    printf("Part 1 answer: %ld\n", sum_of_valid_parts);
    printf("Part 2 answer: %ld\n", sum_of_gears);

    fclose(file);
    return 0;
}