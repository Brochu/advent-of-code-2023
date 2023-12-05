#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO_FILE ".\\inputs\\day5_demo1.txt"
#define DEMO_SEED_COUNT 4
#define PUZZLE_FILE ".\\inputs\\day5.txt"
#define PUZZLE_SEED_COUNT 20

#define FILE_PATH DEMO_FILE
#define SEED_COUNT DEMO_SEED_COUNT
#define FILTERS_COUNT 7

struct MapRange {
    u64 dest;
    u64 src;
    usize size;
};
u64 map(MapRange &range, u64 value) {
    return range.dest + (value - range.src);
}

struct FilterStep {
    std::vector<MapRange> ranges;
};
u64 apply_filter(FilterStep &filter, u64 value) {
    for (MapRange range : filter.ranges) {
        if (value >= range.src && value < range.src + range.size) {
            return map(range, value);
        }
    }
    return value;
}

std::string part1(std::span<u64> seeds, std::span<FilterStep> filters) {
    for (u64 seed : seeds) {
        FilterStep &step = filters[0];

        u64 newSeed = apply_filter(step, seed);
        printf("%lld -> %lld\n", seed, newSeed);
    }
    return "NotCompleted";
}

std::string part2(std::span<u64> seeds, std::span<FilterStep> filters) {
    return "NotCompleted";
}

void parse_filter(FilterStep &filter, char *filterString) {
    std::vector<char*> rangesEntries = Parse::split_char(Parse::split_char(filterString, ":\n")[1], "\n");

    for (char *range : rangesEntries) {
        MapRange map { 0 };
        sscanf_s(range, "%lld %lld %lld", &map.dest, &map.src, &map.size);

        filter.ranges.push_back(map);
    }
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<char*> sections = Parse::split_str(std::move(in), "\n\n");

    u64 seeds[SEED_COUNT];
    std::vector<char*> seed_nums = Parse::split_char(Parse::split_char(sections[0], ": ")[1], " ");
    for (int i = 0; i < SEED_COUNT; i++) {
        seeds[i] = std::stoull(seed_nums[i]);
    }

    FilterStep filters[FILTERS_COUNT];
    for (int i = 1; i < sections.size(); i++) {
        parse_filter(filters[i-1], sections[i]);
    }

    *part1_out = part1(seeds, filters);
    *part2_out = part2(seeds, filters);

    return 0;
}

}
