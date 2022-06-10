#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/param.h>

// 0-9 (first 10)
// A-Z (next 26)
// 36
// with 3 digits, that's 36 * 36 * 36 =
#define HT_SIZE 46656

int parse_lhs(FILE *file) {
    int acc = 0;
    while (true) {
        int c = getc(file);
        if (c == ')') {
            break;
        }
        acc *= 36;
        if (c >= '0' && c <= '9') {
            acc += c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            acc += 10;
            acc += c - 'A';
        }
    }
    return acc;
}

int parse_rhs(FILE *file) {
    int acc = 0;
    while (true) {
        int c = getc(file);
        if (c == '\n') {
            break;
        }
        acc *= 36;
        if (c >= '0' && c <= '9') {
            acc += c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            acc += 10;
            acc += c - 'A';
        }
    }
    return acc;
}

int orbit_map[HT_SIZE] = {[0 ... HT_SIZE - 1] = -1};
int orbit_counts[HT_SIZE] = {[0 ... HT_SIZE - 1] = -1};

int calc_orbits(int celestial_body_hash) {
    if (orbit_counts[celestial_body_hash] == -1) {
        return 1 + calc_orbits(orbit_map[celestial_body_hash]);
    } else {
        return orbit_counts[celestial_body_hash];
    }
}

int main() {
    // 'COM' has a count of 0
    // 16438 is COM in base 36
    orbit_counts[16438] = 0;

    FILE *file = fopen("./day6.input", "r");
    while (true) {
        char c = getc(file);
        if (c == EOF) {
            break;
        }
        ungetc(c, file);
        int left = parse_lhs(file);
        int right = parse_rhs(file);
        orbit_map[right] = left;
    }

    int acc = 0;
    for (int i = 0; i < HT_SIZE; i++) {
        if (orbit_map[i] > -1) {
            acc += calc_orbits(i);
        }
    }

    // print out max orbit
    printf("part 1: %d\n", acc);
}