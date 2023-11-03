#include <iostream>
#include <stdio.h>

#if   DAY == 1
#include "day1.h"
#elif DAY == 2
#include "day2.h"
#endif
#include "parsing.h"

int main(int argc, char **argv) {
    // This is how we will read input in this project
    //printf("-----------\n");
    //std::string line = "Hello!";
    //while (std::getline(std::cin, line)) {
    //    printf("%s\n", line.c_str());
    //}
    //printf("-----------\n");

    printf("[MAIN] Solutions for day %i\n", DAY);
    printf("[MAIN] Here the part_1 solution = %s\n", Solution::part_1().c_str());
    printf("[MAIN] Here the part_2 solution = %s\n", Solution::part_2().c_str());

    return 0;
}
