#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define WIDTH 10
//#define WIDTH 140
typedef long long int64;
typedef char* Gear;

struct Label {
    char *pos;
    int value;
    size_t size;
};

bool is_digit(const char c) {
    return c >= '0' && c <= '9';
}

bool is_included(const std::string &map, const Label &label) {
    for (char *p = label.pos; p < label.pos + label.size; p++) {
        int64 x = (p - map.c_str()) % WIDTH;
        int64 y = (p - map.c_str()) / WIDTH;

        int deltas[3] { -1, 0, 1 };

        for (int dx : deltas) {
            for (int dy : deltas) {
                if (dx == 0 && dy == 0) continue;

                int64 offset = (x + dx) + ((y + dy) * WIDTH);
                if (offset < 0 || offset >= map.size()) continue;

                if (!is_digit(map[offset]) && map[offset] != '.') {
                    return true;
                }
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
    std::string in = INCLUDE_STR(".\\inputs\\day3_demo1.txt");
    std::string map {};
    Parse::enum_str(std::move(in), "\n", [&map](char *token) {
        map.append(token);
    });

    std::vector<Label> labels;
    std::vector<Gear> gears;

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
        if (map[i] == '*') {
            gears.push_back(&map[i]);
        }
    }

    *part1_out = part1(map, labels);
    *part2_out = part2();

    return 0;
}

}
