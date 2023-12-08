#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Network {
    char name[3];
    char left[3];
    char right[3];
} Node;

#define NODE_COUNT 750

int scmp(char* a, char* b) {
    for (int i = 0; i < 3; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

int find(Node* nodes, char name[3]) {
    for (int i=0; i < NODE_COUNT; i++) {
        Node node = nodes[i];
        if (scmp(name, node.name)) {
            return i;
        }
    }
    return -1;
}

int main() {
    Node nodes[NODE_COUNT];
    FILE* file = fopen("./input", "r");

    char directions[300];

    fgets(directions, 300, file);

    char buf[25];
    fgets(buf, 25, file); // skip newline

    int line_no = 0;
    while (fgets(buf, 25, file)) {
        sscanf(
            buf, 
            "%3s = (%3s, %3s)",
            nodes[line_no].name,
            nodes[line_no].left,
            nodes[line_no].right
        );
        line_no++;
    }

    int i = 0;
    int steps = 0;
    char current[3] = "AAA";

    while (1) {
        steps++;
        if (directions[i] == '\n') {
            i = 0;
        }

        int index = find(nodes, current);
        if (directions[i] == 'L') {
            memcpy(current, nodes[index].left, 3);
        } else {
            memcpy(current, nodes[index].right, 3);
        }

        if (scmp(current, "ZZZ")) {
            printf("there!\n");
            break;
        }

        i++;
    }

    printf("Part 1 answer: %d\n", steps);

    fclose(file);
    return 0;
}