#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* file = fopen("./input", "r");

    int final_score = 0;
    char buf[256];

    while (fgets(buf, 256, file)) {
        // skip until after :
        int i = 0;
        while (buf[i] != ':') {
            i++;
        }
        i+=2; // skips : and space after that
        int winning_numbers[100] = {0};
        while (buf[i]!='|') {
            int num = atoi(buf+i);
            winning_numbers[num] += 1;
            i+=3;
        }
        i+=2; // skips | and space after that
        int count = 0;
        while (buf[i]!=0 && buf[i]!='\n') {
            int num = atoi(buf+i);
            if (winning_numbers[num] > 0) {
                winning_numbers[num]--;
                count++;
            }
            i+=3;
        }

        if (count > 0) {
            final_score += (1 << (count - 1));
        }
    }

    printf("Part 1 answer: %d\n", final_score);

    fclose(file);
    return 0;
}