#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 1
#if DEMO == 1
#define FILE_PATH ".\\inputs\\day6_demo1.txt"
#define RACE_COUNT 3
#define RACE_FORMAT "%lld %lld %lld"
#define RACE_EXPAND(a) &a[0], &a[1], &a[2]
#else
#define FILE_PATH ".\\inputs\\day6.txt"
#define RACE_COUNT 4
#define RACE_FORMAT "%lld %lld %lld %lld"
#define RACE_EXPAND(a) &a[0], &a[1], &a[2], &a[3]
#endif

struct Race {
    u64 time;
    u64 dist;
};
void debug_race(std::span<Race> races) {
    for (Race &r : races) {
        printf("[RACE] t = %lld; d = %lld\n", r.time, r.dist);
    }
}

std::string part1(std::span<Race> races) {
    u64 margin = 1;

    for (Race &r : races) {
        u64 count = 0;
        u64 prev = 0;
        for (u64 i = 1; i < r.time; i++) {
            //TODO: Optim, search bounds
            u64 val = i * (r.time - i);
            if (val > r.dist) { count++; }

            if (val < prev && val <= r.dist) {
                break;
            }
            prev = val;
            //debug_race({&r ,1});
            //printf("start %i, speed = %i, remain = %i, max = %i\n", i, i, (r.time - i), val);
        }
        margin *= count;
        //printf("count = %i, margin = %i\n--------------\n", count, margin);
    }

    return std::to_string(margin);
}

std::string part2(Race race) {
    debug_race({&race,1});
    return "NotCompleted";
}

Race combine_races(std::span<Race> races) {
    return { 0, 0 };
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<char*> lines = Parse::split_str(std::move(in), "\n");

    u64 times[RACE_COUNT];
    sscanf_s(Parse::split_char(lines[0], ": ")[1], RACE_FORMAT, RACE_EXPAND(times));
    u64 distances[RACE_COUNT];
    sscanf_s(Parse::split_char(lines[1], ": ")[1], RACE_FORMAT, RACE_EXPAND(distances));

    Race data[RACE_COUNT];
    for (int i = 0; i < RACE_COUNT; i++) {
        data[i].time = times[i];
        data[i].dist = distances[i];
    }

    *part1_out = part1(data);
    *part2_out = part2(combine_races(data));

    return 0;
}

}
