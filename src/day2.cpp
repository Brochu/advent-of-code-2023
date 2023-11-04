#include "day.h"

#include <iostream>

namespace Solution {

int run(std::string *part1_out, std::string *part2_out) {
    std::string line;
    while (std::getline(std::cin, line)) {
        printf("%s\n", line.c_str());
    }

    *part1_out = "0";
    *part2_out = "0";

    return 1;
}

}
