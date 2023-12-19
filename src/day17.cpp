#include "day.h"
#include "parsing.h"

#include <limits>
#include <queue>
#include <span>

namespace Solution {

#define DEMO 1
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day17_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day17.txt"
#endif // ------------------------------------
#define INF std::numeric_limits<float>::infinity()

struct Pos { i32 x, y; };

struct Map {
    u8 *cells;
    usize height;
    usize width;
};
void debug_map(Map &map) {
    for (i32 i = 0; i < map.height; i++) {
        for (i32 j = 0; j < map.width; j++) {
            const usize idx = i * map.width + j;
            printf("%i ", map.cells[idx]);
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
    Q.push({ start, {0, 1}, 0, 0 });
    Q.push({ start, {1, 0}, 0, 0 });

    Pos prev[map.width * map.height][4];
    float dist[map.width * map.height][4];
    for (i32 i = 0; i < map.height; i++) {
        for (i32 j = 0; j < map.width; j++) {
            const usize offset = i * map.width + j;
            prev[offset][0] = prev[offset][1] = prev[offset][2] = prev[offset][3] = { -1, -1 };
            dist[offset][0] = dist[offset][1] = dist[offset][2] = dist[offset][3] = INF;
        }
    }
    prev[0][0] = prev[0][1] = prev[0][2] = prev[0][3] = { -1, -1 };
    dist[0][0] = dist[0][1] = dist[0][2] = dist[0][3] = 0.f;

    while (!Q.empty()) {
        State u = Q.top();
        Q.pop();
    }
    //debug_path(map, prevs);

    const usize exit = (map.width * map.height) - 1;
    const float result = std::min(dist[exit][0], std::min(dist[exit][1], std::min(dist[exit][2], dist[exit][3])));
    return std::to_string(result);
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
