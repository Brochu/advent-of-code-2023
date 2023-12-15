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

std::string part1(std::span<Pattern> pats) {
    //Pattern &p = pats[0];
    for (Pattern &p : pats) {
        for (usize i = 0; i < p.height; i++) {
            for (usize j = 0; j < p.width; j++) {
                printf("%c", p.data[j + (i * p.width)]);
            }
            printf("\n");
        }
        printf("------------\n");
    }

    return "NotCompleted";
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
