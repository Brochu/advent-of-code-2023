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

struct Input {
    usize inputidx;
    u8 offset;
};
struct Module {
    char type;
    char *name;
    char *rest; // Staging before filling in
    std::vector<usize> outputs;

    usize *state;
    usize mask;

    // Conjunctions only
    std::vector<Input> inputs;
};
struct System {
    std::vector<Module> modules;

    usize flip_states = 0;
    usize conj_states = 0;
};
void debug_system(System &sys) {
    printf("[SYSTEM]:\n");
    for (i32 i = 0; i < sys.modules.size(); i++) {
        printf(" [%i] '%s', ", i, sys.modules[i].name);
        for (usize idx : sys.modules[i].outputs) {
            printf("%lld ", idx);
        }
        if (sys.modules[i].type == '&') {
            printf(", ");
            for (Input in : sys.modules[i].inputs) {
                printf("(%lld, %i) ", in.inputidx, in.offset);
            }
        }
        printf("\n");
    }
    printf("[FLIP STATES]:");
    for (i32 i = 0; i < 64; i++) {
        usize mask = pow(2, i);
        printf("%i", (sys.flip_states & mask) ? 1 : 0);
    }
    printf("\n");
    printf("[CONJ STATES]:");
    for (i32 i = 0; i < 64; i++) {
        usize mask = pow(2, i);
        printf("%i", (sys.conj_states & mask) ? 1 : 0);
    }
    printf("\n");
    printf("[FlipFlops]:\n");
    for (Module &mod : sys.modules) {
        if (mod.type == '&' || mod.type == 'B') continue;

        printf("['%s'  STATES]:", mod.name);
        for (i32 i = 0; i < 64; i++) {
            usize mask = pow(2, i);
            printf("%i", (mod.mask & mask) ? 1 : 0);
        }
        printf("\n");
    }
    printf("[Conjunctions]:\n");
    for (Module &mod : sys.modules) {
        if (mod.type == '%' || mod.type == 'B') continue;

        printf("['%s'STATES]:", mod.name);
        for (i32 i = 0; i < 64; i++) {
            usize mask = pow(2, i);
            printf("%i", (mod.mask & mask) ? 1 : 0);
        }
        printf("\n");
    }
}

enum Power { LOW, HIGH };
struct Pulse {
    usize from;
    usize to;
    Power pow;
};

usize part1(System &sys) {
    usize lo_count = 1; // Starts at 1 to consider button press
    usize hi_count = 0;

    debug_system(sys);
    const auto pred = [](Module &in){ return in.type == 'B'; };
    usize start = std::distance(sys.modules.begin(), std::find_if(sys.modules.begin(), sys.modules.end(), pred));

    std::vector<Pulse> stack;
    usize current = 0;
    while (current < stack.size()) {
        Pulse &pulse = stack[current];
        //TODO: Process current pulse
        current++;
    }
    return lo_count * hi_count;
}

std::string part2() {
    return "NotCompleted";
}

void setup_links(System &sys) {
    //TODO: Here we search and connect modules together (save indices)
    usize flipmask = 1;
    usize conjmask = 1;

    for (Module &mod : sys.modules) {
        std::vector<char*> elems = Parse::split_char(mod.rest, ", ");
        for (char *e : elems) {
            const auto it = std::find_if(sys.modules.begin(), sys.modules.end(), [&e](Module &in){
                return strcmp(e, in.name) == 0;
            });
            mod.outputs.push_back(std::distance(sys.modules.begin(), it));
        }

        if (mod.type == '%') {
            mod.mask = flipmask;
            flipmask *= 2;
        }
        else if (mod.type == '&') {
            for (usize i = 0; i < sys.modules.size(); i++) {
                if (strstr(sys.modules[i].rest, mod.name) != nullptr) {
                    u8 offset = log2(conjmask);
                    mod.inputs.push_back({ i, offset });
                    mod.mask |= conjmask;
                    conjmask *= 2;
                }
            }
        }
    }
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

    setup_links(sys);
    *part1_out = std::to_string(part1(sys));
    *part2_out = part2();

    return 0;
}

}
