#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 0
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day15_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day15.txt"
#endif // ------------------------------------

usize hash_algo(const char *word) {
    u64 value = 0;
    for (i32 i = 0; i < strlen(word); i++) {
        if (word[i] == '\n') continue;

        value += word[i];
        value *= 17;
        value %= 256;
        //printf("%c -> %i\n", word[i], word[i]);
    }
    return value;
}

std::string part1(std::span<char*> words) {
    usize total = 0;
    for (char *w : words) {
        usize hashed = hash_algo(w);
        total += hashed;
        //printf("[WORD] '%s' -> %lld\n", w, hashed);
    }
    return std::to_string(total);
}

std::string part2(std::span<char*> words) {
    return "NotCompleted";
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<char*> words = Parse::split_str(std::move(in), ",");

    *part1_out = part1(words);
    *part2_out = part2(words);

    return 0;
}

}
