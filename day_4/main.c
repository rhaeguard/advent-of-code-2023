#include <stdio.h>
#include <stdlib.h>

#define CARD_COUNT 203

int main() {
    FILE* file = fopen("./input", "r");

    int final_score = 0;
    char buf[256];

    // each index corresponds to a card id
    // it's one-based, so 0th element is ignored
    int card_counts[CARD_COUNT + 1] = {0};

    // basic idea is to add all the winning numbers to
    // an array of 100 elements because the max number is 99
    // and then we can basically perform an O(1) lookup
    // to check if a number is in the winning list or not

    while (fgets(buf, 256, file)) {
        // skip until after :
        int i = 5; // skips 'Card '
        int card_num = atoi(buf+i);
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

        card_counts[card_num] += 1;
        if (count > 0) {
            for (int card=card_num+1; card <= card_num+count; card++) {
                card_counts[card] += card_counts[card_num];   
            }
            // basically 2^(count - 1)
            final_score += (1 << (count - 1));
        }
    }

    int final_card_count = 0;

    for (int x = 1; x <= CARD_COUNT; x++) {
        final_card_count += card_counts[x];
    }

    printf("Part 1 answer: %d\n", final_score);
    printf("Part 2 answer: %d\n", final_card_count);

    fclose(file);
    return 0;
}