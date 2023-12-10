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
    std::vector<usize> loop;
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

    printf("LOOP: ");
    for (usize pos : g.loop) {
        usize x = pos % GRID_SIZE;
        usize y = pos / GRID_SIZE;
        printf("(%lld, %lld); ", x, y);
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
void step_path(Path &p, Grid &g) {
    usize offset = p.pos - g.cells;
    if (std::find(g.loop.begin(), g.loop.end(), offset) == g.loop.end()) {
        g.loop.push_back(offset);
    }

    if (p.from == Dir::S) {
        if (*p.pos == '|') p.pos -= GRID_SIZE;
        else if (*p.pos == '7') {
            p.pos -= 1;
            p.from = Dir::E;
        }
        else if (*p.pos == 'F') {
            p.pos += 1;
            p.from = Dir::W;
        }
    }
    else if (p.from == Dir::E) {
        if (*p.pos == '-') p.pos -= 1;
        else if (*p.pos == 'L') {
            p.pos -= GRID_SIZE;
            p.from = Dir::S;
        }
        else if (*p.pos == 'F') {
            p.pos += GRID_SIZE;
            p.from = Dir::N;
        }
    }
    else if (p.from == Dir::W) {
        if (*p.pos == '-') p.pos += 1;
        else if (*p.pos == 'J') {
            p.pos -= GRID_SIZE;
            p.from = Dir::S;
        }
        else if (*p.pos == '7') {
            p.pos += GRID_SIZE;
            p.from = Dir::N;
        }
    }
    else if (p.from == Dir::N) {
        if (*p.pos == '|') p.pos += GRID_SIZE;
        else if (*p.pos == 'J') {
            p.pos -= 1;
            p.from = Dir::E;
        }
        else if (*p.pos == 'L') {
            p.pos += 1;
            p.from = Dir::W;
        }
    }

    p.len++;
}

bool is_done(std::span<Path> paths, Grid &g) {
    usize offset = paths[0].pos - g.cells;
    for (Path &p : paths) {
        usize current = p.pos - g.cells;
        if (current != offset) return false;
    }
    return true;
}

std::string part1(Grid &g) {
    //debug_grid(g);
    std::vector<Path> paths;
    char *up = &g.cells[g.start - GRID_SIZE];
    if (*up == '|' || *up == '7' || *up == 'F') { paths.push_back({ &*up, Dir::S, 1 }); }
    char *lf = &g.cells[g.start - 1];
    if (*lf == '-' || *lf == 'L' || *lf == 'F') { paths.push_back({ &*lf, Dir::E, 1 }); }
    char *rt = &g.cells[g.start + 1];
    if (*rt == '-' || *rt == 'J' || *rt == '7') { paths.push_back({ &*rt, Dir::W, 1 }); }
    char *dw = &g.cells[g.start + GRID_SIZE];
    if (*dw == '|' || *dw == 'J' || *dw == 'L') { paths.push_back({ &*dw, Dir::N, 1 }); }

    while (!is_done(paths, g)) {
        //debug_paths(paths);
        for (Path &p : paths) {
            step_path(p, g);
        }
        //printf("--------\n");
    }
    g.loop.push_back(paths[0].pos - g.cells);
    return std::to_string(paths[0].len);
}

std::string part2(Grid &g) {
    debug_grid(g);
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
            g.loop.push_back(i);
        }
    }

    *part1_out = part1(g);
    *part2_out = part2(g);

    return 0;
}

}
