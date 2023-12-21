#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 1
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day20_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day20.txt"
#endif // ------------------------------------

struct Module {
    char type;
    char *name;
    char *rest;
    std::vector<usize> outputs;

    usize *state;
    usize mask;

    // UNSURE about these, should be for conjunction case
    usize start;
    std::vector<usize> inputs;
};
struct System {
    std::vector<Module> modules;

    usize flip_states;
    usize conj_states;
};
void debug_system(System &sys) {
    printf("[SYSTEM]:\n");
    for (Module &e : sys.modules) {
        printf(" - '%s', '%s'\n", e.name, e.rest);
    }
}

usize part1(System &sys) {
    usize lo_count = 1; // Starts at 1 to consider button press
    usize hi_count = 0;

    debug_system(sys);
    return lo_count * hi_count;
}

std::string part2() {
    return "NotCompleted";
}

void setup_links(System &sys) {
    //TODO: Here we search and connect modules together (save indices)
    //Check if we could setup one u64 int to store any binary states
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    System sys;
    Parse::enum_str(std::move(in), "\n", [&sys](char *token){
        char *name = nullptr;
        char *rest = nullptr;
        Parse::split_once(token, " -> ", &name, &rest);

        if (strcmp(name, "broadcaster") == 0) {
            sys.modules.push_back({ 'B', name, rest });
        } else {
            if (name[0] == '%') {
                sys.modules.push_back({ name[0], &name[1], rest, {}, &sys.flip_states });
            }
            else if (name[0] == '&') {
                sys.modules.push_back({ name[0], &name[1], rest, {}, &sys.conj_states });
            }
        }
    });

    *part1_out = std::to_string(part1(sys));
    *part2_out = part2();

    return 0;
}

}
