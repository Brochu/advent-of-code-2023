#include "day.h"
#include "parsing.h"

namespace Solution {

#define DEMO_FILE ".\\inputs\\day5_demo1.txt"
#define DEMO_SEED_COUNT 4
#define PUZZLE_FILE ".\\inputs\\day5.txt"
#define PUZZLE_SEED_COUNT 20

struct MapRange {
};
struct FilterStep {
};

std::string part1() {
    return "NotCompleted";
}

std::string part2() {
    return "NotCompleted";
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(DEMO_FILE);
    std::vector<char*> sections = Parse::split_str(std::move(in), "\n\n");

    for (char *section : sections) {
        printf("[SECTION] %s\n", section);
    }

    *part1_out = part1();
    *part2_out = part2();

    return 0;
}

}
