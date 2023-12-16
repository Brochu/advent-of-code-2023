#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 1
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day15_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day15.txt"
#endif // ------------------------------------

struct Lens {
    char label[256];
    u8 focus;
};

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
    std::vector<Lens> boxes[256];
    usize result = 0;

    //char *word = words[0]; {
    for (char *word : words) {
        usize count = 0;
        while (word[count] != '=' && word[count] != '-') { count++; }
        Lens l;
        memcpy(l.label, word, count);
        l.label[count] = '\0';
        usize idx = hash_algo(l.label);

        char op = word[count];
        if (word[count] == '=') {
            l.focus = word[count + 1] - '0';
            printf("[ADD] label: %s (%lld), focus: %i\n", l.label, idx, l.focus);
            std::vector<Lens> &box = boxes[idx];
            auto pos = std::find_if(box.begin(), box.end(), [&l](const Lens &in){
                return strcmp(in.label, l.label) == 0;
            });
            if (pos == box.end()) {
                box.insert(box.end(), l);
            } else {
                (*pos).focus = l.focus;
            }
        }
        else if (word[count] == '-') {
            printf("[DEL] label: %s (%lld)\n", l.label, idx);
            std::vector<Lens> &box = boxes[idx];
            auto pos = std::find_if(box.begin(), box.end(), [&l](const Lens &in){
                return strcmp(in.label, l.label) == 0;
            });
            if (pos != box.end()) {
                box.erase(pos);
            }
        }
    }

    for (i32 i = 0; i < 256; i++) {
        if (boxes[i].size() > 0) {
            printf("[BOX %i] > ", i);
            for (Lens &l : boxes[i]) {
                printf("(%s, %i) ", l.label, l.focus);
            }
            printf("\n");
        }
    }

    return std::to_string(result);
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<char*> words = Parse::split_str(std::move(in), ",");

    *part1_out = part1(words);
    *part2_out = part2(words);

    return 0;
}

}
