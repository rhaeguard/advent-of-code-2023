#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int main() {
    FILE* file = fopen("./input", "r");

    char buf[1024];

    int line = 1;

    int sum_of_possible_lines = 0;
    long sum_of_cubes = 0;

    while (fgets(buf, 1024, file)) {
        int i = 0;

        while (buf[i] != ':') {
            i++;
        }
        i++; // get past :

        int r = 0;
        int g = 0;
        int b = 0;

        int rm = 0;
        int gm = 0;
        int bm = 0;

        int possible = 1;
        while (buf[i] != '\n' && buf[i] != 0) {
            if (buf[i] == ';') { // each hand is delimited by ;
                possible = possible && (r <= 12 && g <= 13 && b <= 14);
                
                rm = max(rm, r);
                gm = max(gm, g);
                bm = max(bm, b);
                
                r = 0;
                g = 0;
                b = 0;

            }
            if (buf[i] >= '0' && buf[i] <= '9') {
                int s = i; // start
                while (buf[i] != ' ') {
                    i++;
                }

                int num = atoi(buf+s);

                int ch = buf[++i];
                if (ch == 'r') {
                    r = num;
                } else if (ch == 'g') {
                    g = num;
                } else {
                    b = num;
                }
            }
            i++;
        }
        rm = max(rm, r);
        gm = max(gm, g);
        bm = max(bm, b);

        sum_of_cubes += (rm * gm * bm);

        if (possible && (r <= 12 && g <= 13 && b <= 14)) {
            sum_of_possible_lines += line;
        }

        line++;
    }

    printf("Part 1 answer: %d\n", sum_of_possible_lines);
    printf("Part 2 answer: %ld\n", sum_of_cubes);

    fclose(file);
    return 0;
}