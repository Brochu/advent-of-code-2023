#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 1
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day14_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day14.txt"
#endif // ------------------------------------
//#define CYCLE_COUNT 3
#define CYCLE_COUNT 1000000000

void debug_map(std::span<std::string> lines) {
    for (std::string &s : lines) {
        printf("%s\n", s.c_str());
    }
}

usize part1(std::span<std::string> lines) {
    usize heightmap[lines[0].size()];
    for (i32 i = 0; i < lines[0].size(); i++) {
        heightmap[i] = lines.size();
    }

    usize total = 0;
    for (i32 i = 0; i < lines.size(); i++) {
        for (i32 j = 0; j < lines[i].size(); j++) {
            usize pos = lines.size() - i;

            if (lines[i][j] == 'O') {
                total += heightmap[j];
                heightmap[j]--;
            }
            else if (lines[i][j] == '#') {
                heightmap[j] = pos - 1;
            }
        }
    }
    return total;
}

std::vector<std::string> rotate(std::span<std::string> lines) {
    std::vector<std::string> res;
    for (i32 i = 0; i < lines.size(); i++) {
        std::string l;
        for (i32 j = lines[i].size() - 1; j >= 0; j--) {
            l += lines[j][i];
        }
        res.push_back(l);
    }
    return res;
}

void tilt(std::vector<std::string> &lines) {
    for (i32 i = 1; i < lines.size(); i++) {
        for (i32 j = 0; j < lines[i].size(); j++) {
            if (lines[i][j] == 'O') {
                for (i32 k = i - 1; k >= 0; k--) {
                    if (lines[k][j] == 'O' || lines[k][j] == '#') {
                        lines[i][j] = '.';
                        lines[k + 1][j] = 'O';
                        break;
                    }
                    if (k == 0) {
                        lines[i][j] = '.';
                        lines[0][j] = 'O';
                    }
                }
            }
        }
    }
}

std::string part2(std::vector<std::string> lines) {
    u64 total = 0;

    debug_map(lines);
    std::vector<std::vector<std::string>> cache;

    for (i32 i = 0; i < CYCLE_COUNT; i++) {
        tilt(lines);
        lines = rotate(lines);
        tilt(lines);
        lines = rotate(lines);
        tilt(lines);
        lines = rotate(lines);
        tilt(lines);
        lines = rotate(lines);

        auto pred = [&lines](std::vector<std::string> &in){
            for (i32 i = 0; i < in.size(); i++) {
                if (in[i] != lines[i]) return false;
            }
            return true;
        };
        if (std::find_if(cache.begin(), cache.end(), pred) == cache.end()) {
            cache.push_back(lines);
        } else {
            printf("Found cycle! At %i\n", i);
            break;
        }
    }
    printf("------------\n");
    debug_map(lines);

    return std::to_string(part1(lines));
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<std::string> map;
    Parse::enum_str(std::move(in), "\n", [&map](char *token){
        map.push_back({ token });
    });

    *part1_out = std::to_string(part1(map));
    *part2_out = part2(map);

    return 0;
}

}
