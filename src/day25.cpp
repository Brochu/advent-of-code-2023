#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 1
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day25_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day25.txt"
#endif // ------------------------------------

struct Component {
    char *name;
    std::vector<char*> conns;
};
struct Machine {
    std::vector<Component> cmps;
    bool **mat;
};

usize part1(Machine &m) {
    return 0;
}

usize part2(Machine &m) {
    return 0;
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    Machine m;
    Parse::enum_str(std::move(in), "\n", [&m](char *token){
        char *name = nullptr;
        char *rest = nullptr;
        Parse::split_once(token, ": ", &name, &rest);
        m.cmps.push_back({ name, Parse::split_char(rest, " ") });
    });

    *part1_out = std::to_string(part1(m));
    *part2_out = std::to_string(part2(m));

    return 0;
}

}
