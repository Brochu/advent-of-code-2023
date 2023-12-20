#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 1
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day20_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day20.txt"
#endif // ------------------------------------

usize part1() {
    usize lo_count = 0;
    usize hi_count = 0;

    return lo_count * hi_count;
}

std::string part2() {
    return "NotCompleted";
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    Parse::enum_str(std::move(in), "\n", [](char *token){
        char *left = nullptr;
        char *right = nullptr;
        Parse::split_once(token, " -> ", &left, &right);

        printf("left='%s'; right='%s'\n", left, right);
    });

    *part1_out = std::to_string(part1());
    *part2_out = part2();

    return 0;
}

}
