#include <stdio.h>

#if   DAY == 1
#include "day1.h"
#elif DAY == 2
#include "day2.h"
#endif
#include "parsing.h"

int main(int argc, char **argv) {
    printf("[MAIN] Solutions for day %i\n", DAY);
    printf("[MAIN] Here the part_1 solution = %s\n", Solution::part_1().c_str());
    printf("[MAIN] Here the part_2 solution = %s\n", Solution::part_2().c_str());

    return 0;
}
