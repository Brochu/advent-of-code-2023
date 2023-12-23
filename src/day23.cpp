#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 1
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day23_demo1.txt"
#define MAP_SIZE 23
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day23.txt"
#define MAP_SIZE 141
#endif // ------------------------------------

enum Cell {
    Path = '.',
    Tree = '#',
    Up   = '^',
    Left = '<',
    Right= '>',
    Down = 'v',
};
struct Map {
    std::vector<Cell> cells;
};
void debug_map(Map &map) {
    for (i32 i = 0; i < MAP_SIZE; i++) {
        for (i32 j = 0; j < MAP_SIZE; j++) {
            const usize offset = i * MAP_SIZE + j;
            printf("%c", map.cells[offset]);
        }
        printf("\n");
    }
}

usize part1(Map &map) {
    debug_map(map);
    return 0;
}

usize part2() {
    return 0;
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    Map map;
    std::vector<char*> lines = Parse::split_str(std::move(in), "\n");
    for (i32 i = 0; i < lines.size(); i++) {
        for (i32 j = 0; j < strlen(lines[0]); j++) {
            map.cells.push_back((Cell)lines[i][j]);
        }
    }

    *part1_out = std::to_string(part1(map));
    *part2_out = std::to_string(part2());

    return 0;
}

}
