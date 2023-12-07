#include <stdio.h>
#include <stdlib.h>

#define TOTAL_RACE_COUNT 4

int main() {
    int times[TOTAL_RACE_COUNT];
    int distances[TOTAL_RACE_COUNT];

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
        distances[j++] = n;

        while (buf[i] != ' ') {
            i++;
        }
    }

    int product = 1;

    for (i = 0; i < TOTAL_RACE_COUNT; i++) {
        int race_duration = times[i];
        int record_distance = distances[i];

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

    fseek(file, 0, SEEK_SET);

    // time
    char time_num[100];
    int ni = 0;
    fgets(buf, 100, file);
    i = 0;
    while (buf[i] != '\n' && buf[i] != 0) {
        if (buf[i] >= '0' && buf[i] <= '9') {
            time_num[ni++] = buf[i];
        }
        i++;
    }
    time_num[ni] = '\0';
    long race_duration = atol(time_num);

    // distance   
    char dist_num[100];
    ni = 0;
    fgets(buf, 100, file);
    i = 0;
    while (buf[i] != '\n' && buf[i] != 0) {
        if (buf[i] >= '0' && buf[i] <= '9') {
            dist_num[ni++] = buf[i];
            printf("%c\n", buf[i]);
        }
        i++;
    }
    printf("\n");
    dist_num[ni] = '\0';
    long record_distance = atol(dist_num);

    // (RACE_DURATION - TIME_DISTANCE) * TIME_DISTANCE > DISTANCE_RECORD
    long count = 0;
    for (long t=0; t <= race_duration; t++) {
        if ((race_duration - t) * t > record_distance) {
            count++;
        }
    }

    printf("Part 2 answer: %ld\n%ld\t%ld", count, race_duration, record_distance);
    fclose(file);

    return 0;
}