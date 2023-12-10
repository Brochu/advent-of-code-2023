#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 1
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day10_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day10.txt"
#endif // ------------------------------------

struct Coord {
    u8 x, y;
};

struct Grid {
    std::vector<char*> cells;
    Coord start;
};

void debug_grid(Grid grid) {
    for (int i = 0; i < grid.cells.size(); i++) {
        for (int j = 0; j < strlen(grid.cells[i]); j++) {
            printf("%c ", grid.cells[i][j]);
        }
        printf("\n");
    }
    printf("[START] (%i, %i)\n", grid.start.x, grid.start.y);
}

std::string part1(Grid &grid) {
    return "NotCompleted";
}

std::string part2(Grid &grid) {
    return "NotCompleted";
}

void find_start(Grid &grid) {
    for (int i = 0; i < grid.cells.size(); i++) {
        for (int j = 0; j < strlen(grid.cells[i]); j++) {
            if (grid.cells[i][j] == 'S') {
                grid.start = { (u8)i, (u8)j };
                return;
            }
        }
    }
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<char*> lines = Parse::split_str(std::move(in), "\n");

    Grid grid = { lines };
    find_start(grid);

    *part1_out = part1(grid);
    *part2_out = part2(grid);

    return 0;
}

}
