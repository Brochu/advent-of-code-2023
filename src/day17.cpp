#include "day.h"
#include "parsing.h"

#include <queue>
#include <span>
#include <unordered_map>

namespace Solution {

#define DEMO 1
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day17_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day17.txt"
#endif // ------------------------------------

struct Map {
    u8 *cells;
    usize h;
    usize w;
};
void debug_map(Map &map) {
    for (i32 i = 0; i < map.h; i++) {
        for (i32 j = 0; j < map.w; j++) {
            printf("%i ", map.cells[j + (i * map.w)]);
        }
        printf("\n");
    }
}

std::string part1(Map &map) {
    debug_map(map);

    std::unordered_map<usize, u32> dists;
    return std::to_string(dists[(map.h * map.w) - 1]);
}

std::string part2() {
    return "NotCompleted";
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<char*> lines = Parse::split_str(std::move(in), "\n");

    Map m { new u8[lines.size() * strlen(lines[0])](), lines.size(), strlen(lines[0]) };
    for (i32 i = 0; i < m.h; i++) {
        for (i32 j = 0; j < m.w; j++) {
            m.cells[j + (i * m.w)] = lines[i][j] - '0';
        }
    }

    *part1_out = part1(m);
    *part2_out = part2();

    delete[] m.cells;
    return 0;
}

}
