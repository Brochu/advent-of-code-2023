#include "day.h"
#include "parsing.h"

#include <span>
#include <wchar.h>

namespace Solution {

#define DEMO 1
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day9_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day9.txt"
#endif // ------------------------------------

struct Cochonnerie {
    std::vector<i64> nums;
    std::vector<std::vector<i64>> steps;
};
void debug_cochonnerie(std::span<Cochonnerie> cs) {
    for (Cochonnerie &c : cs) {
        printf("[NUMS]: ");
        for (i64 n : c.nums) {
            printf("'%lld' ", n);
        }
        printf("\n");

        for (std::vector<i64> step : c.steps) {
            printf("[STEP]: ");
            for (i64 n : step) {
                printf("%lld ", n);
            }
            printf("\n");
        }
    }
}

std::string part1() {
    return "NotCompleted";
}

std::string part2() {
    return "NotCompleted";
}

bool is_end(std::vector<i64> *vals) {
    if (vals == nullptr) return true;
    for (i64 i : *vals) {
        if (i != 0) return false;
    }
    return true;
}

void populate_steps(Cochonnerie &c) {
    std::vector<i64> *current = &c.nums;

    while (!is_end(current)) {
        std::vector<i64> next;

        for (int i = 1; i < current->size(); i++) {
            next.push_back((*current)[i] - (*current)[i - 1]);
        }

        c.steps.push_back(next);
        current = &c.steps[c.steps.size() - 1];
    }
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<char*> values = Parse::split_str(std::move(in), "\n");
    std::vector<Cochonnerie> data;

    for (char *line : values) { 
        Cochonnerie c;
        std::vector<char*> changes = Parse::split_char(line, " ");
        for (char *change : changes) {
            c.nums.push_back(std::stoll(change));
        }
        populate_steps(c);
        data.push_back(c);
    }
    debug_cochonnerie(data);

    *part1_out = part1();
    *part2_out = part2();

    return 0;
}

}
