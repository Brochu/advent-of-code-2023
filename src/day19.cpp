#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 1
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day19_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day19.txt"
#endif // ------------------------------------

struct Stage {
    char var;
    char op;
    int value;
    char *target;
};
struct Flow {
    char *name;
    std::vector<Stage> stages;
};
void debug_flow(Flow &flow) {
    printf("[FLOW] '%s'\n", flow.name);
    for (Stage &s : flow.stages) {
        if (s.op == '\0') {
            printf(" - -> '%s'\n", s.target);
        } else {
            printf(" - %c %c %i -> '%s'\n", s.var, s.op, s.value, s.target);
        }
    }
}

std::string part1(std::span<Flow> flows) {
    auto in = std::find_if(flows.begin(), flows.end(), [](Flow &f){ return strcmp(f.name, "in") == 0; });
    debug_flow(*in);

    usize count = 0;
    return std::to_string(count);
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
                fl.stages.push_back({ '\0', '\0', INT_MAX, stage });
            }
        }
        workflows.push_back(fl);
    });
    //printf("%s\n", sections[1]);

    *part1_out = part1(workflows);
    *part2_out = part2();

    return 0;
}

}
