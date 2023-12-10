#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 1
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day10_demo1.txt"
#define GRID_SIZE 5
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day10.txt"
#define GRID_SIZE 140
#endif // ------------------------------------

enum Dir { N, W, E, S };

struct Grid {
    char *cells;
    usize start;
};
void debug_grid(Grid &g) {
    printf("[GRID]\n");
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            printf("%c", g.cells[j + (GRID_SIZE * i)]);
        }
        printf("\n");
    }
    printf("\n");
}

struct Path {
    char *pos;
    Dir from;
    usize len;
};
void debug_paths(std::span<Path> paths) {
    for (Path &p : paths) {
        char d;
        if (p.from == N) d = 'N';
        else if (p.from == W) d = 'W';
        else if (p.from == E) d = 'E';
        else if (p.from == S) d = 'S';
        printf("[PATH] %c from %c [len=%lld]\n", *p.pos, d, p.len);
    }
}

std::string part1(Grid &g) {
    debug_grid(g);
    std::vector<Path> paths;
    char up = g.cells[g.start - GRID_SIZE];
    if (up == '|' || up == '7' || up == 'F') { paths.push_back({ &up, Dir::S, 1 }); }
    char lf = g.cells[g.start - 1];
    if (lf == '-' || lf == 'L' || lf == 'F') { paths.push_back({ &lf, Dir::E, 1 }); }
    char rt = g.cells[g.start + 1];
    if (rt == '-' || rt == 'J' || rt == '7') { paths.push_back({ &rt, Dir::W, 1 }); }
    char dw = g.cells[g.start + GRID_SIZE];
    if (dw == '|' || dw == 'J' || dw == 'L') { paths.push_back({ &dw, Dir::N, 1 }); }

    debug_paths(paths);
    return "NotCompleted";
}

std::string part2(Grid &g) {
    return "NotCompleted";
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::string gridStr;
    Parse::enum_str(std::move(in), "\n", [&gridStr](char *token){
        gridStr.append(token);
    });

    Grid g;
    for (usize i = 0; i < gridStr.size(); i++) {
        if (gridStr[i] == 'S') {
            g.cells = gridStr.data();
            g.start = i;
        }
    }

    *part1_out = part1(g);
    *part2_out = part2(g);

    return 0;
}

}
