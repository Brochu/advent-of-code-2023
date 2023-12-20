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
    usize lo_count = 1; // Starts at 1 to consider button press
    usize hi_count = 0;

    return lo_count * hi_count;
}

std::string part2() {
    return "NotCompleted";
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    *part1_out = std::to_string(part1());
    *part2_out = part2();

    return 0;
}

}
