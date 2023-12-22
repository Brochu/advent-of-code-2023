#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 0
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day21_demo1.txt"
#define WIDTH 11
#define HEIGHT 11
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day21.txt"
#define WIDTH 131
#define HEIGHT 131
#endif // ------------------------------------

struct Pos { i32 x; i32 y; };
bool is_valid(Pos p) {
    return p.x >= 0 && p.x < WIDTH && p.x >= 0 && p.y < HEIGHT;
}

struct Map {
    Pos start;
    std::vector<Pos> rocks;
};
bool is_rock(Map &map, Pos p) {
    return std::find_if(map.rocks.begin(), map.rocks.end(), [&p](Pos &in){
        return in.x == p.x && in.y == p.y;
    }) != map.rocks.end();
}
bool is_visited(std::span<Pos> visited, Pos p) {
    return std::find_if(visited.begin(), visited.end(), [&p](Pos &in){
        return in.x == p.x && in.y == p.y;
    }) != visited.end();
}
void debug_map(Map &map, std::span<Pos> visited) {
    for (i32 i = 0; i < HEIGHT; i++) {
        for (i32 j = 0; j < WIDTH; j++) {
            if (is_rock(map, { j, i })) printf("#");
            else if (is_visited(visited, { j, i })) printf("O");
            else if (j == map.start.x && i == map.start.y) printf("S");
            else printf(".");
        }
        printf("\n");
    }
}

usize part1(Map &map) {
    std::vector<Pos> stack;
    stack.push_back(map.start);

    for (i32 i = 0; i < 64; i++) {
        usize s = stack.size();

        for (i32 j = 0; j < s; j++) {
            Pos curr = stack.back();
            stack.pop_back();

            auto push = [&stack](Pos p){
                auto it = std::find_if(stack.begin(), stack.end(), [&p](Pos &in){
                    return in.x == p.x && in.y == p.y;
                });
                if (it == stack.end()) {
                    stack.insert(stack.begin(), p);
                }
            };
            Pos up { curr.x, curr.y - 1 };
            if (!is_rock(map, up) && is_valid(up)) push(up);
            Pos left { curr.x - 1, curr.y };
            if (!is_rock(map, left) && is_valid(left)) push(left);
            Pos right { curr.x + 1, curr.y };
            if (!is_rock(map, right) && is_valid(right)) push(right);
            Pos down { curr.x, curr.y + 1 };
            if (!is_rock(map, down) && is_valid(down)) push(down);
        }
        //debug_map(map, stack);
        //printf("------------------\n");
    }
    //for (Pos &p : stack) {
    //    printf("(%i, %i)\n", p.x, p.y);
    //}
    return stack.size();
}

usize part2() {
    return 0;
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    Map map;
    std::vector<char*> lines = Parse::split_str(std::move(in), "\n");
    for (i32 i = 0; i < lines.size(); i++) {
        for (i32 j = 0; j < strlen(lines[i]); j++) {
            if (lines[i][j] == 'S') {
                map.start = { j, i };
            }
            else if (lines[i][j] == '#') {
                map.rocks.push_back({ j, i });
            }
        }
    }

    *part1_out = std::to_string(part1(map));
    *part2_out = std::to_string(part2());

    return 0;
}

}
