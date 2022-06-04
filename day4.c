#include <stdio.h>
#include <stdbool.h>

bool contains_adjacents_part1(int num) {
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

bool contains_adjacents_part2(int num) {
    int num_repetitions = 1;
    int prev = num % 10;
    num /= 10;
    while (num > 0) {
        int cur = num % 10;
        if (cur == prev) {
            num_repetitions += 1;
        } else {
            if (num_repetitions == 2) {
                return true;
            }
            num_repetitions = 1;
        }
        prev = cur;
        num /= 10;
    }
    return num_repetitions == 2;
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
    int valid_passwords_count_part1 = 0;
    int valid_passwords_count_part2 = 0;
    for (int password = 145852; password <= 616942; password++) {
        if (contains_adjacents_part1(password) && never_decreases(password)) {
            valid_passwords_count_part1++;
        }
        if (contains_adjacents_part2(password) && never_decreases(password)) {
            valid_passwords_count_part2++;
        }
    }
    printf("part 1: %d\n", valid_passwords_count_part1);
    printf("part 2: %d\n", valid_passwords_count_part2);
}
