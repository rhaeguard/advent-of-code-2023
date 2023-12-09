#include <stdio.h>
#include <stdlib.h>

#define ELEMENT_COUNT 21

int check_if_all_zeros(long* arr[ELEMENT_COUNT], int len) {
    for (int i = 0; i < len; i++) {
        if (arr[i] != 0) {
            return 0;
        }
    }
    return 1;
}

void reduce(long* input[ELEMENT_COUNT], long* next_sum, long* prev_sum) {
    long steps[ELEMENT_COUNT+1][ELEMENT_COUNT+1] = {{0}};

    for (int i=0; i < ELEMENT_COUNT; i++) {
        steps[0][i] = input[i];
    }

    int j = 0;
    int len = ELEMENT_COUNT;
    long t = input[ELEMENT_COUNT-1];
    long z = input[0];
    long sign = -1;
    while (!check_if_all_zeros(steps[j], len)) {
        long* elements = steps[j];
        if (j == ELEMENT_COUNT - 1) {
            break;
        }

        for (int k=0; k < len-1; k++) {
            long a = elements[k+1] - elements[k];
            steps[j+1][k] = a;
        }
        t += steps[j+1][len-2];
        z = z + sign*steps[j+1][0];
        sign = sign * -1;
        j++;
        len--;
    }

    *prev_sum = *prev_sum + z;
    *next_sum = *next_sum + t;
}

int main() {
    FILE* file = fopen("./input", "r");

    char buf[512];

    long next_sum = 0;
    long prev_sum = 0;

    while (fgets(buf, 512, file)) {
        int i = 0;
        int n = 0;
        long input[ELEMENT_COUNT] = {0};
        while (buf[i] != '\n') {
            input[n] = atol(buf+i);
            
            while (buf[i] != ' ') {i++;}
            while (buf[i] == ' ') {i++;}

            n++;
            if (n >= ELEMENT_COUNT) {
                break;
            }
        }

        reduce(input, &next_sum, &prev_sum);

    }

    printf("Part 1 answer: %ld\n", next_sum);
    printf("Part 2 answer: %ld\n", prev_sum);

    fclose(file);
    return 0;
}