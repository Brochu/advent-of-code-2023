#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 0
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day1_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day1.txt"
#endif // ------------------------------------

int get_digit(const char *t) {
    std::string str(t);
    if (strcmp(str.substr(0, 3).c_str(), "one")   == 0) { return 1; }
    if (strcmp(str.substr(0, 3).c_str(), "two")   == 0) { return 2; }
    if (strcmp(str.substr(0, 5).c_str(), "three") == 0) { return 3; }
    if (strcmp(str.substr(0, 4).c_str(), "four")  == 0) { return 4; }
    if (strcmp(str.substr(0, 4).c_str(), "five")  == 0) { return 5; }
    if (strcmp(str.substr(0, 3).c_str(), "six")   == 0) { return 6; }
    if (strcmp(str.substr(0, 5).c_str(), "seven") == 0) { return 7; }
    if (strcmp(str.substr(0, 5).c_str(), "eight") == 0) { return 8; }
    if (strcmp(str.substr(0, 4).c_str(), "nine")  == 0) { return 9; }

    if ((*t) >= '0' && (*t) <= '9') {
        return (*t) - '0';
    }

    return 0;
}

bool is_digit_part1(const char *t) {
    return (*t) >= '0' && (*t) <= '9';
}

std::string part1(std::span<char*> tokens) {
    int total = 0;
    for (const char *token : tokens) {
        size_t i = 0, j = strlen(token) - 1;

        while(!(is_digit_part1(&token[i]) && is_digit_part1(&token[j]))) {
            if (!is_digit_part1(&token[i])) { i++; }
            if (!is_digit_part1(&token[j])) { j--; }
        }

        int first = get_digit(&token[i]);
        int second = get_digit(&token[j]);
        total += (first * 10) + second;
    }

    return std::to_string(total);
}

bool is_digit_part2(const char *t) {
    return get_digit(t) != 0;
}

std::string part2(std::span<char*> tokens) {
    int total = 0;
    for (const char *token : tokens) {
        size_t i = 0, j = strlen(token) - 1;

        while(!(is_digit_part2(&token[i]) && is_digit_part2(&token[j]))) {
            if (!is_digit_part2(&token[i])) { i++; }
            if (!is_digit_part2(&token[j])) { j--; }
        }

        int first = get_digit(&token[i]);
        int second = get_digit(&token[j]);
        total += (first * 10) + second;
    };

    return std::to_string(total);
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string input = INCLUDE_STR(FILE_PATH);
    std::vector<char*> tokens = Parse::split_str(std::move(input), "\n");

    *part1_out = part1(tokens);
    *part2_out = part2(tokens);

    return 0;
}

}
