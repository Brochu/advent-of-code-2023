#include "day.h"
#include "parsing.h"

#include <queue>
#include <span>

namespace Solution {

#define DEMO 1
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
struct Pos {
    i32 x;
    i32 y;
};
struct Map {
    std::vector<Cell> cells;
};
void debug_map(Map &map) {
    for (i32 i = 0; i < MAP_SIZE; i++) {
        for (i32 j = 0; j < MAP_SIZE; j++) {
            const usize offset = i * MAP_SIZE + j;
            printf("%c", map.cells[offset]);
        }
        printf("\n");
    }
}
std::vector<Pos> fetch_map(Map &map, Pos p) {
    std::vector<Pos> result;
    //TODO: Add restrictions
    // TREES
    // FORCED DIRS
    result.push_back({ p.x, p.y - 1 });
    result.push_back({ p.x - 1, p.y });
    result.push_back({ p.x + 1, p.y });
    result.push_back({ p.x, p.y + 1 });
    return result;
}

struct State {
    u32 dist;
    Pos pos;
};

usize part1(Map &map) {
    debug_map(map);
    // Create MAX heap
    auto cmp = [](State &left, State &right){ return left.dist < right.dist; };
    std::priority_queue<State, std::vector<State>, decltype(cmp)> Q(cmp);
    Q.push({ 0, {1, 0} });

    u32 dist[MAP_SIZE * MAP_SIZE];
    bool visited[MAP_SIZE * MAP_SIZE];
    for (i32 i = 0; i < MAP_SIZE * MAP_SIZE; i++) {
        dist[i] = 0;
        visited[i] = (map.cells[i] == Cell::Tree) ? true : false;
    }

    while (!Q.empty()) {
        State current = Q.top();
        Q.pop();

        printf("[ELEM] [%i] (%i, %i)\n", current.dist, current.pos.x, current.pos.y);
        const usize offset = current.pos.y * MAP_SIZE + current.pos.x;
        if (map.cells[offset] == Cell::Up) {
            // Stack the only possible next step
        }
        else if (map.cells[offset] == Cell::Left) {
            // Stack the only possible next step
        }
        else if (map.cells[offset] == Cell::Right) {
            // Stack the only possible next step
        }
        else if (map.cells[offset] == Cell::Down) {
            // Stack the only possible next step
        }
        else {
            // Find all possible next steps, skip trees
        }
    }

    return 0;
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
            map.cells.push_back((Cell)lines[i][j]);
        }
    }

    *part1_out = std::to_string(part1(map));
    *part2_out = std::to_string(part2());

    return 0;
}

}
