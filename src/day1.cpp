#include "day.h"
#include "parsing.h"

namespace Solution {

bool is_digit_part1(const char *t) {
    return (*t) >= '0' && (*t) <= '9';
}

bool is_digit_part2(const char *t) {
    std::string str(t);
    if (strstr(str.substr(0, 3).c_str(), "one") != NULL) { return true; }
    if (strstr(str.substr(0, 3).c_str(), "two") != NULL) { return true; }
    if (strstr(str.substr(0, 5).c_str(), "three") != NULL) { return true; }
    if (strstr(str.substr(0, 4).c_str(), "four") != NULL) { return true; }
    if (strstr(str.substr(0, 4).c_str(), "five") != NULL) { return true; }
    if (strstr(str.substr(0, 3).c_str(), "six") != NULL) { return true; }
    if (strstr(str.substr(0, 5).c_str(), "seven") != NULL) { return true; }
    if (strstr(str.substr(0, 5).c_str(), "eight") != NULL) { return true; }
    if (strstr(str.substr(0, 4).c_str(), "nine") != NULL) { return true; }

    return (*t) >= '0' && (*t) <= '9';
}

uint64_t get_digit(const char *t) {
    std::string str(t);
    if (strstr(str.substr(0, 3).c_str(), "one") != NULL) { return 1; }
    if (strstr(str.substr(0, 3).c_str(), "two") != NULL) { return 2; }
    if (strstr(str.substr(0, 5).c_str(), "three") != NULL) { return 3; }
    if (strstr(str.substr(0, 4).c_str(), "four") != NULL) { return 4; }
    if (strstr(str.substr(0, 4).c_str(), "five") != NULL) { return 5; }
    if (strstr(str.substr(0, 3).c_str(), "six") != NULL) { return 6; }
    if (strstr(str.substr(0, 5).c_str(), "seven") != NULL) { return 7; }
    if (strstr(str.substr(0, 5).c_str(), "eight") != NULL) { return 8; }
    if (strstr(str.substr(0, 4).c_str(), "nine") != NULL) { return 9; }

    if ((*t) >= '0' && (*t) <= '9') {
        return (*t) - '0';
    }

    return 0;
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string input = INCLUDE_STR(".\\inputs\\day1.txt");
    //std::string input = "1abc2\npqr3stu8vwx\na1b2c3d4e5f\ntreb7uchet\n";
    //std::string input = "two1nine\neightwothree\nabcone2threexyz\nxtwone3four\n4nineeightseven2\nzoneight234\n7pqrstsixteen\n";
    uint64_t totalp1 = 0;
    uint64_t totalp2 = 0;

    Parse::enum_str(std::move(input), "\n", [&totalp1, &totalp2](char *token) {
        size_t i = 0;
        size_t j = strlen(token) - 1;

        while(!(is_digit_part1(&token[i]) && is_digit_part1(&token[j]))) {
            if (!is_digit_part1(&token[i])) {
                i++;
            }

            if (!is_digit_part1(&token[j])) {
                j--;
            }
        }

        uint64_t first = token[i] - '0';
        uint64_t second = token[j] - '0';
        totalp1 += (first * 10) + second;

        i = 0;
        j = strlen(token) - 1;

        while(!(is_digit_part2(&token[i]) && is_digit_part2(&token[j]))) {
            if (!is_digit_part2(&token[i])) {
                i++;
            }

            if (!is_digit_part2(&token[j])) {
                j--;
            }
        }

        first = get_digit(&token[i]);
        second = get_digit(&token[j]);
        totalp2 += (first * 10) + second;
    });

    *part1_out = std::to_string(totalp1);
    *part2_out = std::to_string(totalp2);

    return 0;
}

}
