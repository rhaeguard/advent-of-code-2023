#include <stdio.h>
#include <stdlib.h>

#define GAMES 100
#define COLORS 3

int main() {
    FILE* file = fopen("./input", "r");

    char buf[1024];

    int line = 1;

    int sum = 0;

    while (fgets(buf, 1024, file)) {
        int i = 0;

        while (buf[i] != ':') {
            i++;
        }
        i++; // get past :

        int r = 0;
        int g = 0;
        int b = 0;
        int possible = 1;
        while (buf[i] != '\n' && buf[i] != 0) {
            if (buf[i] == ';') { // each hand is delimited by ;
                if (!(r <= 12 && g <= 13 && b <= 14)) {
                    possible = 0;
                    break;
                }

                r = 0;
                g = 0;
                b = 0;

            }
            if (buf[i] >= '0' && buf[i] <= '9') {
                int s = i; // start
                int num = 0;
                while (buf[i] != ' ') {
                    i++;
                }

                num += atoi(buf+s);

                int ch = buf[++i];
                if (ch == 'r') {
                    r += num;
                } else if (ch == 'g') {
                    g += num;
                } else {
                    b += num;
                }
            }
            i++;
        }
        if (possible && (r <= 12 && g <= 13 && b <= 14)) {
            sum += line;
        }

        line++;
    }

    printf("Part 1 answer: %d\n", sum);

    fclose(file);
    return 0;
}