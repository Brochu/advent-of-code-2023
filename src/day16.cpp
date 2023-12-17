#include "day.h"
#include "parsing.h"

#include <iostream>
#include <span>

namespace Solution {

#define DEMO 1
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day16_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day16.txt"
#endif // ------------------------------------

struct Pos {
    i32 x;
    i32 y;
};

enum Direction { UP, LEFT, RIGHT, DOWN };
struct Beam {
    i32 x;
    i32 y;
    Direction dir;
};

struct Map {
    char *cells;
    usize height;
    usize width;
};
Map create_map(std::string &mapStr) {
    std::vector<char*> lines = Parse::split_str(std::move(mapStr), "\n");
    usize h = lines.size();
    usize w = strlen(lines[0]);
    char *cells = new char[h * w]();
    memset(cells, 0, (h * w));

    for (i32 i = 0; i < lines.size(); i++) {
        for (i32 j = 0; j < strlen(lines[i]); j++) {
            cells[j + (i * strlen(lines[i]))] = lines[i][j];
        }
    }

    return { cells, h, w };
}
void destroy_map(Map &&map) {
    map.height = 0;
    map.width = 0;
    delete[] map.cells;
}
void debug_map(Map &map, std::vector<Pos> &energized, std::vector<Beam> &lava) {
    printf("---------------\n");
    for (i32 i = 0; i < map.height; i++) {
        for (i32 j = 0; j < map.width; j++) {
            auto lava_pos = std::find_if(lava.begin(), lava.end(), [&i, &j](const Beam &in){
                return in.x == j && in.y == i;
            });
            auto ener_pos = std::find_if(energized.begin(), energized.end(), [&i, &j](const Pos &in){
                return in.x == j && in.y == i;
            });
            if (lava_pos != lava.end()) {
                printf("*");
            }
            else if (ener_pos != energized.end()) {
                printf("#");
            }
            else {
                printf("%c", map.cells[j + (i * map.width)]);
            }
        }
        printf("\n");
    }
}

std::string part1(Map &map) {
    std::vector<Beam> beams;
    beams.push_back({ 0, 0, Direction::RIGHT });
    std::vector<Pos> energized;
    energized.push_back({ 0, 0 });

    while (!beams.empty()) {
        Beam &current = beams.back();
        beams.pop_back();

        printf("[START] beams count left = %lld; at (%i, %i)\n", beams.size(), current.x, current.y);
        debug_map(map, energized, beams);
        std::cin.ignore(1);

        //TODO: Simulate current beam
    }

    return std::to_string(energized.size());
}

std::string part2(Map &map) {
    usize energized = 0;
    return std::to_string(energized);
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    Map map = create_map(in);

    *part1_out = part1(map);
    *part2_out = part2(map);

    destroy_map(std::move(map));
    return 0;
}

}
