#include "day.h"
#include "parsing.h"

#include <queue>

namespace Solution {

#define DEMO 0
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day17_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day17.txt"
#endif // ------------------------------------
#define INF std::numeric_limits<float>::infinity()

struct Pos { i32 x, y; };
bool operator==(const Pos &l, const Pos &r) { return std::tuple(l.x, l.y) == std::tuple(r.x, r.y); }
Pos operator+(const Pos &l, const Pos &r) { return { l.x + r.x, l.y + r.y }; }
Pos rotate_left(Pos &start) { return { start.y, -start.x }; }
Pos rotate_right(Pos &start) { return { -start.y, start.x }; }

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
bool valid_pos(Map &map, Pos &p) { return (p.x >= 0 && p.y >= 0) && (p.x < map.width && p.y < map.height); }

struct State { Pos pos; Pos dir; u32 loss; u32 count; };

usize dir_index(Pos dir) {
    if (dir.x ==  0 && dir.y == -1) return 0;
    if (dir.x == -1 && dir.y ==  0) return 1;
    if (dir.x ==  1 && dir.y ==  0) return 2;
    if (dir.x ==  0 && dir.y ==  1) return 3;
    else return INT64_MAX;
}

std::string part1(Map &map) {
    //debug_map(map);
    auto cmp = [](State &l, State &r){ return l.loss > r.loss; };
    std::priority_queue<State, std::vector<State>, decltype(cmp)> Q(cmp);
    bool visited[map.width * map.height][4][3];
    for (i32 i = 0; i < map.width * map.height; i++) {
        for (i32 j = 0; j < 4; j++) {
            for (i32 k = 0; k < 3; k++) {
                visited[i][j][k] = false;
            }
        }
    }

    Pos src { 0, 0 };
    Pos dst { (i32)map.width - 1, (i32)map.height - 1 };

    Q.push({ src, {0, 1} });
    Q.push({ src, {1, 0} });
    while (!Q.empty()) {
        auto curr = Q.top();
        Q.pop();
        usize off = curr.pos.y * map.width + curr.pos.x;

        if (visited[off][dir_index(curr.dir)][curr.count]) {
            continue;
        }
        visited[off][dir_index(curr.dir)][curr.count] = true;

        if (curr.pos == dst) {
            return std::to_string(curr.loss);
        }

        { // LEFT
            State move;
            move.dir = rotate_left(curr.dir); 
            move.pos = curr.pos + move.dir;
            if (valid_pos(map, move.pos)) {
                usize offset = move.pos.y * map.width + move.pos.x;
                move.loss = curr.loss + map.cells[offset];
                move.count = 0;
                Q.push(move);
            }
        }

        { // RIGHT
            State move;
            move.dir = rotate_right(curr.dir);  
            move.pos = curr.pos + move.dir;
            if(valid_pos(map, move.pos)){
                usize offset = move.pos.y * map.width + move.pos.x;
                move.loss = curr.loss + map.cells[offset];
                move.count = 0;
                Q.push(move);
            }
        }

        if(curr.count < (3-1)) // forward
        {
            State move;
            move.dir = curr.dir;
            move.pos = curr.pos + move.dir;
            if(valid_pos(map, move.pos)){
                usize offset = move.pos.y * map.width + move.pos.x;
                move.loss = curr.loss + map.cells[offset];
                move.count = curr.count + 1;
                Q.push(move);
            }
        }
    }

    // Could not reach the exit cell
    return std::to_string(INT64_MAX);
}

std::string part2() {
    return "NotCompleted";
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<char*> lines = Parse::split_str(std::move(in), "\n");

    Map map { new u8[lines.size() * strlen(lines[0])](), lines.size(), strlen(lines[0]) };
    for (i32 i = 0; i < map.height; i++) {
        for (i32 j = 0; j < map.width; j++) {
            map.cells[j + (i * map.width)] = lines[i][j] - '0';
        }
    }

    *part1_out = part1(map);
    *part2_out = part2();

    delete[] map.cells;
    return 0;
}

}
