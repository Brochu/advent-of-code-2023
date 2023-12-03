#include "day.h"
#include "parsing.h"

namespace Solution {

std::string part1() {
    return "NotCompleted";
}

std::string part2() {
    return "NotCompleted";
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(".\\inputs\\day3.txt");
    printf("%s\n", in.c_str());

    *part1_out = part1();
    *part2_out = part2();

    return 0;
}

}
