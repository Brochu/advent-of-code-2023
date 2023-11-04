#include "day.h"

#include <algorithm>
#include <iostream>
#include <span>
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
    std::vector<int> nums;
    std::string line = "";

    while(std::getline(std::cin, line)) {
        nums.push_back(atoi(line.c_str()));
    }

    *part1_out = part1(nums);
    *part2_out = part2(nums);

    return 0;
}

}
