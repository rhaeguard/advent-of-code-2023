#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Ranges {
    long src; 
    long dest;
    long length;
} Range;

typedef struct Input {
    long start;
    long end;
    long min;
} Input;


#define MAP_SIZE 400

Range** seedToSoil[MAP_SIZE];
Range** soilToFert[MAP_SIZE];
Range** fertToWatr[MAP_SIZE];
Range** watToLight[MAP_SIZE];
Range** lighToTemp[MAP_SIZE];
Range** tempToHumi[MAP_SIZE];
Range** humidToLoc[MAP_SIZE];

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

void range_overlaps(long start, long end, Range* range, long* out, Range** ranges) {
    long ss = range->src;
    long ee = range->src + range->length;

    // no overlap
    if (start > ee || ss > end) {
        return;
    } 

    long os = start > ss ? start : ss;
    long oe = end < ee ? end : ee;

    out[0] = os;
    out[1] = oe;

    long los = -1;
    long loe = -1;
    
    long ros = -1;
    long roe = -1;
    
    // left overlap
    if (os > start) {
        los = start;
        loe = os-1;

        out[2] = los;
        out[3] = loe;
    }


    // right overlap
    if (oe < end) {
        roe = end;
        ros = oe+1;

        out[4] = ros;
        out[5] = roe;
    }

    for (int y=0; y < 6; y++) {
        if (out[y] == -1) {
            continue;
        }
        out[y] = find_value(out[y], ranges);
    }
}

void init(Range** range) {
    for (int i=0; i<MAP_SIZE;i++) {
        range[i] = NULL;
    }
}

#define SIZE 1000

void phase(long* pairs, Range** the_range) {
    int pair_index = 0;
    long temp[SIZE];
    for (int k = 0; k < SIZE; k++) {
        temp[k] = -1;
    }

    for (int d = 0; d < SIZE; d+=2) {
        if (pairs[d] == -1) {continue;;}

        long start = pairs[d];
        long end = pairs[d+1];

        int found = 0;

        for (int k = 0; the_range[k] != NULL; k++) {
            long out[6] = {-1, -1, -1, -1, -1, -1};
            range_overlaps(start, end, the_range[k], out, the_range);

            if (out[0] != -1) {
                for (int y=0; y < 6; y+=2) {
                    if (out[y] != -1) {
                        temp[pair_index] = out[y];
                        temp[pair_index+1] = out[y+1];
                        pair_index += 2;
                    }
                }
                found = 1;
                break;
            }
        }
        if (!found) {
            temp[pair_index] = start;
            temp[pair_index+1] = end;
            pair_index+=2;
        }
    }


    for (int k = 0; k < SIZE; k++) {
        pairs[k] = temp[k];
    }
}

void p2(
    void* input
){
    Input* inp = input;

    long min = -1;
    for (long xx=inp->start; xx <= inp->end; xx++) {
        long x = xx;
        x = find_value(x, seedToSoil);
        x = find_value(x, soilToFert);
        x = find_value(x, fertToWatr);
        x = find_value(x, watToLight);
        x = find_value(x, lighToTemp);
        x = find_value(x, tempToHumi);
        x = find_value(x, humidToLoc);

        if (min == -1) {
            min = x;
        } else {
            min = min > x ? x : min;
        }
        printf("[%ld/%ld]\n", xx, inp->end);
    }
    inp->min = min;
}

int main() {
    long seeds[20] = {0L};
    int seed_size = 0;
    init(seedToSoil);
    init(soilToFert);
    init(fertToWatr);
    init(watToLight);
    init(lighToTemp);
    init(tempToHumi);
    init(humidToLoc);

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

    printf("Part 1 answer: %ld\n", min);

    min = -1;
    int seed_range_count = 10;
    pthread_t ts[seed_range_count];
    Input* inputs[seed_range_count];

    for (int i = 0; i < seed_size; i+=2) {
        long start = seeds[i];
        long length = seeds[i+1];
        long end = start + length - 1;

        Input* inp = malloc(sizeof(Input));
        inp->start = start;
        inp->end = end;
        inp->min = -1;

        inputs[i / 2] = inp;

        pthread_create(&ts[i/2], NULL, p2, (void *) inp);
    }

    for (int i = 0; i < seed_range_count; i++) {
        pthread_join(ts[i], NULL);

        Input* ii = inputs[i];
        if (min == -1) {
            min = ii->min;
        } else {
            min = min > ii->min ? ii->min : min;
        }
    }

    printf("Part 2 answer: %ld\n", min);

    /*
    this part 2 implementation is fast, but does not 
    really produce the correct answer on the actual input, works for the small input tho
    
    I might return to it to fix it.
    */
    int pair_index = 0;
    long pairs[SIZE];
    for (int k = 0; k < SIZE; k++) {
        pairs[k] = -1;
    }

    for (int i = 0; i < seed_size; i+=2) {
        long start = seeds[i];
        long length = seeds[i+1];
        long end = start + length - 1;
        pairs[pair_index] = start;
        pairs[pair_index+1] = end;
        pair_index += 2;
    }

    long temp[SIZE];
    for (int k = 0; k < SIZE; k++) {
        temp[k] = -1;
    }

    phase(pairs, seedToSoil);
    phase(pairs, soilToFert);
    phase(pairs, fertToWatr);
    phase(pairs, watToLight);
    phase(pairs, lighToTemp);
    phase(pairs, tempToHumi);
    phase(pairs, humidToLoc);

    min = -1;

    for (int k = 0; k < SIZE; k+=2) {
        if (pairs[k] == -1) {break;}
        if (min == -1) {
            min = pairs[k];
        } else {
            min = min > pairs[k] ? pairs[k] : min;
        }
    }

    /////

    printf("Part 2 answer: %ld\n", min);
    
    // TODO: free allocated memories
    fclose(file);

    pthread_exit(NULL);

    return 0;
}