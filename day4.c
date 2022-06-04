#include <stdio.h>
#include <stdbool.h>

const MIN = 145852;
const MAX = 616942;

bool contains_adjacents(int num) {
    int prev = num % 10;
    num /= 10;
    while (num > 0) {
        int cur = num % 10;
        if (cur == prev) {
            return true;
        }
        prev = cur;
        num /= 10;
    }
    return false;
}

bool never_decreases(int num) {
    int prev = num % 10;
    num /= 10;
    while (num > 0) {
        int cur = num % 10;
        if (prev < cur) {
            return false;
        }

        prev = num % 10;
        num /= 10;
    }
    return true;
}

int main(void) {
    int valid_passwords_count = 0;
    for (int password = MIN; password <= MAX; password++) {
        if (contains_adjacents(password) && never_decreases(password)) {
            valid_passwords_count++;
        }
    }
    printf("part 1: %d\n", valid_passwords_count);
}
