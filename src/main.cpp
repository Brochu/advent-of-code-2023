#include <stdio.h>
#include "parsing.h"

#if   DAY == 1
#include "day1.h"
#elif DAY == 2
#include "day2.h"
#endif

int main(int argc, char **argv) {
    printf("[MAIN] Solutions for day %i\n", DAY);
    printf("[MAIN] Here the part_1 solution = %i\n", Solution::part_1());
    printf("[MAIN] Here the part_2 solution = %i\n", Solution::part_2());

    return 0;
}
