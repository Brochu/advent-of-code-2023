#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 1
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day18_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day18.txt"
#endif // ------------------------------------

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

std::vector<Pos> build_corners(std::span<Instr> prog, float &parameter) {
    Pos current { 0, 0 };
    std::vector<Pos> corners;
    corners.push_back(current);

    for (Instr &i : prog) {
        if (i.dir == 'R') current.x += i.steps;
        else if (i.dir == 'L') current.x -= i.steps;
        else if (i.dir == 'D') current.y += i.steps;
        else if (i.dir == 'U') current.y -= i.steps;

        corners.push_back(current);
        parameter += i.steps;
    }
    return corners;
}

float calc_shoelace(std::vector<Pos> &corners, float parameter) {
    float calc = 0.f;
    for (i32 i = 0; i < corners.size() - 1; i++) {
        const Pos &p0 = corners[i + 0];
        const Pos &p1 = corners[i + 1];

        calc += (p0.x - p1.x) * (p0.y + p1.y);
    }
    return (parameter/2) + (calc/2) + 1;
}

std::string part1(std::span<Instr> prog) {
    float parameter = 0.f;
    std::vector<Pos> corners = build_corners(prog, parameter);

    return std::to_string(calc_shoelace(corners, parameter));
}

i64 part2(std::span<Instr> prog) {
    return 0;
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
    *part2_out = std::to_string(part2(prog));

    return 0;
}

}
