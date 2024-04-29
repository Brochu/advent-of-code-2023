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

void debug(Record &rec) {
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
char *state_name(State s) {
    switch (s) {
        case Error: return (char*)"Error";
        case Start: return (char*)"Start";
        case Out: return (char*)"Out";
        case In: return (char*)"In";
        case End: return (char*)"End";
    }
    return (char*)"n/a";
}

struct Exec {
    State state;
    std::vector<u8> stack;
};
void print_exec(Exec &e) {
    if (e.stack.empty()) {
        printf("[EXEC] State = %s, empty stack\n", state_name(e.state));
    }
    else {
        printf("[EXEC] State = %s, top of stack = %i\n", state_name(e.state), e.stack.back());
    }
}

void exec_step(Exec &e, char in) {
    //printf("[STEP] START (with input = %c)\n", in);
    //print_exec(e);

    // Endings
    if (in == '\0' && (e.stack.empty() || e.stack.back() == 0)) {
        e.state = State::End;
        return;
    }
    else if (in == '\0' && !e.stack.empty()) {
        e.state = State::Error;
        return;
    }

    // Progress
    if (in == '.') {
        if (!e.stack.empty() && e.stack.back() == 0) {
            e.stack.pop_back();
        }
        e.state = State::Out;
    }
    else if (in == '#') {
        if (e.stack.empty() || e.stack.back() == 0) {
            e.state = State::Error;
            return;
        }
        else if (!e.stack.empty()) {
            e.stack.back()--;
        }
        e.state = State::In;
    }

    //print_exec(e);
    //printf("[STEP] END (with input = %c)\n", in);
}

u64 calc_arrangements(Record &rec) {
    debug(rec);

    Exec e { State::Start, rec.nums };
    char *next = rec.sp;
    while(e.state != State::End && e.state != State::Error) {
        exec_step(e, *next);
        next++;
    }

    printf("[ARRANGEMENTS] Finished with state: %s\n", state_name(e.state));
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
    std::string in = "#.#.### 1,1,3\n"
                    ".#...#....###. 1,1,3\n"
                    ".#.###.#.###### 1,3,1,6\n"
                    "####.#...#... 4,1,1\n"
                    "#....######..#####. 1,6,5\n"
                    ".###.##....# 3,2,1";
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
