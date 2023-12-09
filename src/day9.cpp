#include "day.h"
#include "parsing.h"

#include <span>
#include <wchar.h>

namespace Solution {

#define DEMO 0
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day9_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day9.txt"
#endif // ------------------------------------

struct series {
    std::vector<i64> nums;
    std::vector<std::vector<i64>> steps;
};
void debug_series(std::span<series> cs) {
    for (series &c : cs) {
        printf("[NUMS]: ");
        for (i64 n : c.nums) {
            printf("%lld,", n);
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

std::string part1(std::span<series> data) {
    i64 total = 0;
    for (series &c : data) {
        i64 diff = 0;
        for (int i = c.steps.size() - 2; i >= 0; i--) {
            auto val = c.steps[i].back();
            //printf("%lld : %lld\n", diff, val);
            diff = val + diff;
        }
        total += diff + c.nums.back();
        //printf("%lld\n", diff + c.nums.back());
    }
    return std::to_string(total);
}

std::string part2(std::span<series> data) {
    i64 total = 0;
    for (series &c : data) {
        i64 diff = 0;
        for (int i = c.steps.size() - 2; i >= 0; i--) {
            auto val = c.steps[i].front();
            printf("%lld - %lld = %lld\n", val, diff, val - diff);
            diff = val - diff;
        }
        i64 res = c.nums.front() - diff;
        printf("res = %lld\n", res);
        total += res;
    }
    return std::to_string(total);
}

bool is_end(std::vector<i64> *vals) {
    if (vals == nullptr) return true;
    for (i64 i : *vals) {
        if (i != 0) return false;
    }
    return true;
}

void populate_steps(series &c) {
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
    std::vector<series> data;

    for (char *line : values) { 
        series c;
        std::vector<char*> changes = Parse::split_char(line, " ");
        for (char *change : changes) {
            c.nums.push_back(std::stoll(change));
        }
        populate_steps(c);
        data.push_back(c);
    }
    //debug_series(data);

    *part1_out = part1(data);
    *part2_out = part2(data);

    return 0;
}

}
