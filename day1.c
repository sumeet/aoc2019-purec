#include <stdio.h>

int calc_part2(int mass) {
    int result = (mass / 3) - 2;
    if (result <= 0) {
        return 0;
    }
    return result + calc_part2(result);
}

int main(void) {
    int part1 = 0;
    int part2 = 0;

    FILE *file = fopen("./day1.input", "r");

    int this_mass = 0;
    for (char c = fgetc(file); c != EOF; c = fgetc(file)) {
        if (c == '\n') {
            part1 += (this_mass / 3) - 2;
            part2 += calc_part2(this_mass);
            this_mass = 0;
        } else {
            this_mass = (this_mass * 10) + c - '0';
        }
    }
    printf("%d\n", part1);
    printf("%d\n", part2);
}
