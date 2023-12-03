#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define WIDTH 140
typedef long long int64;

struct Label {
    char *pos;
    int value;
    size_t size;
};

struct Symbol {
    char *pos;
    char c;
};

bool is_digit(const char c) {
    return c >= '0' && c <= '9';
}

bool is_included(const std::string &map, const Label &label) {
    for (char *p = label.pos; p < label.pos + label.size; p++) {
        int64 range[8];

        int64 offset = p - map.c_str();
        int64 x = offset % WIDTH;
        int64 y = offset / WIDTH;

        range[0] = (x - 1) + ((y - 1) * WIDTH);
        range[1] = (x - 0) + ((y - 1) * WIDTH);
        range[2] = (x + 1) + ((y - 1) * WIDTH);

        range[3] = (x - 1) + ((y - 0) * WIDTH);
        range[4] = (x + 1) + ((y - 0) * WIDTH);

        range[5] = (x - 1) + ((y + 1) * WIDTH);
        range[6] = (x - 0) + ((y + 1) * WIDTH);
        range[7] = (x + 1) + ((y + 1) * WIDTH);

        for (int i = 0; i < 8; i++) {
            if (range[i] < 0 || range[i] >= map.size()) continue;

            if (!is_digit(map[range[i]]) && map[range[i]] != '.') {
                return true;
            }
        }
    }

    return false;
}

std::string part1(const std::string &map, std::span<Label> labels) {
    int64 total = 0;

    for (const Label &label : labels) {
        if (is_included(map, label)) { total += label.value; }
    }
    return std::to_string(total);
}

std::string part2() {
    return "NotCompleted";
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(".\\inputs\\day3.txt");
    std::string map {};
    Parse::enum_str(std::move(in), "\n", [&map](char *token) {
        map.append(token);
    });

    std::vector<Label> labels;
    std::vector<Symbol> symbols;

    for (int i = 0; i < map.size(); i++) {
        if (is_digit(map[i])) {
            Label current { 0 };

            current.pos = &map[i];
            sscanf_s(&map[i], "%i", &current.value);

            while (is_digit(map[i])) {
                i++;
                current.size++;
            }
            labels.push_back(current);
        }
        if (map[i] != '.') {
            Symbol current { 0 };
            current.pos = &map[i];
            current.c = map[i];

            symbols.push_back(current);
        }
    }

    *part1_out = part1(map, labels);
    *part2_out = part2();

    return 0;
}

}
