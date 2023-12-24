#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 0
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day24_demo1.txt"
#define MIN_COORD 7
#define MAX_COORD 27
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day24.txt"
#define MIN_COORD 200000000000000
#define MAX_COORD 400000000000000
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
    usize count = 0;

    //i32 i = 0; {
    for (i32 i = 0; i < hail.size(); i++) {
        //i32 j = 1; {
        for (i32 j = i; j < hail.size(); j++) {
            if (j == i) continue;

            Line &l0 = hail[i];
            const double m0 = (double)l0.slope.y / l0.slope.x;
            const double b0 = l0.sample.y - (m0 * l0.sample.x);
            //printf("[LINE 0] m=%f, b=%f\n", m0, b0);
            Line &l1 = hail[j];
            const double m1 = (double)l1.slope.y / l1.slope.x;
            const double b1 = l1.sample.y - (m1 * l1.sample.x);
            //printf("[LINE 1] m=%f, b=%f\n", m1, b1);

            if (m0 - m1 == 0) {
                //printf("[CROSS] INVALID, Won't cross...\n");
                continue;
            }
            const double x = (b1 - b0) / (m0 - m1);
            const double y = (m0 * x) + b0;
            //printf("[CROSS] x=%f; y=%f\n", x, y);
            //printf("[LIMITS] MIN=%i; MAX=%i\n", MIN_COORD, MAX_COORD);

            bool in_range = x >= MIN_COORD && x <= MAX_COORD && y >= MIN_COORD && y <= MAX_COORD;
            bool in_apast = l0.slope.x < 0 ? x > l0.sample.x : x < l0.sample.x;
            bool in_bpast = l1.slope.x < 0 ? x > l1.sample.x : x < l1.sample.x;
            //printf("[COND] in_range=%i; apast=%i; bpast=%i\n", in_range, in_apast, in_bpast);
            if (in_range && !in_apast && !in_bpast) {
                count++;
            }
        }
    }
    return count;
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
