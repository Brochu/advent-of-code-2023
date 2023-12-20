#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 0
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day19_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day19.txt"
#endif // ------------------------------------

struct Stage {
    char var;
    char op;
    u32 value;
    char *target;
};
struct Flow {
    const char *name;
    std::vector<Stage> stages;
    const char *fallback;
};
void debug_flow(Flow &flow) {
    printf("[FLOW] '%s'; fallback='%s'\n", flow.name, flow.fallback);
    for (Stage &s : flow.stages) {
        printf(" - %c %c %i -> '%s'\n", s.var, s.op, s.value, s.target);
    }
}
Flow* find_flow(std::span<Flow> flows, const char *needle) {
    for (Flow &fl : flows) {
        if (strcmp(fl.name, needle) == 0) { return &fl; }
    }
    return nullptr;
}

struct Part {
    u32 values[4]; // x, m, a, s (LOL didn't notice at first)
};
void debug_part(Part &part) {
    printf("[PART] x=%i; m=%i; a=%i; s=%i\n", part.values[0], part.values[1], part.values[2], part.values[3]);
}
usize part_value(Part &p) {
    return p.values[0] + p.values[1] + p.values[2] + p.values[3];
}

usize var_idx(char var) {
    if (var == 'x') return 0;
    if (var == 'm') return 1;
    if (var == 'a') return 2;
    if (var == 's') return 3;
    else return INT_MAX;
}

const char* apply_flow(Flow &fl, Part &p) {
    for (Stage &st : fl.stages) {
        u32 part_val = p.values[var_idx(st.var)];

        if (st.op == '<' && part_val < st.value) {
            return st.target;
        }
        else if (st.op == '>' && part_val > st.value) {
            return st.target;
        }
    }
    return fl.fallback;
}

std::string part1(std::span<Flow> flows, std::span<Part> parts) {
    usize rating = 0;

    for (Part &p : parts) {
        const char *curr = "in";
        while (strcmp(curr, "A") != 0 && strcmp(curr, "R") != 0) {
            Flow *fl = find_flow(flows, curr);
            debug_flow(*fl);

            curr = apply_flow(*fl, p);
            printf("next: '%s'\n", curr);
        }

        if (strcmp(curr, "A") == 0) {
            rating += part_value(p);
        }
    }
    return std::to_string(rating);
}

std::string part2() {
    return "NotCompleted";
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<char*> sections = Parse::split_str(std::move(in), "\n\n");

    std::vector<Flow>workflows;
    Parse::enum_char(sections[0], "\n", [&workflows](char *token){
        Flow fl;
        fl.name = token;

        while (*token != '{') { token++; }
        token[0] = '\0';
        token++;
        char *end = token;
        while (*end != '}') { end++; }
        end[0] = '\0';

        std::vector<char*> stage_str = Parse::split_char(token, ",");
        for (char *stage : stage_str) {
            if (strstr(stage, ":") != nullptr) {
                Stage s;
                s.var = *stage++;
                s.op = *stage++;
                std::vector<char*> elems = Parse::split_char(stage, ":");
                s.value = std::stoi(elems[0]);
                s.target = elems[1];
                fl.stages.push_back(s);
            } else {
                fl.fallback = stage;
            }
        }
        workflows.push_back(fl);
    });

    std::vector<Part>parts;
    Parse::enum_char(sections[1], "\n", [&parts](char *token){
        token++;
        char *end = token;
        while (*end != '}') end++;
        end[0] = '\0';

        Part p;
        std::vector<char*> vals = Parse::split_char(token, ",");
        for (u32 i = 0; i < vals.size(); i++) {
            vals[i] += 2;
            p.values[i] = std::stoi(vals[i]);
        }
        parts.push_back(p);
    });

    *part1_out = part1(workflows, parts);
    *part2_out = part2();

    return 0;
}

}
