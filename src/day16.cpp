#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 1
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day16_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day16.txt"
#endif // ------------------------------------

enum Cell { EMPTY, BTMIRROR, TBMIRROR, VSPLIT, HSPLIT };

std::string part1() {
    usize energized = 0;
    return std::to_string(energized);
}

std::string part2() {
    usize energized = 0;
    return std::to_string(energized);
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    printf("%s\n", in.c_str());

    *part1_out = part1();
    *part2_out = part2();

    return 0;
}

}
