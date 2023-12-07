#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 0
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
        u64 start = 1;
        u64 val = start * (r.time - start);

        while (val <= r.dist) {
            start++;
            val = start * (r.time - start);
        }

        u64 end = r.time;
        val = end * (r.time - end);
        while (val <= r.dist) {
            end--;
            val = end * (r.time - end);
        }

        margin *= (end - start) + 1;
    }

    return std::to_string(margin);
}

std::string part2(Race race) {
    return part1({&race,1});
}

Race combine_races(std::span<Race> races) {
    std::string timeStr = "";
    std::string distStr = "";
    for (Race &r : races) {
        timeStr.append(std::to_string(r.time));
        distStr.append(std::to_string(r.dist));
    }
    return { std::stoull(timeStr), std::stoull(distStr) };
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
