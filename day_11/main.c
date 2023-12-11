#include <stdio.h>
#include <stdlib.h>

#define SIZE 140
#define COUNT_GALAXY 451

typedef struct Galaxy {
    int row;
    int col;
    long p1_depth;
    long p2_depth;
} Galaxy;

char decide_directions(Galaxy* from, Galaxy* to) {
    int rr = from->row;
    int cc = from->col;

    int min = -1;
    char dir = '0';

    // left
    cc = from->col - 1;
    if (rr >= 0 && rr < SIZE && cc >= 0 && cc < SIZE) {
        int xdiff = to->col - cc;
        int ydiff = to->row - rr;
        int dist = xdiff*xdiff + ydiff*ydiff;
        min = dist;
        dir = 'l';
    }

    // right
    cc = from->col + 1;
    if (rr >= 0 && rr < SIZE && cc >= 0 && cc < SIZE) {
        int xdiff = to->col - cc;
        int ydiff = to->row - rr;
        int dist = xdiff*xdiff + ydiff*ydiff;
        if (dist < min || min == -1) {
            min = dist;
            dir = 'r';
        }
    }

    // down
    rr = from->row+1;
    cc = from->col;
    if (rr >= 0 && rr < SIZE && cc >= 0 && cc < SIZE) {
        int xdiff = to->col - cc;
        int ydiff = to->row - rr;
        int dist = xdiff*xdiff + ydiff*ydiff;   
        if (dist < min || min == -1) {
            min = dist;
            dir = 'd';
        }
    }

    return dir;
}


Galaxy* distance(Galaxy* from, Galaxy* to, int expanded_rows[SIZE], int expanded_cols[SIZE]) {
    Galaxy* current = malloc(sizeof(Galaxy));
    current->row = from->row;
    current->col = from->col;
    current->p1_depth = 0;
    current->p2_depth = 0;
    int seen_rows[SIZE] = {0}; 
    int seen_cols[SIZE] = {0};
    while(1) {
        if (current->row == to->row && current->col == to->col) {
            return current;
        }

        long new_p1_depth = current->p1_depth + 1;
        long new_p2_depth = current->p2_depth + 1;

        char d = decide_directions(current, to);
        int r = current->row;
        int c = current->col;
        
        if (d == 'l') {
            c--;
            
            if (!seen_cols[c] && expanded_cols[c]) {
                seen_cols[c] = 1;
                new_p1_depth += 1;
                new_p2_depth += 999999;
            }    
        } else if (d == 'r') {
            c++;

            if (!seen_cols[c] && expanded_cols[c]) {
                seen_cols[c] = 1;
                new_p1_depth += 1;
                new_p2_depth += 999999;
            }
        } else {
            // d
            r++;

            if (!seen_rows[r] && expanded_rows[r]) {
                seen_rows[r] = 1;
                new_p1_depth += 1;
                new_p2_depth += 999999;
            }
        }

        current->row = r;
        current->col = c;
        current->p1_depth = new_p1_depth;
        current->p2_depth = new_p2_depth;
    }

    return NULL;
}

int main() {
    int space[SIZE][SIZE] = {{0}};
    Galaxy galaxies[COUNT_GALAXY];
    int expanded_rows[SIZE] = {0};
    int expanded_cols[SIZE] = {0};

    FILE* file = fopen("./input", "r");
    
    char buf[510];
    int ln = 0;
    int galaxy_counter = 0;
    while (fgets(buf, 510, file)) {
        for (int i=0; i < SIZE; i++) {
            if (buf[i] == '#') {
                space[ln][i] = 1;
                galaxies[galaxy_counter++] = (struct Galaxy) {
                    .row=ln,
                    .col=i
                };
            }
        }
        ln++;
    }

    for (int i=0; i < SIZE; i++) {
        expanded_rows[i] = 1;
        for (int j=0; j < SIZE; j++) {
            if (space[i][j]) {
                expanded_rows[i] = 0;
                break;
            }
        }
    }

    for (int i=0; i < SIZE; i++) {
        expanded_cols[i] = 1;
        for (int j=0; j < SIZE; j++) {
            if (space[j][i]) {
                expanded_cols[i] = 0;
                break;
            }
        }
    }

    long sum_p1 = 0;
    long sum_p2 = 0;
    for (int i = 0; i < COUNT_GALAXY; i++) {
        Galaxy from = galaxies[i];

        for (int j=i+1; j < COUNT_GALAXY; j++) {
            Galaxy to = galaxies[j];
            Galaxy* resp = distance(&from, &to, expanded_rows, expanded_cols);
            sum_p1 += resp->p1_depth;
            sum_p2 += resp->p2_depth;
        }
    }

    printf("Part 1 answer: %ld\n", sum_p1);
    printf("Part 2 answer: %ld\n", sum_p2);

    fclose(file);
    return 0;
}
