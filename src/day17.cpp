#include "day.h"
#include "parsing.h"

#include <iostream>
#include <limits>
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

enum Direction { NONE, UP, LEFT, RIGHT, DOWN };
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
void debug_path(Map &map, std::unordered_map<usize, usize> &prevs) {
    std::vector<usize> path;
    usize offset = (map.w * map.h) - 1;
    path.push_back(offset);

    while (prevs[offset] != ~0) {
        path.insert(path.begin(), prevs[offset]);
        offset = prevs[offset];
    }

    printf("[PATH]\n");
    for (usize node : path) {
        i32 x = node % map.w;
        i32 y = node / map.w;
        printf("(%i, %i)\n", x, y);
    }
    for (i32 i = 0; i < map.h; i++) {
        for (i32 j = 0; j < map.w; j++) {
            const usize offset = j + (i * map.w);
            if (std::find(path.begin(), path.end(), offset) != path.end()) {
                printf("* ");
            } else {
                printf("%i ", map.cells[offset]);
            }
        }
        printf("\n");
    }
}
void debug_dists(Map &map, std::unordered_map<usize, float> &dists) {
    for (i32 i = 0; i < map.h; i++) {
        for (i32 j = 0; j < map.w; j++) {
            printf("%f ", dists[j + (i * map.w)]);
        }
        printf("\n");
    }
}

struct State {
    i32 x, y;
    float dist;
    Direction from;
    u32 count;
};

std::string part1(Map &map) {
    debug_map(map);

    std::unordered_map<usize, usize> prevs;
    std::unordered_map<usize, float> dists;
    for (i32 i = 0; i < map.h; i++) {
        for (i32 j = 0; j < map.w; j++) {
            const usize offset = j + (i * map.w);
            prevs[offset] = ~0;
            dists[offset] = std::numeric_limits<float>::infinity();
        }
    }
    prevs[0] = ~0;
    dists[0] = 0.f;

    auto cmp = [](State &left, State &right){ return left.dist > right.dist; };
    std::priority_queue<State, std::vector<State>, decltype(cmp)> Q(cmp);
    Q.push({ 0, 0, 0.f, NONE, 1 });

    while (!Q.empty()) {
        const State u = Q.top();
        Q.pop();
        //if (u.count > 3) continue;

        usize idx = u.x + (u.y * map.w);
        //printf("[PICKED] (%i, %i) (from %i; %i) [%f]\n", u.x, u.y, u.from, u.count, u.dist);

        std::vector<usize> neighbors;
        if (u.y > 0 && u.from != Direction::UP) {
            neighbors.push_back(u.x + ((u.y - 1) * map.w));
        }
        if (u.y < (map.h - 1) && u.from != Direction::DOWN) {
            neighbors.push_back(u.x + ((u.y + 1) * map.w));
        }
        if (u.x > 0 && u.from != Direction::LEFT) {
            neighbors.push_back((u.x - 1) + (u.y * map.w));
        }
        if (u.x < (map.w - 1) && u.from != Direction::RIGHT) {
            neighbors.push_back((u.x + 1) + (u.y * map.w));
        }
        for (usize n : neighbors) {
            if (dists[idx] + map.cells[n] < dists[n]) {
                prevs[n] = idx;
                dists[n] = dists[idx] + map.cells[n];
                i32 x = n % map.w;
                i32 y = n / map.w;
                Direction from = NONE;
                if (x - u.x == 1) from = Direction::LEFT;
                else if (x - u.x == -1) from = Direction::RIGHT;
                else if (y - u.y == 1) from = Direction::UP;
                else if (y - u.y == -1) from = Direction::DOWN;
                //printf("[ADDED] (%i, %i), prev = (%i, %i), dist = %f\n", x, y, u.x, u.y, dists[n]);
                Q.push({ x, y, dists[n], from, u.from == from ? u.count + 1 : 1 });
            }
        }
        //std::cin.ignore(1);
    }
    //debug_dists(map, dists);
    debug_path(map, prevs);

    const usize exit = (map.h * map.w) - 1;
    return std::to_string(dists[exit]);
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
