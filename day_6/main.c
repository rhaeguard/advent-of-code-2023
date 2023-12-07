#include <stdio.h>
#include <stdlib.h>

#define TOTAL_RACE_COUNT 4

long count_valid_combinations(long race_duration, long record_distance) {
    // (RACE_DURATION - TIME_DISTANCE) * TIME_DISTANCE > DISTANCE_RECORD
    long count = 0;
    for (long t=0; t <= race_duration; t++) {
        if ((race_duration - t) * t > record_distance) {
            count++;
        }
    }
    return count;
}

long read_full_number(FILE* file) {
    char time_num[100];
    int ni = 0;
    char buf[100];
    fgets(buf, 100, file);
    int i = 0;
    while (buf[i] != '\n' && buf[i] != 0) {
        if (buf[i] >= '0' && buf[i] <= '9') {
            time_num[ni++] = buf[i];
        }
        i++;
    }
    time_num[ni] = '\0';
    return atol(time_num);
}

void populate_array(FILE* file, long* arr, int offset) {
    int j = 0;
    char buf[100];
    fgets(buf, 100, file);
    for (int k = 0; k < TOTAL_RACE_COUNT; k++) {
        while (buf[offset] == ' ') {
            offset++;
        }
        int n = atoi(buf+offset);
        arr[j++] = n;

        while (buf[offset] != ' ') {
            offset++;
        }
    }
}

int main() {
    long times[TOTAL_RACE_COUNT];
    long distances[TOTAL_RACE_COUNT];

    FILE* file = fopen("./input", "r");

    populate_array(file, times, 5); // offset 5 skips Time:
    populate_array(file, distances, 10); // offset 10 skips Distance:

    long product = 1;

    for (int i = 0; i < TOTAL_RACE_COUNT; i++) {
        int race_duration = times[i];
        int record_distance = distances[i];
        product *= count_valid_combinations(race_duration, record_distance);
    }

    printf("Part 1 answer: %ld\n", product);

    fseek(file, 0, SEEK_SET);

    long race_duration = read_full_number(file);
    long record_distance = read_full_number(file);
    long count = count_valid_combinations(race_duration, record_distance);

    printf("Part 2 answer: %ld\n", count);
    fclose(file);

    return 0;
}