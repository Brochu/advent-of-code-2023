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

enum State {
    Error = -1,
    Start,
    Ok,
    Broken,
    End,
};

struct Exec {
    State state;
    std::vector<u8> stack;

    u64 hash;
};

void debug(std::span<Record> recs) {
    for (Record r : recs) {
        printf("Record -> '%s'\n", r.sp);
        printf("\t");
        for (u8 n : r.nums) {
            printf(" %i,", n);
        }
        printf("\n");
    }
}

size_t part1(std::span<Record> records) {
    size_t result = 0;
    debug(records);
    return result;
}

i32 run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<Record> records;
    Parse::enum_str(std::move(in), "\n", [&records](char *token){
        char *springs = nullptr;
        char *vals = nullptr;
        Parse::split_once(token, " ", &springs, &vals);

        std::vector<u8> nums;
        Parse::enum_char(vals, ",", [&nums](char *token) {
            nums.emplace_back(atoi(token));
        });
        records.emplace_back(springs, nums);
    });

    *part1_out = std::to_string(part1({ records.begin() + 1, records.begin() + 2 }));
    //*part2_out = std::to_string(part2());

    return 0;
}

}
