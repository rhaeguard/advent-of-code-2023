#include <stdio.h>
#include <stdlib.h>

#define SIZE 140

int is_in(char c, char* haystack, int len) {
    for (int i = 0; i < len; i++) {
        if (c == haystack[i]) {
            return 1;
        }
    }
    return 0;
}

char get_ch(char input[SIZE][SIZE], int r, int c) {
    if (r >= 0 && r < SIZE && c >= 0 && c < SIZE) {
        return input[r][c];
    }
    return 'X';
}

void get_neighbors(char input[SIZE][SIZE], int* or, int* oc, int seen[SIZE][SIZE], int r, int c) {
    /**
     * 
    | is a vertical pipe connecting north and south.
    - is a horizontal pipe connecting east and west.
    L is a 90-degree bend connecting north and east.
    J is a 90-degree bend connecting north and west.
    7 is a 90-degree bend connecting south and west.
    F is a 90-degree bend connecting south and east.
    . is ground; there is no pipe in this tile.
    */

    int neighbors[4] = {-1, -1, -1, -1};

    char me = get_ch(input, r, c);
    if (me == '|') {
        // north
        char n = get_ch(input, r-1, c);
        if (is_in(n, "|7F", 3)) {
            neighbors[0] = r-1;
            neighbors[1] = c;
        }
        // south
        char s = get_ch(input, r+1, c);
        if (is_in(s, "|LJ", 3)) {
            neighbors[2] = r+1;
            neighbors[3] = c;
        }
    } else if (me == '-') {
        // west
        char n = get_ch(input, r, c-1);
        if (is_in(n, "-LF", 3)) {
            neighbors[0] = r;
            neighbors[1] = c-1;
        }
        // east
        char s = get_ch(input, r, c+1);
        if (is_in(s, "-J7", 3)) {
            neighbors[2] = r;
            neighbors[3] = c+1;
        }
    } else if (me == 'L') {
        // east
        char n = get_ch(input, r, c+1);
        if (is_in(n, "-J7", 3)) {
            neighbors[0] = r;
            neighbors[1] = c+1;
        }
        // north
        char x = get_ch(input, r-1, c);
        if (is_in(x, "|7F", 3)) {
            neighbors[2] = r-1;
            neighbors[3] = c;
        }
    } else if (me == 'J') {
        // north
        char n = get_ch(input, r-1, c);
        if (is_in(n, "|7F", 3)) {
            neighbors[0] = r-1;
            neighbors[1] = c;
        }
        // west
        char x = get_ch(input, r, c-1);
        if (is_in(x, "-LF", 3)) {
            neighbors[2] = r;
            neighbors[3] = c-1;
        }  
    } else if (me == '7') {
        // west
        char n = get_ch(input, r, c-1);
        if (is_in(n, "-LF", 3)) {
            neighbors[0] = r;
            neighbors[1] = c-1;
        } 
        // south
        char s = get_ch(input, r+1, c);
        if (is_in(s, "|LJ", 3)) {
            neighbors[2] = r+1;
            neighbors[3] = c;
        }
    } else if (me == 'F') {
        // east
        char n = get_ch(input, r, c+1);
        if (is_in(n, "-J7", 3)) {
            neighbors[0] = r;
            neighbors[1] = c+1;
        }
        // south
        char s = get_ch(input, r+1, c);
        if (is_in(s, "|LJ", 3)) {
            neighbors[2] = r+1;
            neighbors[3] = c;
        }
    }

    int y = neighbors[0];
    int x = neighbors[1];

    if ((y!=-1 && x!=-1) && !seen[y][x]) {
        *or = y;
        *oc = x;
        return;
    }

    y = neighbors[2];
    x = neighbors[3];

    if ((y!=-1 && x!=-1) && !seen[y][x]) {
        *or = y;
        *oc = x;
    }

}

void bfs(char input[SIZE][SIZE], int r, int c) {
    int seen[SIZE][SIZE] = {{0}};

    seen[r][c] = 1;

    int neighbors[4] = {
        r, c-1, r+1, c // neighbors of the start point
    };

    int depth = 1;

    for (;;) {
        if (neighbors[0] == neighbors[2] && neighbors[1] == neighbors[3]) {
            r = neighbors[0];
            c = neighbors[1];

            seen[r][c] = 1;
            break;
        }

        int or = -1;
        int oc = -1;

        r = neighbors[0];
        c = neighbors[1];

        seen[r][c] = 1;
        get_neighbors(input, &or, &oc, seen, r, c);
        neighbors[0] = or;
        neighbors[1] = oc;


        or = -1;
        oc = -1;

        r = neighbors[2];
        c = neighbors[3];
        
        seen[r][c] = 1;
        get_neighbors(input, &or, &oc, seen, r, c);
        neighbors[2] = or;
        neighbors[3] = oc;

        depth++;
    }

    printf("Part 1 answer: %d\n", depth);

    int tiles = 0;

    // https://en.wikipedia.org/wiki/Point_in_polygon
    // ray casting algorithm
    for (int row=0; row < SIZE; row++) {
        for (int col=0; col < SIZE; col++) {
            if (!seen[row][col]) {
                int count = 0;
                for (int s=col; s < SIZE; s++) {
                    if (seen[row][s] && is_in(input[row][s], "|JL", 3)) {
                        count++;
                    }
                }
                if (count % 2 == 1) {
                    tiles++;
                }
            }
        }
    }

    printf("Part 2 answer: %d\n", tiles);
}

int main() {
    char input[SIZE][SIZE] = {{0}};

    FILE* file = fopen("./input", "r");
    
    char buf[250];
    int ln = 0;
    int r, c = 0;
    while (fgets(buf, 250, file)) {
        for (int i=0; i<SIZE; i++) {
            if (buf[i] == 'S') {
                r = ln;
                c = i;
            }
            input[ln][i] = buf[i];
        }
        ln++;
    }

    bfs(&input, r, c);

    fclose(file);
    return 0;
}