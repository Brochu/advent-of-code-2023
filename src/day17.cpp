#include "day.h"
#include "parsing.h"

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

struct State {
    i32 x, y;
    i32 prevx, prevy;
    float dist;
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
    Q.push({ 0, 0, -1, -1, 0.f });

    while (!Q.empty()) {
        const State u = Q.top();
        Q.pop();
        printf("[PICKED] (%i, %i) (from %i, %i) [%f]\n", u.x, u.y, u.prevx, u.prevy, u.dist);

        std::vector<usize> neighbors;
        if (u.y > 0 && (u.x != u.prevx || (u.y - 1) != u.prevy)) {
            neighbors.push_back(u.x + ((u.y - 1) * map.w));
        }
        if (u.y < (map.h - 1) && (u.x != u.prevx || (u.y + 1) != u.prevy)) {
            neighbors.push_back(u.x + ((u.y + 1) * map.w));
        }
        if (u.x > 0 && ((u.x - 1) != u.prevx || u.y != u.prevy)) {
            neighbors.push_back((u.x - 1) + (u.y * map.w));
        }
        if (u.x < (map.w - 1) && ((u.x + 1) != u.prevx || u.y != u.prevy)) {
            neighbors.push_back((u.x + 1) + (u.y * map.w));
        }
        printf("Neighbors -> \n");
        for (usize n : neighbors) {
            printf("%lld -> (%lld, %lld)\n", n, n % map.w, n / map.w);
            //TODO: Condition checks for updating dists and prevs
        }
    }

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
