#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 1
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day23_demo1.txt"
#define MAP_SIZE 23
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day23.txt"
#define MAP_SIZE 141
#endif // ------------------------------------

usize part1() {
    return 0;
}

usize part2() {
    return 0;
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    printf("%s", in.c_str());

    *part1_out = std::to_string(part1());
    *part2_out = std::to_string(part2());

    return 0;
}

}
