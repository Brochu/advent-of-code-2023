#include "day.h"
#include "parsing.h"

namespace Solution {

#define DEMO 0
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day20_demo2.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day20.txt"
#endif // ------------------------------------

enum Power { LOW, HIGH };
struct Input {
    usize inputidx;
    Power pow;
};
struct Module {
    char type;
    char *name;
    std::vector<char*> outstr;
    std::vector<usize> outputs;

    usize *state;
    usize mask;

    // Conjunctions only
    std::vector<Input> inputs;
};
struct System {
    std::vector<Module> modules;
    usize flip_states = 0;
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
                printf("(%lld, %s) ", in.inputidx, in.pow == Power::LOW ? "LOW" : "HIGH");
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

        printf("['%s'  STATES]:", mod.name);
        for (i32 i = 0; i < 64; i++) {
            usize mask = pow(2, i);
            printf("%i", (mod.mask & mask) ? 1 : 0);
        }
        printf("\n");
    }
}

bool check_conjunction(Module &conj) {
    for (Input &in : conj.inputs) {
        if (in.pow != Power::HIGH) { return false; }
    }
    return true;
}

struct Pulse {
    usize from;
    usize to;
    Power pow;
    const char *to_name;
};

struct CacheEntry {
    usize key;
    usize lo_pulses;
    usize hi_pulses;
    usize out;
};

usize part1(System &sys, std::string &part2) {
    usize lo_total = 0;
    usize hi_total = 0;

    const auto pred = [](Module &in){ return in.type == 'B'; };
    usize start = std::distance(sys.modules.begin(), std::find_if(sys.modules.begin(), sys.modules.end(), pred));

    for (i32 i = 0; i < 1000; i++) {
        usize lo_count = 0;
        usize hi_count = 0;

        std::vector<Pulse> stack;
        stack.push_back({ INT_MAX, start, Power::LOW, "" }); // BUTTON PUSHED

        usize current = 0;
        while (current < stack.size()) {
            Pulse pulse = stack[current];
            if (pulse.pow == Power::LOW) lo_count++;
            else if (pulse.pow == Power::HIGH) hi_count++;
            if (pulse.to >= sys.modules.size()) {
                const char * pname = pulse.pow == Power::LOW ? "LOW" : "HIGH";

                if (pulse.pow == Power::LOW) {
                    printf("[WOW] Trying to send pulse to invalid module? i=%i name=%s power=%s\n", i, pulse.to_name, pname);
                }
                current++;
                continue;
            }

            Module &mod = sys.modules[pulse.to];
            if (mod.type == 'B') { // BCAST
                for (i32 i = 0; i < mod.outputs.size(); i++) {
                    stack.push_back({ pulse.to, mod.outputs[i], pulse.pow, mod.outstr[i] });
                }
            }
            else if (mod.type == '%'){ // FLIPFLOP
                if (pulse.pow == Power::LOW) {
                    bool ison = (sys.flip_states & mod.mask) == mod.mask;
                    sys.flip_states ^= mod.mask;
                    for (i32 i = 0; i < mod.outputs.size(); i++) {
                        stack.push_back({ pulse.to, mod.outputs[i], ison ? LOW : HIGH, mod.outstr[i] });
                    }
                }
            }
            else if (mod.type == '&'){ // CONJUNCTION
                for (Input &in : mod.inputs) {
                    if (in.inputidx == pulse.from) {
                        in.pow = pulse.pow;
                        break;
                    }
                }
                Power newpow = check_conjunction(mod) ? Power::LOW : Power::HIGH;
                for (i32 i = 0; i < mod.outputs.size(); i++) {
                    stack.push_back({ pulse.to, mod.outputs[i], newpow, mod.outstr[i] });
                }
            }
            current++;
        }

        //printf("PULSES:\n");
        //for (Pulse &p : stack) {
        //    printf("(%lld) -%s-> (%lld)\n", p.from, p.pow == Power::HIGH ? "HIGH" : "LOW", p.to);
        //}

        //debug_system(sys);
        lo_total += lo_count;
        hi_total += hi_count;
        //std::cin.ignore(1);
    }
    printf("lo_total=%lld; hi_total=%lld:\n", lo_total, hi_total);
    part2 = "2020";
    return lo_total * hi_total;
}

void setup_links(System &sys) {
    usize flipcount = 0;
    usize conjcount = 0;
    usize inpcount = 0;

    usize flipmask = 1;
    usize conjmask = 1;

    for (Module &mod : sys.modules) {
        for (char *e : mod.outstr) {
            const auto it = std::find_if(sys.modules.begin(), sys.modules.end(), [&e](Module &in){
                return strcmp(e, in.name) == 0;
            });
            mod.outputs.push_back(std::distance(sys.modules.begin(), it));
        }

        if (mod.type == '%') {
            mod.mask = flipmask;
            flipmask *= 2;
            flipcount++;
        }
        else if (mod.type == '&') {
            for (usize i = 0; i < sys.modules.size(); i++) {
                const Module &curr = sys.modules[i];
                auto it = std::find_if(curr.outstr.begin(), curr.outstr.end(), [&mod](char *out){
                    return strcmp(mod.name, out) == 0;
                });
                if (it != curr.outstr.end()) {
                    u8 offset = log2(conjmask);
                    mod.inputs.push_back({ i, Power::LOW });
                    mod.mask |= conjmask;
                    conjmask *= 2;
                    conjcount++;
                    inpcount += curr.outstr.size();
                }
            }
        }
    }

    printf("FLIP: %lld; CONJ: %lld; INPUT: %lld\n", flipcount, conjcount, inpcount);
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    System sys;
    Parse::enum_str(std::move(in), "\n", [&sys](char *token){
        char *name = nullptr;
        char *rest = nullptr;
        Parse::split_once(token, " -> ", &name, &rest);

        if (strcmp(name, "broadcaster") == 0) {
            sys.modules.push_back({ 'B', name, Parse::split_char(rest, ", ") });
        } else {
            if (name[0] == '%') {
                sys.modules.push_back({ name[0], &name[1], Parse::split_char(rest, ", "), {}, &sys.flip_states });
            }
            else if (name[0] == '&') {
                sys.modules.push_back({ name[0], &name[1], Parse::split_char(rest, ", "), {}, nullptr });
            }
        }
    });

    setup_links(sys);
    *part1_out = std::to_string(part1(sys, *part2_out));

    return 0;
}
}
