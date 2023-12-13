#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 0
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day12_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day12.txt"
#endif // ------------------------------------

struct Row {
    char *status;
    std::vector<u8> groups;
    usize missCount;
    usize num = 0; // To be incremented when a new valid arrangement is found
};
void debug_rows(std::span<Row> rows) {
    for (Row &r : rows) {
        printf("[%lld][%lld ?s] %s : ", r.num, r.missCount, r.status);
        for (u8 g : r.groups) {
            printf("%i ", g);
        }
        printf("\n");
    }
}

struct RowState {
    char springs[64];
    usize idx;
    usize len;
};
RowState new_state(Row & row) {
    RowState state;
    memcpy(state.springs, row.status, strlen(row.status));
    state.springs[strlen(row.status)] = '\0';
    state.idx = 0;
    state.len = strlen(row.status);
    return state;
}
RowState duplicate(RowState &rs, char spring) {
    //printf("[FROM] %s -> ", rs.springs);
    RowState newstate;
    memcpy(newstate.springs, rs.springs, rs.len);
    newstate.springs[rs.len] = '\0';
    newstate.springs[rs.idx] = spring;
    newstate.idx = rs.idx + 1;
    newstate.len = rs.len;
    //printf("[TO] %s\n", newstate.springs);
    return newstate;
}
bool is_done(RowState &rs) {
    usize questionNum = 0;
    for (int j = 0; j < rs.len; j++) {
        if (rs.springs[j] == '?') questionNum++;
    }
    return questionNum <= 0;
}

bool is_valid(Row &r, RowState &rs) {
    printf("[PERMUTATION]: %s\n", rs.springs);
    std::vector<u8> validGroups;
    u8 *current = nullptr;
    for (int i = 0; i < rs.len; i++) {
        if (rs.springs[i] == '#') {
            if (current == nullptr) {
                validGroups.push_back(0);
                current = &validGroups[validGroups.size() - 1];
            }
            (*current)++;
        }
        else if (rs.springs[i] == '.' && current != nullptr) {
            current = nullptr;
        }
    }

    if (r.groups.size() == validGroups.size()) {
        for (int i = 0; i < validGroups.size(); i++) {
            if (r.groups[i] != validGroups[i]) return false;
        }
        return true;
    }
    return false;
}

std::string part1(std::span<Row> rows) {
    for (Row &r : rows) {
        //debug_rows({ &r, 1 });
        std::vector<RowState> stack;
        stack.insert(std::begin(stack), new_state(r));

        while (!stack.empty()) {
            RowState rs = stack.back();
            stack.pop_back();
            if (is_done(rs)) {
                if (is_valid(r, rs)) {
                    //printf("%s\n", rs.springs);
                    r.num++;
                }
                continue;
            }

            if (rs.springs[rs.idx] == '?') {
                stack.insert(std::begin(stack), duplicate(rs, '.'));
                stack.insert(std::begin(stack), duplicate(rs, '#'));
            } else {
                rs.idx++;
                stack.push_back(rs);
            }

            //char transformed[strlen(rs.ref->status) + 1];
            //strcpy_s(transformed, strlen(rs.ref->status) + 1, rs.ref->status);

            // Get status with replacements
            // If no more ?'s, (NEED TO VALIDATE ANYWAY) row.num++
            // Else check next ?
            // If both '.' and '#' are possible, push both states
            // Else only add possible state
        }
    }

    usize total = 0;
    for (Row &r : rows) {
        printf("[NUM] %lld\n", r.num);
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
        usize missCount = 0;
        for (int i = 0; i < strlen(sections[0]); i++) {
            if (sections[0][i] == '?') missCount++;
        }

        std::vector<char*> groupStr = Parse::split_char(sections[1], ",");
        std::vector<u8> groups;
        for (char *c : groupStr) {
            groups.push_back(std::stoi(c));
        }
        rows.push_back({ sections[0], groups, missCount });
    });

    *part1_out = part1(rows);
    *part2_out = part2(rows);

    return 0;
}

}
