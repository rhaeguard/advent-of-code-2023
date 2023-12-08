#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Network {
    char name[3];
    char left[3];
    char right[3];
    int active;
} Node;

#define NODE_COUNT 750
#define TABLE_CAPACITY 30000

static inline long gcd(long a, long b) { 
    return b == 0 ? a : gcd(b, a % b); 
} 
  
static inline long lcm(long a, long b) { 
    return (a*b / gcd(a, b)); 
} 

unsigned int hash(char arr[3]) {
    unsigned int hash = 0;
    hash = 31*hash + arr[0];
    hash = 31*hash + arr[1];
    hash = 31*hash + arr[2];
    return hash % TABLE_CAPACITY;
}

static inline int scmp(char* a, char* b) {
    return a[0] == b[0] && a[1] == b[1] && a[2] == b[2];
}

Node* find_in_lookup(Node** lookup, char name[3]) {
    int ix = hash(name);
    return lookup[ix];
}

int main() {
    Node* lookup[TABLE_CAPACITY];
    Node* nodes[NODE_COUNT];
    FILE* file = fopen("./input", "r");

    char directions[300];

    fgets(directions, 300, file);

    char buf[25];
    fgets(buf, 25, file); // skip newline

    int line_no = 0;
    while (fgets(buf, 25, file)) {
        Node* node = malloc(sizeof(Node));
        sscanf(
            buf, 
            "%3s = (%3s, %3s)",
            node->name,
            node->left,
            node->right
        );
        node->active = 0; // false by default

        int ix = hash(node->name);
        if (lookup[ix] == NULL) {
            lookup[ix] = node;
        } else {
            printf("COLLISION!!!\n");
        }
        nodes[line_no] = node;
        line_no++;
    }

    int dir = 0;
    int steps = 0;
    Node* current = find_in_lookup(lookup, "AAA");

    while (1) {
        steps++;
        if (directions[dir] == '\n') {
            dir = 0;
        }

        if (directions[dir] == 'L') {
            current = find_in_lookup(lookup, current->left);
        } else {
            current = find_in_lookup(lookup, current->right);
        }

        if (scmp(current->name, "ZZZ")) {
            break;
        }

        dir++;
    }

    printf("Part 1 answer: %d\n", steps);

    long answer2 = 1;

    for (int j = 0; j < TABLE_CAPACITY; j++) {
        Node* start = nodes[j];
        if (start->name[2] == 'A') {
            
            long steps = 0; // reset the steps counter
            dir = 0; // reset directions index

            while (1) {
                steps++;
                if (directions[dir] == '\n') {
                    dir = 0;
                }

                char* name = directions[dir] == 'L' ? start->left : start->right;
                start = find_in_lookup(lookup, name);

                if (start->name[2] == 'Z') {
                    answer2 = lcm(answer2, steps);
                    break;
                }

                dir++;
            }
        }
    }

    printf("Part 2 answer: %ld\n", answer2);
    
    fclose(file);
    return 0;
}