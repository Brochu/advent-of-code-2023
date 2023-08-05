#include <stdio.h>

#include "parsing.h"
#include "day1.h"

int main(int argc, char **argv) {
    printf("[MAIN] Solutions for day ...\n");

    int val = Parse::tests();
    printf("[MAIN] Here's a value = %i\n", val);

    int solved = Solution::part_1();
    printf("[MAIN] Here the part_1 solution = %i\n", solved);

    return 0;
}
