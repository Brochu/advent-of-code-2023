#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

//#define FILE_PATH ".\\inputs\\day6_demo1.txt"
//#define RACE_COUNT 3
//#define RACE_FORMAT "%i %i %i"
//#define RACE_EXPAND(a) &a[0], &a[1], &a[2]
#define FILE_PATH ".\\inputs\\day6.txt"
#define RACE_COUNT 4
#define RACE_FORMAT "%i %i %i %i"
#define RACE_EXPAND(a) &a[0], &a[1], &a[2], &a[3]

struct Race {
    int time;
    int dist;
};
void debug_race(std::span<Race> races) {
    for (Race &r : races) {
        printf("[RACE] t = %i; d = %i\n", r.time, r.dist);
    }
}

std::string part1(std::span<Race> races) {
    int margin = 1;

    for (Race &r : races) {
        int count = 0;
        for (int i = 1; i < r.time; i++) {
            int val = i * (r.time - i);
            if (val > r.dist) { count++; }

            //debug_race({&r ,1});
            //printf("start %i, speed = %i, remain = %i, max = %i\n", i, i, (r.time - i), val);
        }
        margin *= count;
        //printf("count = %i, margin = %i\n--------------\n", count, margin);
    }

    return std::to_string(margin);
}

std::string part2() {
    return "NotCompleted";
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<char*> lines = Parse::split_str(std::move(in), "\n");

    int times[RACE_COUNT];
    sscanf_s(Parse::split_char(lines[0], ": ")[1], RACE_FORMAT, RACE_EXPAND(times));
    int distances[RACE_COUNT];
    sscanf_s(Parse::split_char(lines[1], ": ")[1], RACE_FORMAT, RACE_EXPAND(distances));

    Race data[RACE_COUNT];
    for (int i = 0; i < RACE_COUNT; i++) {
        data[i].time = times[i];
        data[i].dist = distances[i];
    }

    *part1_out = part1(data);
    *part2_out = part2();

    return 0;
}

}
