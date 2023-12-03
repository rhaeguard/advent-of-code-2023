#include <stdio.h>
#include <stdlib.h>

#define SIZE 140

int coords[SIZE][SIZE] = {0};

int check(int left, int right, int row) {
    if ((left>=0 && coords[row][left]) || (right < SIZE && coords[row][right])) {
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
            if (coords[row-1][i]) {
                return 1;
            }
        }
    }

    if (row + 1 < SIZE) {
        for (int i = left; i <= right; i++) {
            if (coords[row+1][i]) {
                return 1;
            }
        }
    }

    return 0;
}

int main() {
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

                if (check(left, right, y)) {
                    sum_of_valid_parts += num;
                }
            }
            i++;
        }
        y++;
    }

    printf("Part 1 answer: %ld\n", sum_of_valid_parts);

    fclose(file);
    return 0;
}