#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define WIDTH 10

struct Label {
    char *pos;
    int value;
    size_t size;
};

struct Symbol {
    char *pos;
    char c;
};

std::string part1(std::span<Label> labels) {
    return "NotCompleted";
}

std::string part2() {
    return "NotCompleted";
}

bool is_digit(const char c) {
    return c >= '0' && c <= '9';
}

bool is_included(const std::string &map, std::span<Label> labels) {
    return true;
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(".\\inputs\\day3_demo1.txt");
    printf("%s", in.c_str());

    std::vector<Label> labels;
    std::vector<Symbol> symbols;

    for (int i = 0; i < in.size(); i++) {
        if (is_digit(in[i])) {
            Label current { 0 };

            current.pos = &in[i];
            sscanf_s(&in[i], "%i", &current.value);

            while (is_digit(in[i])) {
                i++;
                current.size++;
            }
            labels.push_back(current);
        }
        else if (in[i] != '.' && in[i] != '\n') {
            Symbol current { 0 };
            current.pos = &in[i];
            current.c = in[i];

            symbols.push_back(current);
        }
    }

    *part1_out = part1(labels);
    *part2_out = part2();

    return 0;
}

}
