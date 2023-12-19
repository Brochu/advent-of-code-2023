#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 0
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day18_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day18.txt"
#endif // ------------------------------------
#define FOUND(l, p) (std::find_if(std::begin(l), std::end(l), p) != std::end(l))

struct Instr {
    char dir;
    i32 steps;
    char *color; // I think this is for part 2
};
void debug_instr(std::span<Instr> prog) {
    for (Instr &i : prog) { printf("[%c][%i] -> '%s'\n", i.dir, i.steps, i.color); }
}

struct Pos {
    i32 x;
    i32 y;
};

void show_map(std::span<Pos> trench, i32 fromx, i32 tox, i32 fromy, i32 toy) {
    for (i32 i = fromy; i < toy; i++) {
        for (i32 j = fromx; j < tox; j++) {
            auto pred = [&i, &j](Pos &in){ return in.x == j && in.y == i; };
            if (FOUND(trench, pred)) {
                printf("# ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

std::string part1(std::span<Instr> prog) {
    std::vector<Pos> trench;
    i32 minx = INT_MAX;
    i32 miny = INT_MAX;
    i32 maxx = 0;
    i32 maxy = 0;

    Pos current { 0, 0 };
    for (Instr &i : prog) {
        for (i32 j = 0; j < i.steps; j++) {
            if (i.dir == 'U') current.y--;
            else if (i.dir == 'L') current.x--;
            else if (i.dir == 'R') current.x++;
            else if (i.dir == 'D') current.y++;
            trench.push_back(current);

            //printf("[NEW] (%i, %i)\n", current.x, current.y);
            minx = std::min(minx, current.x);
            miny = std::min(miny, current.y);
            maxx = std::max(maxx, current.x);
            maxy = std::max(maxy, current.y);
        }
    }
    minx--; miny--;
    maxx+=2; maxy+=2;
    //show_map(trench, minx, maxx, miny, maxy);

    //TODO: This is slow, look up information on shoelace formula, should optim this
    std::vector<Pos> stack;
    stack.push_back({ 1, 1 });
    while (!stack.empty()) {
        Pos current = stack.back();
        stack.pop_back();

        auto pred = [&current](Pos &in){ return in.x == current.x && in.y == current.y; };
        if (FOUND(trench, pred)) { continue; }
        trench.push_back(current);

        stack.push_back({ current.x, current.y - 1 });
        stack.push_back({ current.x - 1, current.y });
        stack.push_back({ current.x + 1, current.y });
        stack.push_back({ current.x, current.y + 1 });
    }
    //show_map(trench, minx, maxx, miny, maxy);

    return std::to_string(trench.size());
}

std::string part2() {
    return "NotCompleted";
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);

    std::vector<Instr> prog;
    Parse::enum_str(std::move(in), "\n", [&prog](char *token){
        char dir = *token;
        token += 2;
        std::vector<char*> elems = Parse::split_char(token, " ");
        prog.push_back({ dir, atoi(elems[0]), elems[1] });
    });

    *part1_out = part1(prog);
    *part2_out = part2();

    return 0;
}

}
