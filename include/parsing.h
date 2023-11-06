#pragma once
#include <string>
#include <vector>

#define INCLUDE_STR(Path) Parse::read_file(Path)

namespace Parse {

std::string read_file(const std::string &path);
std::vector<char*> split_str(std::string &&str);

}
