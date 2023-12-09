#include <stdio.h>
#include <stdlib.h>

#define ELEMENT_COUNT 21

int check_if_all_zeros(long* arr, int len) {
    for (int i = 0; i < len; i++) {
        if (arr[i] != 0) {return 0;}
    }
    return 1;
}

void reduce(
    long* input, 
    long* next_sum, 
    long* prev_sum
) {
    long steps[ELEMENT_COUNT][ELEMENT_COUNT] = {{0}};

    for (int i=0; i < ELEMENT_COUNT; i++) {
        steps[0][i] = input[i];
    }

    int j = 0; // indicates the depth
    int len = ELEMENT_COUNT; // the length of the current array

    long next = input[ELEMENT_COUNT-1];
    long prev = input[0];
    long sign = -1;
    
    while (
        !check_if_all_zeros(steps[j], len) && 
        j != ELEMENT_COUNT - 1 // boundary check
    ) {
        long* elements = steps[j];
        for (int k=0; k < len-1; k++) {
            steps[j+1][k] = elements[k+1] - elements[k];
        }
        next += steps[j+1][len-2];

        // the pattern is: N0 - N1 + N2 - N3 + N4 - N5....
        prev = prev + sign*steps[j+1][0];
        sign = sign * -1; 

        j++;
        len--;
    }

    *prev_sum = *prev_sum + prev;
    *next_sum = *next_sum + next;
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
            
            while (buf[i] != ' ') {i++;} // skip the non-whitespace chars
            while (buf[i] == ' ') {i++;} // skip whitespace chars

            n++;
            if (n >= ELEMENT_COUNT) {
                break;
            }
        }
        reduce(input, &next_sum, &prev_sum);
    }

    printf("Part 1 answer: %ld\n", next_sum); // 1681758908
    printf("Part 2 answer: %ld\n", prev_sum); // 803

    fclose(file);
    return 0;
}