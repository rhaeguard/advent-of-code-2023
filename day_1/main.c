#include <stdio.h>

int equals(char* line, int start, char* what, int what_size) {

    for (int i = 0; i < what_size; i++) {
        char lch = line[start+i];
        if (lch == 0 || lch == '\n') {
            return 0;
        }

        char wch = what[i];

        if (lch != wch) {
            return 0;
        }
    }

    return 1;
}

int main() {
    // part 1 - start
    FILE* p = fopen("./input", "r");
    if (p == NULL) {
        printf("error!");
        return 1;
    }

    char buf[128];

    int sum = 0;

    while (fgets(buf, 128, p)) {
        char f = 0;
        char l = 0;
        
        int i = 0;
        while (buf[i] != '\n') {
            int is_num = buf[i] >= '0' && buf[i] <= '9';
            if (is_num) {
                if (!f) {
                    f = buf[i];
                    l = buf[i];
                } else {
                    l = buf[i];
                }
            }
            i++;
        }
        sum += ((f - 48) * 10 + (l-48));
    }

    printf("Part 1 answer: %d\n", sum);

    // part 1 - end

    fseek(p, 0, SEEK_SET);

    char line[128];

    sum = 0;

    while (fgets(line, 128, p)) {
        char f = 0;
        char l = 0;

        for (int i=0; i < 128-5; i++) {
            if (line[i] == '\n' || line[i] == 0) {
                break;
            }

            char ch = 0;
            if (line[i] >= '0' && line[i] <= '9') {
                ch = line[i];
            } else if (equals(line, i, "one", 3)) {
                ch = '1';
            } else if (equals(line, i, "two", 3)) {
                ch = '2';
            } else if (equals(line, i, "three", 5)) {
                ch = '3';
            } else if (equals(line, i, "four", 4)) {
                ch = '4';
            } else if (equals(line, i, "five", 4)) {
                ch = '5';
            } else if (equals(line, i, "six", 3)) {
                ch = '6';
            } else if (equals(line, i, "seven", 5)) {
                ch = '7';
            } else if (equals(line, i, "eight", 5)) {
                ch = '8';
            } else if (equals(line, i, "nine", 4)) {
                ch = '9';
            } else if (equals(line, i, "zero", 4)) {
                ch = '0';
            }

            if (ch >= '0' && ch <= '9') {
                if (!f) {
                    f = ch;
                    l = ch;
                } else {
                    l = ch;
                }
            }
        }
        sum += ((f - 48) * 10 + (l-48));
    }

    printf("Part 2 answer: %d\n", sum);

    fclose(p);
    return 0;
}