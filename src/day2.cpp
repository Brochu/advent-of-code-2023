#include "day.h"
#include "parsing.h"

#include <iostream>
#include <span>
#include <string>
#include <vector>

namespace Solution {

void check_p1(std::span<char> token, uint64_t &count2s, uint64_t &count3s) {
    const static int8_t offset = 97;
    int8_t counts[26] = { 0 };

    for(const char &c : token) {
        //printf("%c", c);
        counts[c - offset]++;
    }
    //printf(": ");
    for(int i = 0; i < 6; i++) {
        //printf("%c -> %i,", i + offset, counts[i]);
    }
    //printf(" -- ");

    bool found2s = false;
    bool found3s = false;
    for (const int8_t &c : counts) {
        if (!found2s && c == 2){
            count2s++;
            found2s = true;
        }

        if (!found3s && c == 3) {
            count3s++;
            found3s = true;
        }

        if (found2s && found3s) break;
    }

    //printf("(%lld, %lld)\n", count2s, count3s);
}

uint8_t strdiff(const char *s1, const char *s2) {
    uint8_t diffs = 0;

    for(int i = 0; i < strlen(s1); i++) {
        if (s1[i] != s2[i]) diffs++;
    }

    return diffs;
}

std::string check_p2(std::span<char*> tokens) {
    for(int i = 0; i < tokens.size(); i++) {
        for(int j = 0; j < tokens.size(); j++) {
            if (i == j) continue;

            char *f = tokens[i];
            char *s = tokens[j];

            if (strdiff(f, s) == 1) {
                printf("%s <=> %s\n", f, s);

                std::string res = "";
                for(int i = 0; i < strlen(f); i++) {
                    if (f[i] == s[i]) res += f[i];
                }
                return res;
            }
        }
    }

    return "NotFound";
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string input = INCLUDE_STR(".\\inputs\\day2.txt");
    //std::string input = "abcdef\nbababc\nabbcde\nabcccd\naabcdd\nabcdee\nababab\n";
    //std::string input = "abcde\nfghij\nklmno\npqrst\nfguij\naxcye\nwvxyz";
    auto tokens = Parse::split_str(std::move(input));

    uint64_t count2s = 0;
    uint64_t count3s = 0;

    for(char *t : tokens) {
        check_p1(std::span{t, strlen(t)}, count2s, count3s);
    }

    *part1_out = std::to_string(count2s * count3s);
    *part2_out = check_p2(tokens);

    return 1;
}

}
