#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 0
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day11_demo1.txt"
#define GRID_SIZE 10
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day11.txt"
#define GRID_SIZE 140
#endif // ------------------------------------
#define FOUND(l, a) (std::find(std::begin(l), std::end(l), a)) != std::end(l)

struct Space {
    char *grid;
    std::vector<i64> colsEmpty;
    std::vector<i64> rowsEmpty;
};
void debug_space(Space &s) {
    printf("[SPACE]\n");
    for (i64 i = 0; i < GRID_SIZE; i++) {
        for (i64 j = 0; j < GRID_SIZE; j++) {
            i64 offset = j + (i * GRID_SIZE);
            printf("%c", s.grid[offset]);
        }
        printf("\n");
    }
    printf("[COLS]: ");
    for (i64 pos : s.colsEmpty) {
        printf("%lld, ", pos);
    }
    printf("\n");
    printf("[ROWS]: ");
    for (i64 pos : s.rowsEmpty) {
        printf("%lld, ", pos);
    }
    printf("\n");
}

struct Pos {
    i64 x;
    i64 y;
};
i64 man_distance(Pos &left, Pos &right) {
    return abs(right.x - left.x) + abs(right.y - left.y);
}

std::string part1(Space &s) {
    //debug_space(s);
    std::vector<Pos> galaxies;

    i64 ymod = 0;
    for (i64 i = 0; i < GRID_SIZE; i++) {
        if (FOUND(s.rowsEmpty, i)) { ymod++; }
        i64 xmod = 0;
        for (i64 j = 0; j < GRID_SIZE; j++) {
            if (FOUND(s.colsEmpty, j)) { xmod++; }
            i64 offset = j + (i * GRID_SIZE);
            if (s.grid[offset] == '#') {
                //printf("[GAL] (%i, %i) [+(%i, %i)] - (%i, %i)\n", j, i, xmod, ymod, (j + xmod), (i + ymod));
                galaxies.push_back({ (j + xmod), (i + ymod) });
            }
        }
    }
    //for (Pos &g : galaxies) {
    //    printf("(%i, %i)\n", g.x, g.y);
    //}
    i64 total = 0;
    for (i64 i = 0; i < galaxies.size(); i++) {
        for (i64 j = i; j < galaxies.size(); j++) {
            if (i == j) continue;
            i64 dist = man_distance(galaxies[i], galaxies[j]);
            //printf("(%i, %i) -> %lld\n", i, j, dist);
            total += dist;
        }
    }

    return std::to_string(total);
}

std::string part2(Space &s) {
    std::vector<Pos> galaxies;

    i64 ymod = 0;
    for (i64 i = 0; i < GRID_SIZE; i++) {
        if (FOUND(s.rowsEmpty, i)) { ymod+=999999; }
        i64 xmod = 0;
        for (i64 j = 0; j < GRID_SIZE; j++) {
            if (FOUND(s.colsEmpty, j)) { xmod+=999999; }
            i64 offset = j + (i * GRID_SIZE);
            if (s.grid[offset] == '#') {
                galaxies.push_back({ (j + xmod), (i + ymod) });
            }
        }
    }
    i64 total = 0;
    for (i64 i = 0; i < galaxies.size(); i++) {
        for (i64 j = i; j < galaxies.size(); j++) {
            if (i == j) continue;
            i64 dist = man_distance(galaxies[i], galaxies[j]);
            total += dist;
        }
    }

    return std::to_string(total);
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::string spaceStr;
    Parse::enum_str(std::move(in), "\n", [&spaceStr](char *token){
        spaceStr.append(token);
    });

    char *space = spaceStr.data();
    std::vector<i64> rows;
    for (i64 i = 0; i < GRID_SIZE; i++) {
        bool isEmpty = true;
        for (i64 j = 0; j < GRID_SIZE; j++) {
            i64 offset = j + (i * GRID_SIZE);
            if (space[offset] != '.') {
                isEmpty = false;
            }
        }
        if (isEmpty) {
            rows.push_back(i);
        }
    }

    std::vector<i64> cols;
    for (i64 i = 0; i < GRID_SIZE; i++) {
        bool isEmpty = true;
        for (i64 j = 0; j < GRID_SIZE * GRID_SIZE; j += GRID_SIZE) {
            i64 offset = j + i;
            if (space[offset] != '.') {
                isEmpty = false;
            }
        }
        if (isEmpty) {
            cols.push_back(i);
        }
    }
    Space s { space, cols, rows };

    *part1_out = part1(s);
    *part2_out = part2(s);

    return 0;
}

}
