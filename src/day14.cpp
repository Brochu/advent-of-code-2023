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

void debug_map(std::span<std::string> lines) {
    for (std::string &s : lines) {
        printf("%s\n", s.c_str());
    }
}

std::string part1(std::span<std::string> lines) {
    usize heightmap[lines[0].size()];
    for (i32 i = 0; i < lines[0].size(); i++) {
        heightmap[i] = lines.size();
    }

    usize total = 0;
    for (i32 i = 0; i < lines.size(); i++) {
        for (i32 j = 0; j < lines[i].size(); j++) {
            usize pos = lines.size() - i;

            if (lines[i][j] == 'O') {
                //printf("Found O at %i\n", j);
                total += heightmap[j];
                heightmap[j]--;
            }
            else if (lines[i][j] == '#') {
                //printf("Found # at %i\n", j);
                heightmap[j] = pos - 1;
            }
        }
        //printf("[HEIGHTS]: ");
        //for (i32 i = 0; i < strlen(lines[0]); i++) {
        //    printf("%lld, ", heightmap[i]);
        //}
        //printf("\n");
    }
    return std::to_string(total);
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
                //printf("(%i, %i)\n", i, j);
                for (i32 k = i - 1; k >= 0; k--) {
                    //printf("k=%i\n", k);
                    if (lines[k][j] == 'O' || lines[k][j] == '#') {
                        //printf("[SWAP] k=%i; i=%i\n", k + 1, i);
                        lines[i][j] = '.';
                        lines[k + 1][j] = 'O';
                        break;
                    }
                    if (k == 0) {
                        //printf("[SWAP] To start\n");
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
    for (i32 i = 0; i < 3; i++) {
        tilt(lines);
        lines = rotate(lines);
        tilt(lines);
        lines = rotate(lines);
        tilt(lines);
        lines = rotate(lines);
        tilt(lines);
        lines = rotate(lines);
    }
    printf("------------\n");
    debug_map(lines);

    return std::to_string(total);
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<std::string> map;
    Parse::enum_str(std::move(in), "\n", [&map](char *token){
        map.push_back({ token });
    });

    *part1_out = part1(map);
    *part2_out = part2(map);

    return 0;
}

}
