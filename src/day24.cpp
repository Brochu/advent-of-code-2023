#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 1
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day24_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day24.txt"
#endif // ------------------------------------

struct Vec3 {
    double x;
    double y;
    double z;
};
void debug_vec3(Vec3 &vec) {
    printf("(%f, %f, %f)", vec.x, vec.y, vec.z);
}

struct Line {
    Vec3 sample;
    Vec3 slope;
};
void debug_line(Line &line) {
    printf("[LINE]: sample=");
    debug_vec3(line.sample);
    printf("; slope=");
    debug_vec3(line.slope);
    printf("\n");
}

usize part1(std::span<Line> hail) {
    for (Line &h : hail) {
        debug_line(h);
    }
    return 0;
}

usize part2() {
    return 0;
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<Line> hail;
    Parse::enum_str(std::move(in), "\n", [&hail](char *line){
        i64 px, py, pz;
        i64 vx, vy, vz;
        //TODO: Check why I cannot just read doubles here???
        sscanf_s(line, "%lld, %lld, %lld @ %lld, %lld, %lld", &px, &py, &pz, &vx, &vy, &vz);
        hail.push_back({ {(double)px, (double)py, (double)pz}, {(double)vx, (double)vy, (double)vz} });
    });

    *part1_out = std::to_string(part1(hail));
    *part2_out = std::to_string(part2());

    return 0;
}

}
