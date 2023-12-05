#include <stdio.h>
#include <stdlib.h>

typedef struct Ranges {
    long src; 
    long dest;
    long length;
} Range;

#define MAP_SIZE 40

void init(Range** range) {
    for (int i=0; i<MAP_SIZE;i++) {
        range[i] = NULL;
    }
}

int in_range(long num, Range* range) {
    return num >= range->src && num <= range->src + range->length;
}

long find_value(long src, Range** ranges) {

    for (int i=0; i<MAP_SIZE;i++) {
        Range* r = ranges[i];
        if (r == NULL) {
            break;
        }

        if (in_range(src, r)) {
            long diff = src - r->src;
            return r->dest + diff;
        }
    }

    return src;
}

int main() {
    long seeds[4] = {0L};
    int seed_size = 0;
    Range** seedToSoil[MAP_SIZE]; init(seedToSoil);
    Range** soilToFert[MAP_SIZE]; init(soilToFert);
    Range** fertToWatr[MAP_SIZE]; init(fertToWatr);
    Range** watToLight[MAP_SIZE]; init(watToLight);
    Range** lighToTemp[MAP_SIZE]; init(lighToTemp);
    Range** tempToHumi[MAP_SIZE]; init(tempToHumi);
    Range** humidToLoc[MAP_SIZE]; init(humidToLoc);

    FILE* file = fopen("./input", "r");

    char buf[256];

    {
        fgets(buf, 256, file);
        int i=7;
        while (buf[i] != '\n' && buf[i] != 0) {
            seeds[seed_size] = atol(buf+i);
            while(buf[i] != ' ' && buf[i] != 0 && buf[i] != '\n') {
                i++;
            }
            i++;
            seed_size++;
        }
    }

    int step_counter = 0;
    int arr_index = 0;
    while (fgets(buf, 256, file)) {
        if ((buf[0] == '\n' || buf[0] == 0)) {
            continue;
        }

        if (buf[0] >= 'a' && buf[0] <= 'z') {
            step_counter++;
            arr_index = 0;
            continue;
        }

        if (step_counter == 1) {
            // seed to soil
            long int d, s, l;
            if (sscanf(buf, "%ld %ld %ld", &d, &s, &l) == 3) {
                Range* r = (Range*) malloc (sizeof(Range));
                r->dest=d;
                r->src=s;
                r->length=l;
                seedToSoil[arr_index++] = r;
            }
        } else if (step_counter == 2) {
            // soil to fert
            long int d, s, l;
            if (sscanf(buf, "%ld %ld %ld", &d, &s, &l) == 3) {
                Range* r = (Range*) malloc (sizeof(Range));
                r->dest=d;
                r->src=s;
                r->length=l;
                soilToFert[arr_index++] = r;
            }
        } else if (step_counter == 3) {
            // fert to water
            long int d, s, l;
            if (sscanf(buf, "%ld %ld %ld", &d, &s, &l) == 3) {
                Range* r = (Range*) malloc (sizeof(Range));
                r->dest=d;
                r->src=s;
                r->length=l;
                fertToWatr[arr_index++] = r;
            }
        } else if (step_counter == 4) {
            // water to light
            long int d, s, l;
            if (sscanf(buf, "%ld %ld %ld", &d, &s, &l) == 3) {
                Range* r = (Range*) malloc (sizeof(Range));
                r->dest=d;
                r->src=s;
                r->length=l;
                watToLight[arr_index++] = r;
            }
        } else if (step_counter == 5) {
            // light to temp
            long int d, s, l;
            if (sscanf(buf, "%ld %ld %ld", &d, &s, &l) == 3) {
                Range* r = (Range*) malloc (sizeof(Range));
                r->dest=d;
                r->src=s;
                r->length=l;
                lighToTemp[arr_index++] = r;
            }
        } else if (step_counter == 6) {
            // temp to humid
            long int d, s, l;
            if (sscanf(buf, "%ld %ld %ld", &d, &s, &l) == 3) {
                Range* r = (Range*) malloc (sizeof(Range));
                r->dest=d;
                r->src=s;
                r->length=l;
                tempToHumi[arr_index++] = r;
            }
        } else if (step_counter == 7) {
            // humid to loc
            long int d, s, l;
            if (sscanf(buf, "%ld %ld %ld", &d, &s, &l) == 3) {
                Range* r = (Range*) malloc (sizeof(Range));
                r->dest=d;
                r->src=s;
                r->length=l;
                humidToLoc[arr_index++] = r;
            }
        }
    }

    long min = -1;

    for (int i = 0; i < seed_size; i++) {
        long x = seeds[i];
        x = find_value(x, seedToSoil);
        x = find_value(x, soilToFert);
        x = find_value(x, fertToWatr);
        x = find_value(x, watToLight);
        x = find_value(x, lighToTemp);
        x = find_value(x, tempToHumi);
        x = find_value(x, humidToLoc);

        if (i == 0) {
            min = x;
        } else {
            min = min > x ? x : min;
        }
    }
        printf("min: %ld\n", min);


    // TODO: free allocated memories
    fclose(file);

    return 0;
}