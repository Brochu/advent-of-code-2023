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

bool can_match(char *sub, char next, usize group) {
    printf("[MATCH] %s, %c, %lld\n", sub, next, group);
    return false;
}

usize solve_row(Row &r) {
    const usize H = r.groups.size() + 1;
    const usize W = strlen(r.springs) + 1;
    usize D[H][W];
    memset(D, 0, sizeof(usize) * W * H);
    D[0][0] = 1;

    for (i32 i = 1; i < H; i++) {
        for (i32 j = 0; j < strlen(r.springs); j++) {
            char c = r.springs[j];
            usize g = r.groups[i - 1];
            printf("(%i, %i) = (%c, %lld)\n", i, j, c, g);

            if (c == '.') {
                D[i][j + 1] = D[i][j];
            }
            else if (c == '#') {
                if ((strlen(r.springs) - j) < g) {
                    D[i][j + 1] = 0;
                } else {
                    char sub[g + 1];
                    memcpy(sub, &r.springs[j], g);
                    sub[g] = '\0';

                    char next = '.';
                    if ((j + g) < strlen(r.springs)) { next = r.springs[j + g]; }
                    if (can_match(sub, next, g)) {
                    }
                }
            }
        }
    }

    for (i32 i = 0; i < H; i++) {
        for (i32 j = 0; j < W; j++) {
            printf("%lld ", D[i][j]);
        }
        printf("\n");
    }
    return 0;
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
