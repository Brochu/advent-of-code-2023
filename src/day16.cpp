#include "day.h"
#include "parsing.h"

#include <iostream>
#include <span>

namespace Solution {

#define DEMO 0
#if DEMO == 1 // ------------------------------------
#define FILE_PATH ".\\inputs\\day16_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day16.txt"
#endif // ------------------------------------
#define FOUND(l, n) (std::find(std::begin(l), std::end(l), n) != std::end(l))

enum Direction { UP, LEFT, RIGHT, DOWN };
struct Beam {
    i32 x;
    i32 y;
    Direction dir;
};
bool contains_beam(std::span<Beam> beams, Beam &needle) {
    return std::find_if(beams.begin(), beams.end(), [&needle](Beam &in){
        return in.x == needle.x && in.y == needle.y && in.dir == needle.dir;
    }) != beams.end();
}

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
void debug_map(Map &map, std::vector<usize> &energized, Beam &beam) {
    printf("---------------\n");
    for (i32 i = 0; i < map.height; i++) {
        for (i32 j = 0; j < map.width; j++) {
            const usize offset = j + (i * map.width);
            if (beam.x == j && beam.y == i) {
                if (beam.dir == UP) printf("^");
                else if (beam.dir == LEFT) printf("<");
                else if (beam.dir == RIGHT) printf(">");
                else if (beam.dir == DOWN) printf("v");
            }
            else if (FOUND(energized, offset)) { printf("#"); }
            else { printf("%c", map.cells[j + (i * map.width)]); }
        }
        printf("\n");
    }
}

std::string part1(Map &map) {
    std::vector<Beam> beams;
    std::vector<usize> energized;
    std::vector<Beam> history;
    beams.push_back({ 0, 0, Direction::RIGHT });
    history.push_back(beams.back());

    while (!beams.empty()) {
        Beam beam = beams.back();
        beams.pop_back();
        printf("[START BEAM] at (%i, %i), %lld left, energized count: %lld\n", beam.x, beam.y, beams.size(), energized.size());

        while (beam.x >= 0 && beam.x < map.width && beam.y >= 0 && beam.y < map.height)
        {
            printf("[BEAM BEFORE] at (%i, %i), %lld left\n", beam.x, beam.y, beams.size());
            //debug_map(map, energized, beam);
            //std::cin.ignore(1);

            const usize offset = beam.x + (beam.y * map.width);
            if (!FOUND(energized, offset)) { energized.push_back(offset); }

            char c = map.cells[beam.x + (beam.y * map.width)];
            if (c == '|') {
                if (beam.dir == UP) { beam.y--; }
                else if (beam.dir == DOWN) { beam.y++; }
                else if (beam.dir == RIGHT || beam.dir == LEFT) {
                    beams.push_back({ beam.x, beam.y - 1, UP });
                    beam.y++;
                    beam.dir = DOWN;
                }
            }
            else if (c == '-') {
                if (beam.dir == LEFT) { beam.x--; }
                else if (beam.dir == RIGHT) { beam.x++; }
                else if (beam.dir == UP || beam.dir == DOWN) {
                    beams.push_back({ beam.x - 1, beam.y, LEFT });
                    beam.x++;
                    beam.dir = RIGHT;
                }
            }
            else if (c == '/') {
                if (beam.dir == UP) { beam.x++; beam.dir = RIGHT; }
                else if (beam.dir == LEFT) { beam.y++; beam.dir = DOWN; }
                else if (beam.dir == RIGHT) { beam.y--, beam.dir = UP; }
                else if (beam.dir == DOWN) { beam.x--, beam.dir = LEFT; }
            }
            else if (c == '\\') {
                if (beam.dir == UP) { beam.x--; beam.dir = LEFT; }
                else if (beam.dir == LEFT) { beam.y--; beam.dir = UP; }
                else if (beam.dir == RIGHT) { beam.y++, beam.dir = DOWN; }
                else if (beam.dir == DOWN) { beam.x++, beam.dir = RIGHT; }
            }
            else {
                if (beam.dir == UP) beam.y--;
                else if (beam.dir == DOWN) beam.y++;
                else if (beam.dir == LEFT) beam.x--;
                else if (beam.dir == RIGHT) beam.x++;
            }

            if (contains_beam(history, beam)) { break; }
            history.push_back(beam);
            printf("[BEAM AFTER] at (%i, %i)\n", beam.x, beam.y);
        }
    }
    Beam dud { 0, 0, RIGHT };
    //debug_map(map, energized, dud);

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
