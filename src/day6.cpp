#include "day.h"
#include "parsing.h"

namespace Solution {

#define FILE_PATH ".\\inputs\\day6_demo1.txt"
//#define FILE_PATH ".\\inputs\\day6.txt"

std::string part1() {
    return "NotCompleted";
}

std::string part2() {
    return "NotCompleted";
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    printf("%s\n", in.c_str());

    *part1_out = part1();
    *part2_out = part2();

    return 0;
}

}