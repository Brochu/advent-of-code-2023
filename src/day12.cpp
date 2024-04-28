#include "day.h"
#include "parsing.h"

#include <cstdlib>
#include <string>
#include <span>

namespace Solution {

#define DEMO 1
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day12_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day12.txt"
#endif // ------------------------------------

struct Record {
    char *sp;
    std::vector<u8>nums;
};

void debug(const Record &rec) {
    printf("Record -> '%s'\n", rec.sp);
    printf("\t");
    for (auto it = rec.nums.rbegin(); it != rec.nums.rend(); it++) {
        printf(" %i,", *it);
    }
    printf("\n-------------------\n");
}

enum State {
    Error = -1,
    Start,
    Out,
    In,
    End,
};

struct Exec {
    State state;
    std::vector<u8> stack;
};
void exec_step(Exec &e, char in) {
    printf("[AUTOMATE] InState = %i, stack = %i, input = %c\n", e.state, e.stack.back(), in);

    if (in == '\0') {
        e.state = State::Error;
    }

    printf("[AUTOMATE] OutState = %i, stack = %i\n", e.state, e.stack.back());
}

u64 calc_arrangements(const Record &rec) {
    debug(rec);

    Exec e { Start, rec.nums };
    char *next = rec.sp;
    while(e.state != State::End && e.state != State::Error) {
        exec_step(e, *next);
        next++;
    }

    return 1;
}

u64 part1(std::span<Record> records) {
    u64 sum = 0;
    for (Record &rec : records) {
        sum += calc_arrangements(rec);
    }
    return sum;
}

i32 run(std::string *part1_out, std::string *part2_out) {
    //std::string in = INCLUDE_STR(FILE_PATH);
    std::string in = "#.#.### 1,1,3";
    std::vector<Record> records;
    Parse::enum_str(std::move(in), "\n", [&records](char *token){
        char *springs = nullptr;
        char *vals = nullptr;
        Parse::split_once(token, " ", &springs, &vals);

        std::vector<u8> nums;
        Parse::enum_char(vals, ",", [&nums](char *token) {
            nums.emplace(nums.begin(), atoi(token));
        });
        records.emplace_back(springs, nums);
    });

    *part1_out = std::to_string(part1(records));
    *part2_out = "NotCompleted";

    return 0;
}

}
