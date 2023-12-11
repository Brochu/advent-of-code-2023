#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 0
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day10_demo2.txt"
//#define GRID_WIDTH 5
//#define GRID_HEIGHT 5
#define GRID_WIDTH 20
#define GRID_HEIGHT 10
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day10.txt"
#define GRID_WIDTH 140
#define GRID_HEIGHT 140
#endif // ------------------------------------
#define FOUND(l, i) (std::find(l.begin(), l.end(), i) != l.end())

enum Dir { N, W, E, S };

struct Grid {
    char *cells;
    usize start;
    std::vector<usize> loop;
};
void debug_grid(Grid &g) {
    printf("[GRID]\n");
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            printf("%c", g.cells[j + (GRID_WIDTH * i)]);
        }
        printf("\n");
    }
    printf("\n");

    //printf("LOOP: ");
    //for (usize pos : g.loop) {
    //    usize x = pos % GRID_WIDTH;
    //    usize y = pos / GRID_WIDTH;
    //    printf("(%lld, %lld); ", x, y);
    //}
    //printf("\n");
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
    if (!FOUND(g.loop, offset)) {
        g.loop.push_back(offset);
    }

    if (p.from == Dir::S) {
        if (*p.pos == '|') p.pos -= GRID_WIDTH;
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
            p.pos -= GRID_WIDTH;
            p.from = Dir::S;
        }
        else if (*p.pos == 'F') {
            p.pos += GRID_WIDTH;
            p.from = Dir::N;
        }
    }
    else if (p.from == Dir::W) {
        if (*p.pos == '-') p.pos += 1;
        else if (*p.pos == 'J') {
            p.pos -= GRID_WIDTH;
            p.from = Dir::S;
        }
        else if (*p.pos == '7') {
            p.pos += GRID_WIDTH;
            p.from = Dir::N;
        }
    }
    else if (p.from == Dir::N) {
        if (*p.pos == '|') p.pos += GRID_WIDTH;
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
    char *up = &g.cells[g.start - GRID_WIDTH];
    if (*up == '|' || *up == '7' || *up == 'F') { paths.push_back({ &*up, Dir::S, 1 }); }
    char *lf = &g.cells[g.start - 1];
    if (*lf == '-' || *lf == 'L' || *lf == 'F') { paths.push_back({ &*lf, Dir::E, 1 }); }
    char *rt = &g.cells[g.start + 1];
    if (*rt == '-' || *rt == 'J' || *rt == '7') { paths.push_back({ &*rt, Dir::W, 1 }); }
    char *dw = &g.cells[g.start + GRID_WIDTH];
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
    for (int i = 0; i < strlen(g.cells); i++) {
        if (!FOUND(g.loop, i)) {
            g.cells[i] = '.';
        }
    }
    //debug_grid(g);

    usize count = 0;
    for (int i = 0; i < GRID_HEIGHT; i++) {
        bool isIn = false;
        for (int j = 0; j < GRID_WIDTH; j++) {
            usize offset = j + (i * GRID_WIDTH);
            char c = g.cells[offset];

            if (c == '|' || c == '7' || c == 'F' || c == 'S') {
                isIn = !isIn;
            }
            else if (c == '.' && isIn) {
                count++;
            }
            
            //printf("(%i, %i) [%lld] -> %c\n", i, j, offset, c);
        }
    }

    return std::to_string(count);
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
