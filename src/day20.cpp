#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 0
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day20_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day20.txt"
#endif // ------------------------------------

struct Entry {
    const char *name;
    char *rest;
};
struct System {
    std::vector<Entry> data;

    std::vector<usize> flipflops;
    std::vector<usize> conjunctions;
    //store states in two u64's
};
void debug_system(System &sys) {
    printf("[SYSTEM]:\n");
    for (Entry &e : sys.data) {
        printf(" - '%s', '%s'\n", e.name, e.rest);
    }
    printf("[FLIPS (%lld)]:\n", sys.flipflops.size());
    for (usize idx : sys.flipflops) {
        printf(" - '%lld'\n", idx);
    }
    printf("[CONJC (%lld)]:\n", sys.conjunctions.size());
    for (usize idx : sys.conjunctions) {
        printf(" - '%lld'\n", idx);
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
            sys.data.push_back({ name, rest });
        } else {
            sys.data.push_back({ &name[1], rest });
            if (name[0] == '%') {
                sys.flipflops.push_back(sys.data.size() - 1);
            }
            else if (name[0] == '&') {
                sys.conjunctions.push_back(sys.data.size() - 1);
            }
        }
    });

    *part1_out = std::to_string(part1(sys));
    *part2_out = part2();

    return 0;
}

}
