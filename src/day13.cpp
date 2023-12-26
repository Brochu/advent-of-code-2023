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
    std::vector<std::string> rows;
    std::vector<std::string> cols;
};
void debug_patterns(std::span<Pattern> pats) {
    for (Pattern &p : pats) {
        for (std::string & r : p.rows) {
            printf("%s\n", r.c_str());
        }
        printf("------------------\n");
        for (std::string & c : p.cols) {
            printf("%s\n", c.c_str());
        }
        printf("==================\n");
    }
}

bool check_lines(std::string &s0, std::string &s1, u32 tolerence = 0) {
    if (tolerence == 0) {
        return s0 == s1;
    } else {
        //TODO: Add details here for part 2
        return false;
    }
}

bool find_reflection(Pattern &p, usize &vpos, usize &hpos) {
    vpos = 0;
    hpos = 0;

    for (i32 i = 1; i < p.rows.size(); i++) {
        std::string &l0 = p.rows[i-1];
        std::string &l1 = p.rows[i];

        printf("%s\n%s\nequals=%s\n\n", l0.c_str(), l1.c_str(), check_lines(l0, l1) ? "YES" : "NO");
        //TODO: if we match, need to check if match correspond to a reflection line
    }

    //TODO: Need to repeat process for cols
    return true;
}

std::string part1(std::span<Pattern> pats) {
    usize total = 0;
    Pattern &p = pats[0]; {
    //for (Pattern &p : pats) {
        usize vpos = 0;
        usize hpos = 0;
        if (find_reflection(p, vpos, hpos)) {
            total += vpos;
            total += (hpos * 100);
        }
        else {
            printf("[ERR] Could not find a reflection...\n");
            debug_patterns({ &p, 1});
        }
    }
    return std::to_string(total);
}

std::string part2(std::span<Pattern> pats) {
    usize total = 0;
    //for (Pattern &p : pats) {
    //    usize pos = 0;
    //    if (find_vertical(p, pos, true)) {
    //        total += pos;
    //    }
    //    else if (find_horizontal(p, pos, true)) {
    //        total += (pos * 100);
    //    }
    //    else {
    //        printf("[ERR] Could not find a reflection...\n");
    //        debug_patterns({ &p, 1});
    //    }
    //}
    return std::to_string(total);
}

int run(std::string *part1_out, std::string *part2_out) {
    std::vector<Pattern> patterns;

    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<char*> blocks = Parse::split_str(std::move(in), "\n\n");
    for (char *b : blocks) {
        std::vector<char*> lines = Parse::split_char(b, "\n");
        std::vector<std::string> rows;
        for (i32 i = 0; i < lines.size(); i++) {
            rows.push_back({ lines[i] });
        }
        std::vector<std::string> cols;
        for (i32 i = 0; i < strlen(lines[0]); i++) {
            std::string col;
            for (i32 j = 0; j < lines.size(); j++) {
                col += lines[j][i];
            }
            cols.push_back(col);
        }
        patterns.push_back({ rows, cols });
    }

    *part1_out = part1(patterns);
    *part2_out = part2(patterns);

    return 0;
}

}
