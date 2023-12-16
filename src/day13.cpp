#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 1
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day13_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day13.txt"
#endif // ------------------------------------

struct Pattern {
    std::string data;
    usize height;
    usize width;
};
void debug_patterns(std::span<Pattern> pats) {
    for (Pattern &p : pats) {
        for (usize i = 0; i < p.height; i++) {
            for (usize j = 0; j < p.width; j++) { printf("%c", p.data[j + (i * p.width)]); }
            printf("\n");
        }
        printf("------------\n");
    }
}

bool find_vertical(Pattern &p, usize &pos) {
    u32 cols[p.width];

    bool found = false;
    usize mirror = 0;
    for (u32 i = 0; i < p.width; i++) {
        u32 val = 0;
        for (u32 j = 0; j < p.height; j++) {
            val <<= 1;
            if (p.data[i + (j * p.width)] == '#') { val++; };
        }
        //printf("Total = %i\n", val);
        cols[i] = val;

        if (i > 0 && !found && cols[i] == cols[i - 1]) {
            //printf("Possible reflections line\n");
            found = !found;
            pos = i;
            mirror = i - 1;
        }
        else if (found && cols[i] != cols[--mirror]) {
            found = !found;
        }
        else if (found && mirror == 0) {
            break;
        }
    }
    return found;
}
bool find_horizontal(Pattern &p, usize &pos) {
    return false;
}

std::string part1(std::span<Pattern> pats) {
    usize total = 0;
    //Pattern &p = pats[0]; {
    for (Pattern &p : pats) {
        usize pos = 0;
        if (find_vertical(p, pos)) {
            total += pos;
        }
        else if (find_horizontal(p, pos)) {
            total += pos;
        }
        else {
            printf("[ERR] Could not find a reflection...");
            debug_patterns({ &p, 1});
        }
    }
    return std::to_string(total);
}

std::string part2(std::span<Pattern> pats) {
    return "NotCompleted";
}

int run(std::string *part1_out, std::string *part2_out) {
    std::vector<Pattern> patterns;

    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<char*> blocks = Parse::split_str(std::move(in), "\n\n");
    for (char *b : blocks) {
        std::vector<char*> lines = Parse::split_char(b, "\n");
        Pattern p { {}, lines.size(), strlen(lines[0]) };
        for (char *l : lines) { p.data.append(l); }
        patterns.push_back(p);
    }

    *part1_out = part1(patterns);
    *part2_out = part2(patterns);

    return 0;
}

}
