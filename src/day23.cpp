#include "day.h"
#include "parsing.h"

#include <queue>
#include <span>

namespace Solution {

#define DEMO 0
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day23_demo1.txt"
#define MAP_SIZE 23
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day23.txt"
#define MAP_SIZE 141
#endif // ------------------------------------

//TODO: Remember this
enum Cell {
    Path = '.',
    Tree = '#',
    Up   = '^',
    Left = '<',
    Right= '>',
    Down = 'v',
};
struct Pos { i32 x; i32 y; };
bool is_valid(Pos &pos) {
    return pos.x >= 0 && pos.x < MAP_SIZE && pos.y >= 0 && pos.y < MAP_SIZE;
}
bool operator==(const Pos &left, const Pos &right) {
    return left.x == right.x && left.y == right.y;
}
Pos operator+(const Pos &left, const Pos &right) {
    return {left.x + right.x, left.y + right.y};
}

typedef std::vector<Cell> Map;
void debug_map(Map &map, Pos &start, Pos &end) {
    for (i32 i = 0; i < MAP_SIZE; i++) {
        for (i32 j = 0; j < MAP_SIZE; j++) {
            const Pos curr { j, i };
            if (curr == start) printf("O");
            else if (curr == end) printf("X");
            else {
                printf("%c", map[i * MAP_SIZE + j]);
            }
        }
        printf("\n");
    }
}
std::vector<Pos> fetch_map(Map &map, std::span<Pos> visited, Pos &p) {
    std::vector<Pos> result;
    Pos deltas[4] { {0, -1}, {-1, 0}, {1, 0}, {0, 1} };

    const usize poff = p.y * MAP_SIZE + p.x;
    if (map[poff] == Cell::Up) result.push_back(p + deltas[0]);
    else if (map[poff] == Cell::Left) result.push_back(p + deltas[1]);
    else if (map[poff] == Cell::Right) result.push_back(p + deltas[2]);
    else if (map[poff] == Cell::Down) result.push_back(p + deltas[3]);
    else {
        for (Pos &delta : deltas) result.push_back(p + delta);
    }

    auto end = std::remove_if(result.begin(), result.end(), [&map, &visited](Pos &in){
        const usize offset = in.y * MAP_SIZE + in.x;
        auto pred = [&in](Pos &v){ return v == in; };
        return !is_valid(in) || std::find_if(visited.begin(), visited.end(), pred) != visited.end() || map[offset] == Cell::Tree;
    });
    return { result.begin(), end };
}

struct State {
    u32 dist;
    Pos pos;
    std::vector<Pos> visited;
};
bool is_done(State &s, Pos &dst, std::span<Pos> next) {
    return next.size() <= 0 || s.pos == dst;
}

usize part1(Map &map) {
    Pos src { 1, 0 };
    Pos dst { MAP_SIZE - 2, MAP_SIZE - 1 };
    //debug_map(map, src, dst);

    std::vector<State> done;
    std::vector<State> stack;
    stack.push_back({ 0, src, {} });

    while (!stack.empty()) {
    //while (stack.size() == 1) {
        for (i32 idx = stack.size() - 1; idx >= 0; idx--) {
            std::vector<Pos> reach = fetch_map(map, stack[idx].visited, stack[idx].pos);
            if (is_done(stack[idx], dst, reach)) {
                done.push_back(stack[idx]);
                stack.erase(stack.begin() + idx);
                continue;
            }

            i32 newx = stack[idx].pos.x;
            i32 newy = stack[idx].pos.y;
            stack[idx].visited.push_back({ newx, newy });
            stack[idx].pos = reach[0];
            stack[idx].dist++;

            if (reach.size() > 1) {
                for (i32 i = 1; i < reach.size(); i++) {
                    State dup = stack[idx];
                    dup.pos = reach[i];
                    stack.push_back(dup);
                }
            }
        }
    }

    usize max = 0;
    for (State s : done) {
        if (s.dist > max) max = s.dist;
    }
    return max;
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
            map.push_back((Cell)lines[i][j]);
        }
    }

    *part1_out = std::to_string(part1(map));
    *part2_out = std::to_string(part2());

    return 0;
}

}
