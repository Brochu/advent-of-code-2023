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
Pos operator+(const Pos &left, const Pos &right) { return {left.x + right.x, left.y + right.y}; }

struct Map {
    std::vector<Cell> cells;
};
void debug_map(Map &map, Pos &start, Pos &end) {
    for (i32 i = 0; i < MAP_SIZE; i++) {
        for (i32 j = 0; j < MAP_SIZE; j++) {
            if (start.x == j && start.y == i) printf("O");
            else if (end.x == j && end.y == i) printf("X");
            else {
                printf("%c", map.cells[i * MAP_SIZE + j]);
            }
        }
        printf("\n");
    }
}
bool is_valid(Pos &pos) { return pos.x >= 0 && pos.x < MAP_SIZE && pos.y >= 0 && pos.y < MAP_SIZE; }
std::vector<Pos> fetch_map(Map &map, const bool *visited, Pos &p) {
    Pos deltas[4] {
        {  0, -1 },
        { -1,  0 },
        {  1,  0 },
        {  0,  1 },
    };
    std::vector<Pos> result;
    for (Pos &delta : deltas) {
        Pos pos = p + delta;
        const usize offset = pos.y * MAP_SIZE + pos.x;

        if (is_valid(pos) && !visited[offset]) {
            result.push_back(pos);
        }
    }
    return result;
}

struct State {
    u32 dist;
    Pos pos;
};

usize part1(Map &map) {
    Pos src { 1, 0 };
    Pos dst { MAP_SIZE - 2, MAP_SIZE - 1 };
    debug_map(map, src, dst);

    // Create MAX heap
    auto cmp = [](State &left, State &right){ return left.dist < right.dist; };
    std::priority_queue<State, std::vector<State>, decltype(cmp)> Q(cmp);
    Q.push({ 0, src });

    u32 dist[MAP_SIZE * MAP_SIZE];
    bool visited[MAP_SIZE * MAP_SIZE];
    for (i32 i = 0; i < MAP_SIZE * MAP_SIZE; i++) {
        dist[i] = 0;
        visited[i] = (map.cells[i] == Cell::Tree) ? true : false;
    }

    while (!Q.empty()) {
        State current = Q.top();
        Q.pop();

        const usize coff = current.pos.y * MAP_SIZE + current.pos.x;
        visited[coff] = true;

        if (current.pos.x == dst.x && current.pos.y == dst.y) {
            // Found destination cell
            return dist[current.pos.y * MAP_SIZE + current.pos.x];
        }

        printf("[CURR] [%i] (%i, %i)\n", current.dist, current.pos.x, current.pos.y);
        for (Pos &n : fetch_map(map, visited, current.pos)) {
            const usize noff = n.y * MAP_SIZE + n.x;
            printf("[N] [%i] (%i, %i)\n", dist[noff], n.x, n.y);
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
