#include "day.h"
#include "parsing.h"

namespace Solution {

#define DEMO 0
#if DEMO == 0 // ------------------------------------
#define FILE_PATH ".\\inputs\\day0_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day0.txt"
#endif // ------------------------------------

std::string part1() {
    return "NotCompleted";
}

std::string part2() {
    return "NotCompleted";
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    printf("%s", in.c_str());

    *part1_out = part1();
    *part2_out = part2();

    return 0;
}

}
