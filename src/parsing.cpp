#include "parsing.h"

#include <cassert>
#include <fstream>

namespace Parse {

std::string read_file(const std::string &path) {
    std::string content = "";

    std::ifstream file(path);
    assert(file.is_open());

    std::string line = "";
    while(std::getline(file, line)) {
        content.append(line);
        content.append("\n");
    }

    return content;
}

std::vector<char*> split_str(std::string &&str, const std::string &separator) {
    std::vector<char*> tokens;
    char *token, *nextt = nullptr;

    token = strtok_s(str.data(), separator.c_str(), &nextt);
    while(token) {
        tokens.push_back(token);
        token = strtok_s(NULL, separator.c_str(), &nextt);
    }

    return tokens;
}

}
