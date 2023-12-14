#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 1
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day12_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day12.txt"
#endif // ------------------------------------

struct Row {
    char *springs;
    std::vector<u8> groups;
};
void print_rows(std::span<Row> rows) {
    for (Row &r : rows) {
        printf("[ROW] %s; ", r.springs);
        for (u8 g : r.groups) { printf("%i ", g); }
        printf("\n");
    }
}

usize rec_solve_row(char *str, std::span<u8> groups, usize idx) {
    printf("[REC-START] %s; %i\n", str, groups[idx]);
    if (idx >= groups.size()) {
        for (i32 i = 0; i < strlen(str); i++) {
            if (str[i] == '#') {
                printf("[REC] No more groups, found # -> return 0\n");
                return 0;
            }
        }
        printf("[REC] No more groups, no more # -> return 1\n");
        return 1;
    }
    if (strlen(str) == 0) {
        printf("[REC] Springs over, we know there are groups left -> return 0\n");
        return 0;
    }
    usize out = rec_solve_row(str+1, groups, idx);
    printf("[REC-END] %s; %i -> %lld\n", str, groups[idx], out);
    return out;
}
usize solve_row(Row &r) {
    return rec_solve_row(r.springs, r.groups, 0);
}

std::string part1(std::span<Row> rows) {
    print_rows({ &rows[0], 1 });

    usize total = 0;
    Row &r = rows[0]; {
    //for (Row &r : rows) {
        total += solve_row(r);
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
