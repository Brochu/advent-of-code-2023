#include "day.h"
#include "parsing.h"

#include <algorithm>
#include <iostream>
#include <span>
#include <string.h>
#include <vector>

namespace Solution {

std::string part1(std::span<int> nums) {
    int64_t total = 0;

    for (int &n : nums) {
        total += n;
    }
    return std::to_string(total);
}

std::string part2(std::span<int> nums) {
    std::vector<int64_t> cache;
    int64_t total = 0;
    int current = 0;

    for (int i = 0; i < INT_MAX; i++) {
        current = nums[i % nums.size()];
        total += current;

        auto pos = std::find(cache.begin(), cache.end(), total);
        bool found = pos != cache.end();
        if (found) {
            break;
        }
        else {
            cache.push_back(total);
        }
    }

    return std::to_string(total);
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string input = INCLUDE_STR(".\\inputs\\day1.txt");
    char *token, *nextt = nullptr;

    std::vector<int> nums;
    token = strtok_s(input.data(), "\n", &nextt);
    while(token) {
        nums.push_back(atoi(token));
        token = strtok_s(NULL, "\n", &nextt);
    }
    //int nums[5] = { 7, 7, -2, -7, -4 };

    *part1_out = part1(nums);
    *part2_out = part2(nums);

    return 0;
}

}
