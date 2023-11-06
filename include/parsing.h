#pragma once
#include <string>
#include <vector>

#define INCLUDE_STR(Path) Parse::read_file(Path)

namespace Parse {

std::string read_file(const std::string &path);
std::vector<char*> split_str(std::string &&str);

template<typename Fn>
void enum_str(std::string &&str, Fn func) {
    std::vector<char*> tokens;
    char *token, *nextt = nullptr;

    token = strtok_s(str.data(), "\n", &nextt);
    while(token) {
        func(token);
        token = strtok_s(NULL, "\n", &nextt);
    }
}

}
