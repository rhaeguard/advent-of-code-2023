#include <stdio.h>
#include <stdlib.h>

#define SIZE 140
#define COUNT_GALAXY 451

typedef struct Galaxy {
    int row;
    int col;
    int depth;
} Galaxy;

char decide_directions2(Galaxy* from, Galaxy* to) {
    // int xdiff = to->col - from->col;
    // int ydiff = to->row - from->row;
    // int dist = xdiff*xdiff + ydiff*ydiff;

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


int bfs2(Galaxy* from, Galaxy* to, int expanded_rows[SIZE], int expanded_cols[SIZE]) {
    int depth = 0;
    Galaxy* current = malloc(sizeof(Galaxy));
    current->row = from->row;
    current->col = from->col;
    current->depth = 0;
    int seen_rows[SIZE] = {0}; 
    int seen_cols[SIZE] = {0};
    while(1) {
        if (current->row == to->row && current->col == to->col) {
            depth = current->depth;
            break;
        }

        int new_depth = current->depth + 1;

        char d = decide_directions2(current, to);
        int r = current->row;
        int c = current->col;
        
        if (d == 'l') {
            c--;
            
            if (!seen_cols[c] && expanded_cols[c]) {
                seen_cols[c] = 1;
                new_depth++; 
            }    
        } else if (d == 'r') {
            c++;

            if (!seen_cols[c] && expanded_cols[c]) {
                seen_cols[c] = 1;
                new_depth++; 
            }
        } else {
            // d
            r++;

            if (!seen_rows[r] && expanded_rows[r]) {
                seen_rows[r] = 1;
                new_depth++; 
            }
        }

        // printf("dir: %c\t%d %d\n", d, r, c);

        // if you're in a expanded column and move L/R to another column +1
        // if you're in an expanded row and move down to another row +1

        // if ((!seen_rows[r] && expanded_rows[r]) || (!seen_cols[c] && expanded_cols[c])) {
        //     if (expanded_rows[r]) {
        //         seen_rows[c] = 1;
        //     }

        //     if (expanded_cols[c]) {
        //         seen_cols[c] = 1;
        //     }
        //     new_depth++;
        // }
        current = realloc(current, sizeof(Galaxy));
        current->row = r;
        current->col = c;
        current->depth = new_depth;
    }

    // printf("\n(%d %d) + (%d %d): %d\n", from->row, from->col, to->row, to->col, depth);

    return depth;
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
    int c = 0;
    int sum = 0;
    for (int i = 0; i < COUNT_GALAXY; i++) {
        Galaxy from = galaxies[i];

        for (int j=i+1; j < COUNT_GALAXY; j++) {
            Galaxy to = galaxies[j];
            sum += bfs2(&from, &to, expanded_rows, expanded_cols);
        }
        // break;
    }

    printf("Part 1 answer: %d\n", sum);

    fclose(file);
    return 0;
}