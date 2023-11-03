#pragma once
#include <string>

#define INCLUDE_STR(Path) Parse::read_file(Path)

namespace Parse {
    std::string read_file(const std::string& path);
}
