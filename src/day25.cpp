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

struct Machine {
    std::vector<char*> names;
    bool **mat; //TODO: Fill this based off names idx
};

usize part1(Machine &m) {
    for (char *name : m.names) {
        printf(" - '%s'\n", name);
    }
    //auto it = std::find(m.names.begin(), m.names.end(), "lsr");
    //printf(" Found 'lsr' at %s\n", *it);
    return 0;
}

usize part2(Machine &m) {
    return 0;
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    usize next_idx = 0;
    Machine m;
    Parse::enum_str(std::move(in), "\n", [&m, &next_idx](char *token){
        char *name = nullptr;
        char *rest = nullptr;
        Parse::split_once(token, ": ", &name, &rest);

        auto add = [&m](char *name){
            auto it = std::find_if(m.names.begin(), m.names.end(), [&name](char *in){
                return strcmp(name, in) == 0;
            });
            if (it == m.names.end()) {
                m.names.push_back(name);
            }
        };

        add(name);
        std::vector<char*> conns = Parse::split_char(rest, " ");
        for (char *connection : Parse::split_char(rest, " ")) {
            add(connection);
        }
    });

    *part1_out = std::to_string(part1(m));
    *part2_out = std::to_string(part2(m));

    return 0;
}

}
