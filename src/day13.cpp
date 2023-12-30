#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 0
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day13_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day13.txt"
#endif // ------------------------------------
#define SMUDGE_TARGET 1

typedef std::vector<std::string> Pattern;

int countDifferingCharacters(const std::string& str1, const std::string& str2) {
    int count = 0;
    for (int i = 0; i < str1.length(); i++) {
        if (str1[i] != str2[i]) {
            count++;
        }
    }

    return count;
}

int findMirror(std::vector<std::string> &group) {
    for (int split = 1; split < group.size(); split++) {
        int size = std::min(split, (int)group.size() - split);
        
        int smudgeCount = 0;
        for (int y = 0; y < size; y++) {
            std::string side1 = group[split - 1 - y];
            std::string side2 = group[split + y];
            smudgeCount += countDifferingCharacters(side1, side2);
        }
        if (smudgeCount == SMUDGE_TARGET) {
            return split;
        }
    }
    return 0;
}

std::vector<std::string> rotate(std::vector<std::string> &group) {
    std::vector<std::string> ret;

    int width = group[0].length();
    for (int i = 0; i < width; i++) {
        std::string s = "";

        for (int j = 0; j < group.size(); j++) {
            s += group[group.size() - j -1][i];
        }
        
        ret.push_back(s);
    }

    return ret;
}

u64 getScore(std::vector<std::string> &group) {
    u64 ret = findMirror(group) * 100;
    std::vector<std::string> rotated = rotate(group);
    ret += findMirror(rotated);

    return ret;
}

u64 part1(std::span<Pattern> pats) {
    u64 total = 0;
    for (Pattern &p : pats) {
        total += getScore(p);
    }
    return total;
}

u64 part2(std::span<Pattern> pats) {
    u64 total = 0;
    for (Pattern &p : pats) {
        total += getScore(p);
    }
    return total;
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
        patterns.push_back(rows);
    }

    *part1_out = std::to_string(part1(patterns));
    *part2_out = std::to_string(part2(patterns));

    return 0;
}

}
