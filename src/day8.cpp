#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 0
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day8_demo2.txt"
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
    //debug_dirs(instr);

    u32 numSteps = 0;
    Node *current = nullptr;
    for (Node &n : nodes) {
        if (strcmp(n.name, "AAA") == 0) {
            current = &n;
            break;
        }
    }

    if (current != nullptr) {
        while (strcmp(current->name, "ZZZ") != 0) {
            //debug_nodes({current, 1});
            Dir pick = instr[numSteps % instr.size()];
            u32 target = current->indices[pick];
            current = &nodes[target];
            numSteps++;
        }
    }

    return std::to_string(numSteps);
}

bool is_done(std::span<Node*> nodes) {
    for (Node *n : nodes) {
        if (n->name[2] != 'Z') {
            return false;
        }
    }
    return true;
}

// Function to return LCM of two numbers 
u64 LCM(u64 a, u64 b) 
{ 
    u64 greater = std::max(a, b); 
    u64 smallest = std::min(a, b); 
    for (u64 i = greater; ; i += greater) { 
        if (i % smallest  == 0) 
            return i; 
    } 
} 

std::string part2(std::span<Dir> instr, std::span<Node> nodes) {
    //debug_dirs(instr);
    std::vector<Node*> current;
    for (Node &n : nodes) {
        if (n.name[2] == 'A') {
            current.push_back(&n);
            //debug_nodes({&n, 1});
        }
    }
    std::vector<u64> numSteps;
    numSteps.resize(current.size());

    for (int i = 0; i < current.size(); i++) {
        while (current[i]->name[2] != 'Z') {
            //debug_nodes({current, 1});
            Dir pick = instr[numSteps[i] % instr.size()];
            u32 target = current[i]->indices[pick];
            current[i] = &nodes[target];
            numSteps[i]++;
        }
    }

    for (u64 num : numSteps) {
        printf("%lld\n", num);
    }
    u64 res = numSteps[0];
    for (int i = 1; i < numSteps.size(); i++) {
        res = LCM(res, numSteps[i]);
    }
    return std::to_string(res);
}

void fetch_indices(Node &n, std::span<Node> nodes, u32 &leftIdx, u32 &rightIdx){
    // Find Left
    for(int i = 0; i < nodes.size(); i++) {
        if (strcmp(nodes[i].name, n.conn[0]) == 0) {
            leftIdx = i;
            break;
        }
    }

    // Find Right
    for(int i = 0; i < nodes.size(); i++) {
        if (strcmp(nodes[i].name, n.conn[1]) == 0) {
            rightIdx = i;
            break;
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
    for (Node &n : nodes) {
        u32 lIdx = 0;
        u32 rIdx = 0;
        fetch_indices(n, nodes, lIdx, rIdx);

        n.indices[0] = lIdx;
        n.indices[1] = rIdx;
    }
    //debug_nodes(nodes);

    *part1_out = part1(instr, nodes);
    *part2_out = part2(instr, nodes);

    return 0;
}

}
