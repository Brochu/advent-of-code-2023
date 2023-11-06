#pragma once
#include <string>
#include <vector>

#define INCLUDE_STR(Path) Parse::read_file(Path)

namespace Parse {

std::string read_file(const std::string &path);
std::vector<char*> split_str(std::string &&str);

template<typename Fn>
void enum_file(const std::string &path, Fn func) {
    std::string input = INCLUDE_STR(path);

    std::vector<char*> tokens;
    char *token, *nextt = nullptr;

    token = strtok_s(input.data(), "\n", &nextt);
    while(token) {
        func(token);
        token = strtok_s(NULL, "\n", &nextt);
    }
}

}
