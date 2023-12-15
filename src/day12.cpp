#include "day.h"
#include "parsing.h"

#include <map>
#include <span>
#include <sstream>

namespace Solution {

#define DEMO 0
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day12_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day12.txt"
#endif // ------------------------------------

std::vector<std::string> split(std::string source, std::string delim)
{
    std::vector<std::string> result;

    size_t start = 0;
    size_t end = source.find(delim);
    while (end != std::string::npos)
    {
        auto sub = source.substr(start, end - start);
        result.push_back(sub);

        start = end + delim.length();
        end   = source.find(delim, start);
    }

    auto sub = source.substr(start, end - start);
    result.push_back(sub);

    return result;
}

bool matches2(const std::string& input, size_t pos, size_t len)
{
    // Ensure that the preceding character can be a . (need . or ?)
    if ((pos > 0) && (input[pos-1] == '#')) return false;
    // Can't match if the group overruns the input
    if ((pos + len) > input.size()) return false;
    // Ensure that the group items can all be # (need # or ?)
    for (int i = 0; i < len; ++i) if (input[pos+i] == '.') return false;   
    // If we are the end of the input there is no need for a following .
    if ((pos + len) == input.size()) return true;
    // Ensure that the following character can be a . (need . or ?)
    return (input[pos + len] != '#');
}


// After a day of barking up the wrong tree I remembered that memoising is a good solution.
// I really must get this technique into my regular vocabulary.
using Memo    = std::pair<size_t, size_t>;
using MemoMap = std::map<Memo, size_t>;


size_t calculate(const std::string& input, const std::vector<size_t>& groups, size_t pos, size_t grp, MemoMap& memo_map)
{
    Memo memo = std::make_pair(pos, grp);
    if (memo_map.find(memo) != memo_map.end()) return memo_map[memo];

    if (grp >= groups.size())
    {
        for (auto p = pos; p < input.size(); p++)
            if (input[p] == '#') return 0;
        return 1;
    }

    size_t result = 0;
    while (pos < input.size())
    {
        if (matches2(input, pos, groups[grp]))
        {
            result += calculate(input, groups, pos + groups[grp] + 1, grp + 1, memo_map);
        }

        if (input[pos] == '#') break;
        ++pos;
    }

    memo_map[memo] = result;
    return result;
}

size_t calculate(const std::string& s0, const std::string& s1)
{
    auto t = split(s1, ",");

    std::vector<size_t> groups;
    for (auto c: t) { groups.push_back(stoi(c)); }
    auto corrupt = s0 + ".";

    MemoMap memo_map;
    return calculate(corrupt, groups, 0, 0, memo_map);
}

template <typename T>
auto part1(const T& lines)
{
    size_t result = 0;
    for (std::string line: lines)
    {
        if (line.size() == 0) continue;

        auto s  = split(line, " ");
        auto s0 = s[0];
        auto s1 = s[1];
        result += calculate(s0, s1);    
    }    

    return result;
}


template <typename T>
auto part2(T& lines)
{
    size_t result = 0;
    for (auto line: lines)
    {
        if (line.size() == 0) continue;

        auto s  = split(line, " ");
        auto s0 = s[0] + "?" + s[0] + "?" + s[0] + "?" + s[0] + "?" + s[0];
        auto s1 = s[1] + "," + s[1] + "," + s[1] + "," + s[1] + "," + s[1];
        result += calculate(s0, s1);    
    }    

    return result;
}

i32 run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<std::string> lines = split(in, "\n");

    *part1_out = std::to_string(part1(lines));
    *part2_out = std::to_string(part2(lines));

    return 0;
}

}
