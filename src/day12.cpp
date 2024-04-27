#include "day.h"
#include "parsing.h"

#include <string>

namespace Solution {

#define DEMO 1
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day12_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day12.txt"
#endif // ------------------------------------

size_t part1()
{
    size_t result = 0;
    return result;
}


size_t part2()
{
    size_t result = 0;
    return result;
}

i32 run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<char *> lines = Parse::split_str(std::move(in), "\n");

    for (int i = 0; i < lines.size(); i++) {
        printf(" * '%s'\n", lines[i]);
    }
    *part1_out = std::to_string(part1());
    *part2_out = std::to_string(part2());

    return 0;
}

}
