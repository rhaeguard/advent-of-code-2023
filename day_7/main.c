#include <stdio.h>
#include <stdlib.h>

#define TOTAL_HANDS 1000

typedef struct Pairs {
    char hand[TOTAL_HANDS];
    int bid;
} Pair;

char FIVE = 'h';
char FOUR = 'g';
char FULL = 'f';
char THREE = 'e';
char TWO = 'd';
char ONE = 'c';
char HIGH = 'b';
char NONE = 'a';

char two(Pair* x) {
    int table[91] = {0};

    for (int i=0; i < 5; i++) {
        char c = x->hand[i];
        table[c] += 1;
    }

    int twos = 0;

    for (int i = 0; i < 91; i++) {
        if (table[i] == 2) {
            twos++;
        }
    }

    if (twos == 2) {
        return TWO;
    }

    if (twos == 1) {
        return ONE;
    }

    return HIGH;
}


char full(Pair* x) {
    int table[91] = {0};

    for (int i=0; i < 5; i++) {
        char c = x->hand[i];
        table[c] += 1;
    }

    int has_three = 0;

    for (int i = 0; i < 91; i++) {
        if (table[i] == 3) {
            has_three = 1;
            break;
        }
    }

    if (!has_three) {
        return two(x);
    }

    for (int i = 0; i < 91; i++) {
        if (table[i] == 2) {
            return FULL;
        }
    }

    return THREE;
}

char four(Pair* x) {
    int table[91] = {0};

    for (int i=0; i < 5; i++) {
        char c = x->hand[i];
        table[c] += 1;
    }

    for (int i = 0; i < 91; i++) {
        if (table[i] == 4) {
            return FOUR;
        }
    }

    return full(x);
}

char five(Pair* x) {
    char f = x->hand[0];
    
    for (int i=1; i < 5; i++) {
        if (x->hand[i] != f) {
            return four(x);
        }
    }
    return FIVE;
}

int get_j_count(Pair* x) {
    int c = 0;
    for (int i = 0; i < 5; i++) {
        if (x->hand[i] == 'J') {
            c++;
        }
    }
    return c;
}

char get_type(Pair* x) {
    return five(x);
}

char get_type_with_joker(Pair* x) {
    char k = get_type(x);
    if (k == FIVE) {
        return k;
    }

    int j = get_j_count(x);
    if (k == FOUR) {
        if (j != 0) { // 1 or 4 Js
            return FIVE;    
        }
        return k;
    }

    if (k == FULL) {
        if (j == 3 || j == 2) {
            return FIVE;    
        }
        if (j == 1) {
            return FOUR;    
        }
        return k;
    } else if (k == THREE) {
        if (j == 3 || j == 1) {
            return FOUR;
        }
        return k;
    }

    if (k == TWO) {
        if (j == 2) {
            return FOUR;
        }

        if (j == 1) {
            return FULL;
        }
    } else if (k == ONE && (j == 2 || j == 1)) {
        return THREE;
    } else if (j == 1) {
        return ONE;
    }
    return k;
}


int cmpfunc (const void * a, const void * b) {
    int strength[91] = {0};
    strength['A'] = 13;
    strength['K'] = 12;
    strength['Q'] = 11;
    strength['J'] = 10;
    strength['T'] = 9;
    strength['9'] = 8;
    strength['8'] = 7;
    strength['7'] = 6;
    strength['6'] = 5;
    strength['5'] = 4;
    strength['4'] = 3;
    strength['3'] = 2;
    strength['2'] = 1;
    
    Pair* x = (Pair*) a;
    Pair* y = (Pair*) b;

    char tx = get_type(x);
    char ty = get_type(y);

    int res = tx - ty;

    if (tx == ty) {
        for (int i = 0; i < 5; i++) {
            if (x->hand[i] != y->hand[i]) {
                res = strength[x->hand[i]] - strength[y->hand[i]];
                break;
            }
        }
    }

    return res;
}

int cmpfunc_with_joker (const void * a, const void * b) {
    int strength[91] = {0};
    strength['A'] = 13;
    strength['K'] = 12;
    strength['Q'] = 11;
    strength['J'] = 0;
    strength['T'] = 9;
    strength['9'] = 8;
    strength['8'] = 7;
    strength['7'] = 6;
    strength['6'] = 5;
    strength['5'] = 4;
    strength['4'] = 3;
    strength['3'] = 2;
    strength['2'] = 1;
    
    Pair* x = (Pair*) a;
    Pair* y = (Pair*) b;

    char tx = get_type_with_joker(x);
    char ty = get_type_with_joker(y);

    int res = tx - ty;

    if (tx == ty) {
        for (int i = 0; i < 5; i++) {
            if (x->hand[i] != y->hand[i]) {
                res = strength[x->hand[i]] - strength[y->hand[i]];
                break;
            }
        }
    }

    return res;
}

int main() {
    Pair all_hands[TOTAL_HANDS];

    FILE* file = fopen("./input", "r");
    
    char buf[50];
    int line_no = 0;
    while (fgets(buf, 50, file)) {
        Pair pair = {
            .hand = {0},
            .bid = 0,
        };
        for (int i=0; i < 5;i++) {
            pair.hand[i] = buf[i];
        }
        pair.bid = atoi(buf+6);
        all_hands[line_no++] = pair; 
    }

    qsort(all_hands, TOTAL_HANDS, sizeof(Pair), cmpfunc);

    long sum = 0L;
    for (int i = 0; i < TOTAL_HANDS; i++) {
        sum += (i+1) * all_hands[i].bid;
    }

    printf("Part 1 answer: %ld\n", sum);


    qsort(all_hands, TOTAL_HANDS, sizeof(Pair), cmpfunc_with_joker);

    sum = 0L;
    for (int i = 0; i < TOTAL_HANDS; i++) {
        sum += (i+1) * all_hands[i].bid;
    }

    printf("Part 2 answer: %ld\n", sum);

    fclose(file);

    return 0;
}