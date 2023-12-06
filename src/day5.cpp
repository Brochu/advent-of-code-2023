#include "day.h"
#include "parsing.h"

#include <algorithm>
#include <span>

namespace Solution {

#define FILE_PATH ".\\inputs\\day5_demo1.txt"
#define SEED_COUNT 4
//#define FILE_PATH ".\\inputs\\day5.txt"
//#define SEED_COUNT 20

#define FILTERS_COUNT 7

struct SeedRange {
    u64 start;
    usize size;
};

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
    u64 min_loc = LONG_MAX;

    for (u64 seed : seeds) {
        u64 current = seed;
        for (FilterStep filter : filters) {
            u64 newSeed = apply_filter(filter, current);
            current = newSeed;
        }

        if (current < min_loc) {
            min_loc = current;
        }
    }
    return std::to_string(min_loc);
}

SeedRange apply_filter_range(SeedRange &sr, FilterStep &filter, std::vector<SeedRange> &stack) {
    //TODO: Find first complete or partial match
    // return SeedRange to consider done
    // For ranges that still need to be considered, push onto stack
    return {};
}

std::string part2(std::span<SeedRange> seeds, std::span<FilterStep> filters) {
    std::vector<SeedRange> stack;
    for (SeedRange &sr : seeds) {
        stack.push_back(sr);
    }

    FilterStep &filter = filters[0]; {
    //for (FilterStep &filter : filters) {
        std::vector<SeedRange> done;
        while (stack.size() > 0) {
            SeedRange &sr = stack.back();
            stack.pop_back();

            done.push_back(apply_filter_range(sr, filter, stack));
        }

        //TODO: Something with done, probably use it as next stack for next filter?
    }
    return "Incomplete";
}

std::vector<u64> parse_seeds_p1(std::span<char*> seed_nums) {
    std::vector<u64> seeds;

    for (int i = 0; i < SEED_COUNT; i++) {
        seeds.push_back(std::stoull(seed_nums[i]));
    }

    return seeds;
}

std::vector<SeedRange> parse_seeds_p2(std::span<char*> seed_nums) {
    std::vector<SeedRange> seeds;
    for (int i = 0; i < seed_nums.size(); i += 2) {
        seeds.push_back({ std::stoull(seed_nums[i]), std::stoull(seed_nums[i + 1]) });
    }
    return seeds;
}

void parse_filter(FilterStep &filter, char *filterString) {
    std::vector<char*> rangesEntries = Parse::split_char(Parse::split_char(filterString, ":\n")[1], "\n");

    for (char *range : rangesEntries) {
        MapRange map { 0 };
        sscanf_s(range, "%lld %lld %lld", &map.dest, &map.src, &map.size);

        filter.ranges.push_back(map);
    }

    std::sort(filter.ranges.begin(), filter.ranges.end(), [](MapRange &left, MapRange &right){
        return left.src < right.src;
    });
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<char*> sections = Parse::split_str(std::move(in), "\n\n");

    FilterStep filters[FILTERS_COUNT];
    for (int i = 1; i < sections.size(); i++) {
        parse_filter(filters[i-1], sections[i]);
    }

    std::vector<char*> seed_nums = Parse::split_char(Parse::split_char(sections[0], ": ")[1], " ");
    std::vector<u64> p1_seeds = parse_seeds_p1(seed_nums);
    std::vector<SeedRange> p2_seeds = parse_seeds_p2(seed_nums);

    *part1_out = part1(p1_seeds, filters);
    *part2_out = part2(p2_seeds, filters);

    return 0;
}

}
