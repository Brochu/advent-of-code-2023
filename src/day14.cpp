#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 0
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day14_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day14.txt"
#endif // ------------------------------------

std::string part1(std::span<char*> lines) {
    usize heightmap[strlen(lines[0])];
    for (i32 i = 0; i < strlen(lines[0]); i++) {
        heightmap[i] = lines.size();
    }

    usize total = 0;
    for (i32 i = 0; i < lines.size(); i++) {
        for (i32 j = 0; j < strlen(lines[i]); j++) {
            usize pos = lines.size() - i;

            if (lines[i][j] == 'O') {
                //printf("Found O at %i\n", j);
                total += heightmap[j];
                heightmap[j]--;
            }
            else if (lines[i][j] == '#') {
                //printf("Found # at %i\n", j);
                heightmap[j] = pos - 1;
            }
        }
        //printf("[HEIGHTS]: ");
        //for (i32 i = 0; i < strlen(lines[0]); i++) {
        //    printf("%lld, ", heightmap[i]);
        //}
        //printf("\n");
    }
    return std::to_string(total);
}

std::string part2(std::span<char*> lines) {
    return "NotCompleted";
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<char*> lines = Parse::split_str(std::move(in), "\n");

    *part1_out = part1(lines);
    *part2_out = part2(lines);

    return 0;
}

}
