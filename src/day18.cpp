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

struct Instr {
    char dir;
    i32 steps;
    char *color; // I think this is for part 2
};
void debug_instr(std::span<Instr> prog) {
    for (Instr &i : prog) { printf("[%c][%i] -> '%s'\n", i.dir, i.steps, i.color); }
}

struct Pos {
    i64 x;
    i64 y;
};

i64 hex_val(char c) {
    if (c == 'a') return 10;
    else if (c == 'b') return 11;
    else if (c == 'c') return 12;
    else if (c == 'd') return 13;
    else if (c == 'e') return 14;
    else if (c == 'f') return 15;
    else return c - '0';
}

i64 decode_instr_p1(Instr &i, Pos &current) {
    if (i.dir == 'R') current.x += i.steps;
    else if (i.dir == 'L') current.x -= i.steps;
    else if (i.dir == 'D') current.y += i.steps;
    else if (i.dir == 'U') current.y -= i.steps;

    return i.steps;
}
i64 decode_instr_p2(Instr &i, Pos &current) {
    char dir = i.color[strlen(i.color) - 1];
    i64 steps = 0;
    i64 base = 1;
    //printf("[INSTR] '%s'; dir=%c; ", i.color, dir);
    for (i32 j = strlen(i.color)-2; j > 0; j--) {
        //printf("%c ", i.color[j]);
        steps += hex_val(i.color[j]) * base;
        base *= 16;
    }
    //printf("; final=%lld\n", steps);

    if (dir == '0') current.x += steps;
    else if (dir == '1') current.y += steps;
    else if (dir == '2') current.x -= steps;
    else if (dir == '3') current.y -= steps;

    return steps;
}

std::vector<Pos> build_corners(std::span<Instr> prog, i64 &parameter, bool part2 = false) {
    Pos current { 0, 0 };
    std::vector<Pos> corners;
    corners.push_back(current);

    for (Instr &i : prog) {
        if (!part2) {
            parameter += decode_instr_p1(i, current);
        } else {
            parameter += decode_instr_p2(i, current);
        }
        corners.push_back(current);
    }
    return corners;
}

i64 calc_shoelace(std::vector<Pos> &corners, i64 parameter) {
    i64 calc = 0;
    for (i32 i = 0; i < corners.size() - 1; i++) {
        const Pos &p0 = corners[i + 0];
        const Pos &p1 = corners[i + 1];
        //printf("(%lld, %lld)\n", p0.x, p0.y);

        calc += (p0.x - p1.x) * (p0.y + p1.y);
    }
    return (parameter/2) + (calc/2) + 1;
}

std::string part1(std::span<Instr> prog) {
    i64 parameter = 0;
    std::vector<Pos> corners = build_corners(prog, parameter);

    return std::to_string(calc_shoelace(corners, parameter));
}

std::string part2(std::span<Instr> prog) {
    i64 parameter = 0;
    std::vector<Pos> corners = build_corners(prog, parameter, true);

    return std::to_string(calc_shoelace(corners, parameter));
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);

    std::vector<Instr> prog;
    Parse::enum_str(std::move(in), "\n", [&prog](char *token){
        char dir = *token;
        token += 2;

        char *steps;
        char *color;
        Parse::split_once(token, " ", &steps, &color);
        color++;
        color[strlen(color) - 1] = '\0';

        prog.push_back({ dir, atoi(steps), color });
    });

    *part1_out = part1(prog);
    *part2_out = part2(prog);

    return 0;
}

}
