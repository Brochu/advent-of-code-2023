#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define DEMO 0
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day2_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day2.txt"
#endif // ------------------------------------

struct Subset {
    int cubes[3];

    Subset(int red, int green, int blue) {
        cubes[0] = red;
        cubes[1] = green;
        cubes[2] = blue;
    }
};

struct Game {
    size_t id;
    std::vector<Subset> subsets;
};

void debug(std::span<Game> games) {
    for (const Game &g : games) {
        printf("[GAME] id: %lld, size(): %lld\n", g.id, g.subsets.size());
        for (const Subset &s : g.subsets) {
            printf("\t[SUBSET] RED: %i, GREEN: %i, BLUE: %i\n", s.cubes[0], s.cubes[1], s.cubes[2]);
        }
    }
}

bool is_possible(int max[3], const Game &game) {
    for (const Subset &sub : game.subsets) {
        if (sub.cubes[0] > max[0]) { return false; }
        else if (sub.cubes[1] > max[1]) { return false; }
        else if (sub.cubes[2] > max[2]) { return false; }
    }

    return true;
}

std::string part1(std::span<Game> games) {
    int max[3] = { 12, 13, 14 };
    size_t result = 0;
    for (const Game &game : games) {
        if (is_possible(max, game)) {
            result += game.id;
        }
    }
    return std::to_string(result);
}

std::string part2(std::span<Game> games) {
    size_t score = 0;

    for (const Game &game : games) {
        int min[3] = { 0 };

        for (const Subset &sub : game.subsets) {
            min[0] = std::max(min[0], sub.cubes[0]);
            min[1] = std::max(min[1], sub.cubes[1]);
            min[2] = std::max(min[2], sub.cubes[2]);
        }
        score += min[0] * min[1] * min[2];
    }
    return std::to_string(score);
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<Game> games;

    Parse::enum_str(std::move(in), "\n", [&games](char *token) {
        token = (strstr(token, ": ") + 2);
        std::vector<char*> subsets = Parse::split_char(token, "; ");

        std::vector<Subset> subs;
        for (char *s : subsets) {
            std::vector<char*> cubes = Parse::split_char(s, ", ");

            int vals[3] = { 0 };
            for (char *c : cubes) {
                int num = 0; char color;
                sscanf_s(c, "%i %c", &num, &color, 1);
                vals[color % 3] = num;
            }
            subs.emplace_back(vals[0], vals[1], vals[2]);
        }
        games.push_back({ games.size() + 1, subs });
    });

    *part1_out = part1(games);
    *part2_out = part2(games);

    return 0;
}

}
