#include "day.h"
#include "parsing.h"

#include <span>
#include <string>

namespace Solution {

#define DEMO 1
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day12_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day12.txt"
#endif // ------------------------------------

// Row read from the input
struct Row {
    char *status;
    std::vector<u8> groups;
    usize num = 0; // To be incremented when a new valid arrangement is found
};
void debug_rows(std::span<Row> rows) {
    for (Row &r : rows) {
        printf("[%lld] %s : ", r.num, r.status);
        for (u8 g : r.groups) {
            printf("%i ", g);
        }
        printf("\n");
    }
}

// Row that is currently being iterated on in the BFS algo
struct RowState {
};

std::string part1(std::span<Row> rows) {
    Row &r = rows[0]; {
    // for (Row &r : rows)
        std::vector<RowState> stack;
        while (!stack.empty()) {
            // Get status with replacements
            // If no more ?'s, (NEED TO VALIDATE ANYWAY) row.num++
            // Else check next ?
            // If both '.' and '#' are possible, push both states
            // Else only add possible state
        }
    }

    usize total = 0;
    for (Row &r : rows) {
        total += r.num;
    }
    return std::to_string(total);
}

std::string part2(std::span<Row> rows) {
    return "NotCompleted";
}

i32 run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<Row> rows;
    Parse::enum_str(std::move(in), "\n", [&rows](char *token){
        std::vector<char*> sections = Parse::split_char(token, " ");
        std::vector<char*> groupStr = Parse::split_char(sections[1], ",");
        std::vector<u8> groups;
        for (char *c : groupStr) {
            groups.push_back(std::stoi(c));
        }
        rows.push_back({ sections[0], groups });
    });

    *part1_out = part1(rows);
    *part2_out = part2(rows);

    return 0;
}

}
