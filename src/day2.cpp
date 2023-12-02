#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

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

size_t get_color_idx(const char *color) {
    if (strcmp(color, "red") == 0) { return 0; }
    else if (strcmp(color, "green") == 0) { return 1; }
    else if (strcmp(color, "blue") == 0) { return 2; }
    else { return INTMAX_MAX; }
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

int calc_power(const Game &game) {
    int min[3] = { 0 };

    for (const Subset &sub : game.subsets) {
        min[0] = std::max(min[0], sub.cubes[0]);
        min[1] = std::max(min[1], sub.cubes[1]);
        min[2] = std::max(min[2], sub.cubes[2]);
    }
    return min[0] * min[1] * min[2];
}

std::string part2(std::span<Game> games) {
    size_t score = 0;

    for (const Game &game : games) {
        score += calc_power(game);
    }
    return std::to_string(score);
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(".\\inputs\\day2.txt");
    std::vector<Game> games;

    Parse::enum_str(std::move(in), "\n", [&games](char *token) {
        token = (strstr(token, ": ") + 2);
        std::vector<char*> subsets = Parse::split_char(token, ";");

        std::vector<Subset> subs;
        for (char *s : subsets) {
            if (*s == ' ') { s++; };

            std::vector<char*> cubes = Parse::split_char(s, ",");

            int vals[3] = { 0 };
            for (char *c : cubes) {
                if (*c == ' ') { c++; };

                const char *color = strstr(c, " ") + 1;
                size_t idx = get_color_idx(color);
                int num = std::stoi(std::string(c).substr(0, color - c).c_str());
                vals[idx] = num;
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
