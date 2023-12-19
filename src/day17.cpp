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

struct Pos { i32 x, y; };
Pos* find_pos(std::span<Pos> list, Pos needle) {
    auto it = std::find_if(list.begin(), list.end(), [&needle](Pos &in){
        return needle.x == in.x && needle.y == in.y;
    });
    if (it != list.end()) { return &*it; }
    return nullptr;
}

struct Map {
    u8 *cells;
    usize height;
    usize width;

    u8 get(Pos p){ return cells[p.y * width + p.x]; }
    bool is_valid(Pos p) { return (p.x >= 0 && p.x < width) && (p.y >= 0 && p.y < height); }
};
usize pos_offset(Map &map, Pos p) { return p.y * map.width + p.x; }
Pos offset_pos(Map &map, usize o) {
    i32 x = o % map.width;
    i32 y = o / map.width;
    return { x, y };
}
void debug_map(Map &map) {
    for (i32 i = 0; i < map.height; i++) {
        for (i32 j = 0; j < map.width; j++) { printf("%i ", map.get({ i, j })); }
        printf("\n");
    }
}
void debug_path(Map &map, std::unordered_map<usize, Pos> &prevs) {
    std::vector<Pos> path;
    usize offset = (map.width * map.height) - 1;
    path.push_back({ (i32)map.width - 1, (i32)map.height - 1 });

    while (prevs[offset].x != -1 && prevs[offset].y != -1) {
        path.insert(path.begin(), prevs[offset]);
        offset = pos_offset(map ,prevs[offset]);
    }

    printf("[PATH]\n");
    for (Pos &node : path) {
        printf("(%i, %i)\n", node.x, node.y);
    }
    for (i32 i = 0; i < map.height; i++) {
        for (i32 j = 0; j < map.width; j++) {
            Pos *p = find_pos(path, { i, j });
            if (p != nullptr) printf("* ");
            else printf("%i ", map.get({ i, j }));
        }
        printf("\n");
    }
}

struct State { Pos pos; Pos dir; float loss; u32 count; };
void debug_state(State &s) {
    printf("[STATE] pos=(%i, %i); dir=(%i, %i); loss=%f; count=%i\n",
           s.pos.x, s.pos.y, s.dir.x, s.dir.y, s.loss, s.count);
}

std::string part1(Map &map) {
    debug_map(map);
    const Pos start = { 0, 0 };

    auto cmp = [](State &left, State &right){ return left.loss > right.loss; };
    std::priority_queue<State, std::vector<State>, decltype(cmp)> Q(cmp);
    Q.push({ start, {1, 0}, 0, 0 });
    Q.push({ start, {0, 1}, 0, 0 });

    std::unordered_map<usize, Pos> prevs;
    std::unordered_map<usize, float> dists;
    for (i32 i = 0; i < map.height; i++) {
        for (i32 j = 0; j < map.width; j++) {
            const usize offset = i * map.width + j;
            prevs[offset] = { -1, -1 };
            dists[offset] = std::numeric_limits<float>::infinity();
        }
    }
    prevs[0] = { -1, -1 };
    dists[0] = 0.f;

    while (!Q.empty()) {
        State u = Q.top();
        Q.pop();
        debug_state(u);

        printf("[DIRECTIONS]:\n");
        // TURN LEFT
        Pos go_left = { u.dir.y, -u.dir.x };
        Pos left = { u.pos.x + go_left.x, u.pos.y + go_left.y };
        if (map.is_valid(left)) {
            printf("- (%i, %i), (%i, %i)\n", go_left.x, go_left.y, left.x, left.y);
        }
        // GO FORWARD
        Pos go_forward = u.dir;
        Pos forward = { u.pos.x + go_forward.x, u.pos.y + go_forward.y };
        if (map.is_valid(forward)) {
            printf("- (%i, %i), (%i, %i)\n", go_forward.x, go_forward.y, forward.x, forward.y);
        }
        // TURN RIGHT
        Pos go_right = { -u.dir.y, u.dir.x };
        Pos right = { u.pos.x + go_right.x, u.pos.y + go_right.y };
        if (map.is_valid(right)) {
            printf("- (%i, %i), (%i, %i)\n", go_right.x, go_right.y, right.x, right.y);
        }
    }
    //debug_path(map, prevs);

    const usize exit = (map.width * map.height) - 1;
    return std::to_string(dists[exit]);
}

std::string part2() {
    return "NotCompleted";
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<char*> lines = Parse::split_str(std::move(in), "\n");

    Map m { new u8[lines.size() * strlen(lines[0])](), lines.size(), strlen(lines[0]) };
    for (i32 i = 0; i < m.height; i++) {
        for (i32 j = 0; j < m.width; j++) {
            m.cells[j + (i * m.width)] = lines[i][j] - '0';
        }
    }

    *part1_out = part1(m);
    *part2_out = part2();

    delete[] m.cells;
    return 0;
}

}
