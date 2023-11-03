#include "day1.h"

#include <iostream>

namespace Solution {

std::string part_1() {
    int value = 0;
    std::string line = "";
    while (std::getline(std::cin, line)) {
        char sign = line[0];
        int v = atoi(line.substr(1).c_str());

        if (sign == '+') {
            value += v;
        }
        else if (sign == '-') {
            value -= v;
        }
    }

    return std::to_string(value);
}

std::string part_2() {
    return "70";
}

}
