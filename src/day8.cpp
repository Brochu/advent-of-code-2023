#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 0
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day8_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day8.txt"
#endif // ------------------------------------

enum Dir { Left, Right };
void debug_dirs(std::span<Dir> dirs) {
    printf("[INSTRUCTIONS]: ");
    for (Dir &d : dirs) {
        printf("%s, ", (d == Dir::Left) ? "Left" : "Right");
    }
    printf("\n");
}

struct Node {
    char *name;
    char *conn[2]; //0 -> left; 1 -> right
    u32 indices[2]; //0 -> left; 1 -> right
};
void debug_nodes(std::span<Node> nodes) {
    for (Node &n : nodes) {
        printf("[NODE] '%s' -> (%s[%i], %s[%i])\n", n.name, n.conn[0], n.indices[0], n.conn[1], n.indices[1]);
    }
}

std::string part1(std::span<Dir> instr, std::span<Node> nodes) {
    debug_dirs(instr);

    u32 numSteps = 0;
    Node *current = nullptr;
    for (Node &n : nodes) {
        if (strcmp(n.name, "AAA") == 0) {
            current = &n;
            break;
        }
    }

    while (strcmp(current->name, "ZZZ") != 0) {
        debug_nodes({current, 1});
        Dir pick = instr[numSteps % instr.size()];
        u32 target = current->indices[pick];
        current = &nodes[target];
        numSteps++;
    }

    return std::to_string(numSteps);
}

std::string part2(std::span<Dir> instr, std::span<Node> nodes) {
    return "NotCompleted";
}

void fetch_indices(std::span<Node> nodes){
    //TODO: Is there a better way to do this?
    for (Node &n : nodes) {
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < nodes.size(); j++) {
                if (strcmp(nodes[j].name, n.conn[i]) == 0) {
                    n.indices[i] = j;
                    break;
                }
            }
        }
    }
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<char*> docs = Parse::split_str(std::move(in), "\n\n");

    std::vector<Dir> instr;
    for (int i = 0; i < strlen(docs[0]); i++) {
        if (docs[0][i] == 'L') instr.push_back(Dir::Left);
        else if (docs[0][i] == 'R') instr.push_back(Dir::Right);
    }
    //debug_dirs(instr);

    std::vector<Node> nodes;
    std::vector<char*> nodesData = Parse::split_char(docs[1], "\n");
    for (char *nstr : nodesData) {
        std::vector<char*> elems = Parse::split_char(nstr, " = ");
        std::vector<char*> conns = Parse::split_char(elems[1], ", ");
        conns[0]++;
        conns[1][3] = '\0';
        nodes.push_back({ elems[0], {conns[0], conns[1]} });
    }
    fetch_indices(nodes);
    //debug_nodes(nodes);

    *part1_out = part1(instr, nodes);
    *part2_out = part2(instr, nodes);

    return 0;
}

}
