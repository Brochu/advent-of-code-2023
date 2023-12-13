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
    char *status;
    std::vector<u8> groups;
    usize num = 0; // To be incremented when a new valid arrangement is found
};

struct RowState {
    usize idx;
    usize len;
    char springs[64];
};
RowState new_state(Row & row) {
    RowState state { 0, strlen(row.status) };
    memcpy(state.springs, row.status, strlen(row.status));
    state.springs[strlen(row.status)] = '\0';
    return state;
}
RowState duplicate(RowState &rs, char spring) {
    RowState newstate { rs.idx + 1, rs.len };
    memcpy(newstate.springs, rs.springs, rs.len);
    newstate.springs[rs.idx] = spring;
    newstate.springs[rs.len] = '\0';
    return newstate;
}
bool is_done(RowState &rs) {
    usize questionNum = 0;
    for (i32 j = 0; j < rs.len; j++) {
        if (rs.springs[j] == '?') questionNum++;
    }
    return questionNum <= 0;
}

bool is_valid(Row &r, RowState &rs) {
    //printf("[PERMUTATION]: %s\n", rs.springs);
    std::vector<u8> validGroups;
    u8 *current = nullptr;
    for (i32 i = 0; i < rs.len; i++) {
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
        for (i32 i = 0; i < validGroups.size(); i++) {
            if (r.groups[i] != validGroups[i]) return false;
        }
        return true;
    }
    return false;
}

std::string part1(std::span<Row> rows) {
    for (i32 i = 0; i < rows.size(); i++) {
        Row &r = rows[i];
        //printf("[NEW ROW] idx = %i\n", i);
        std::vector<RowState> stack;
        stack.insert(std::begin(stack), new_state(r));

        while (!stack.empty()) {
            RowState rs = stack.back();
            stack.pop_back();
            if (is_done(rs)) {
                if (is_valid(r, rs)) { r.num++; }
                continue;
            }

            if (rs.springs[rs.idx] == '?') {
                stack.insert(std::begin(stack), duplicate(rs, '.'));
                stack.insert(std::begin(stack), duplicate(rs, '#'));
            } else {
                rs.idx++;
                stack.push_back(rs);
            }
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
