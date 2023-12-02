#include <stdio.h>

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

    printf("Sum: %d\n", sum);

    fclose(p);

    // part 1 - end

    return 0;
}