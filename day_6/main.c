#include <stdio.h>
#include <stdlib.h>

#define TOTAL_RACE_COUNT 4

int main() {
    int times[TOTAL_RACE_COUNT];
    int distance[TOTAL_RACE_COUNT];

    FILE* file = fopen("./input", "r");

    char buf[100];

    // time
    fgets(buf, 100, file);
    int i = 5;
    int j = 0;

    for (int k = 0; k < TOTAL_RACE_COUNT; k++) {
        while (buf[i] == ' ') {
            i++;
        }
        int n = atoi(buf+i);
        times[j++] = n;

        while (buf[i] != ' ') {
            i++;
        }
    }

    // distance
    fgets(buf, 100, file);
    i = 9;
    j = 0;
    for (int k = 0; k < TOTAL_RACE_COUNT; k++) {
        while (buf[i] == ' ') {
            i++;
        }
        int n = atoi(buf+i);
        distance[j++] = n;

        while (buf[i] != ' ') {
            i++;
        }
    }

    int product = 1;

    for (i = 0; i < TOTAL_RACE_COUNT; i++) {
        int race_duration = times[i];
        int record_distance = distance[i];

        // (RACE_DURATION - TIME_DISTANCE) * TIME_DISTANCE > DISTANCE_RECORD
        int count = 0;
        for (int t=0; t <= race_duration; t++) {
            if ((race_duration - t) * t > record_distance) {
                count++;
            }
        }
        product *= count;
    }

    printf("Part 1 answer: %d\n", product);

    fclose(file);

    return 0;
}