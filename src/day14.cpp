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
#define CYCLE_COUNT 1000000000

void debug_map(std::span<std::string> lines) {
    for (std::string &s : lines) {
        printf("%s\n", s.c_str());
    }
}

usize part1(std::span<std::string> lines) {
    usize heightmap[lines[0].size()];
    for (i32 i = 0; i < lines[0].size(); i++) {
        heightmap[i] = lines.size();
    }

    usize total = 0;
    for (i32 i = 0; i < lines.size(); i++) {
        for (i32 j = 0; j < lines[i].size(); j++) {
            usize pos = lines.size() - i;

            if (lines[i][j] == 'O') {
                total += heightmap[j];
                heightmap[j]--;
            }
            else if (lines[i][j] == '#') {
                heightmap[j] = pos - 1;
            }
        }
    }
    return total;
}

void tilt_east(std::vector<std::string>& platform) {
  for (int col_idx = platform[0].size() - 1; col_idx >= 0; col_idx--) {
    for (int row_idx = 0; row_idx < platform.size(); row_idx++) {
      if (platform[row_idx][col_idx] == 'O') {
        int new_col_idx = col_idx + 1;
        while (new_col_idx < platform[0].size()) {
          if (platform[row_idx][new_col_idx] != '.') {
            new_col_idx--;
            break;
          }
          new_col_idx++;
        }
        if (new_col_idx >= platform.size()) {
          new_col_idx = platform.size() - 1;
        }
        if (col_idx != new_col_idx) {
          platform[row_idx][col_idx] = '.';
          platform[row_idx][new_col_idx] = 'O';
        }
      }
    }
  }
}

void tilt_west(std::vector<std::string>& platform) {
  for (int col_idx = 1; col_idx < platform[0].size(); col_idx++) {
    for (int row_idx = 0; row_idx < platform.size(); row_idx++) {
      if (platform[row_idx][col_idx] == 'O') {
        int new_col_idx = col_idx - 1;
        while (new_col_idx >= 0) {
          if (platform[row_idx][new_col_idx] != '.') {
            new_col_idx++;
            break;
          }
          new_col_idx--;
        }
        if (new_col_idx < 0) {
          new_col_idx = 0;
        }
        if (col_idx != new_col_idx) {
          platform[row_idx][col_idx] = '.';
          platform[row_idx][new_col_idx] = 'O';
        }
      }
    }
  }
}

void tilt_south(std::vector<std::string>& platform) {
  for (int row_idx = platform.size() - 1; row_idx >= 0; row_idx--) {
    for (int col_idx = 0; col_idx < platform[0].size(); col_idx++) {
      if (platform[row_idx][col_idx] == 'O') {
        int new_row_idx = row_idx + 1;
        while (new_row_idx < platform.size()) {
          if (platform[new_row_idx][col_idx] != '.') {
            new_row_idx--;
            break;
          }
          new_row_idx++;
        }
        if (new_row_idx >= platform.size()) {
          new_row_idx = platform.size() - 1;
        }
        if (row_idx != new_row_idx) {
          platform[row_idx][col_idx] = '.';
          platform[new_row_idx][col_idx] = 'O';
        }
      }
    }
  }
}


void tilt_north(std::vector<std::string>& platform) {
  for (int row_idx = 1; row_idx < platform.size(); row_idx++) {
    for (int col_idx = 0; col_idx < platform[0].size(); col_idx++) {
      if (platform[row_idx][col_idx] == 'O') {
        int new_row_idx = row_idx - 1;
        while (new_row_idx >= 0) {
          if (platform[new_row_idx][col_idx] != '.') {
            new_row_idx++;
            break;
          }
          new_row_idx--;
        }
        if (new_row_idx < 0) {
          new_row_idx  = 0;
        }
        if (row_idx != new_row_idx) {
          platform[row_idx][col_idx] = '.';
          platform[new_row_idx][col_idx] = 'O';
        }
      }
    }
  }
}

//TODO: Since this code was copied, I need to rewrite on my own later
std::string part2(std::vector<std::string> platform) {
    std::vector<std::vector<std::string>> cache;
      const auto check_seen_before = [&cache, & platform]() {
        for (int idx = 0; idx < cache.size(); idx++) {
          bool equal = true;
          for (int i = 0; i < platform.size() && equal; i++) {
            if (platform[i] != cache[idx][i]) {
              equal = false;
            }
          }
          if (equal) return idx;
        }
        return -1;
      };

      int first_seen_at = -1;
      int seen_again_at = -1; // kept for debug
      bool first = true;
      for (long long i = 0; i < CYCLE_COUNT; i++) {
        if (const auto idx = check_seen_before(); idx != -1) {
          first_seen_at = idx;
          // std::cout << "Found at " << first_seen_at << ", repeated at " << i << '\n';
          seen_again_at = i;
          break;
        } else {
          cache.push_back(platform);
        }
        tilt_north(platform);
        tilt_west(platform);
        tilt_south(platform);
        tilt_east(platform);
      }

      // Calculate load
      const int delta = seen_again_at - first_seen_at;
      const int idx = (CYCLE_COUNT - first_seen_at) % (delta) + first_seen_at;
      const auto& final_platform = cache[idx];
      int ans = 0;
      for (int row_idx = 0; row_idx < final_platform.size(); row_idx++) {
        for (int col_idx = 0; col_idx < final_platform[0].size(); col_idx++) {
          ans += (final_platform[row_idx][col_idx] == 'O' ? final_platform.size() - row_idx : 0);
        }
      }
    return std::to_string(ans);
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<std::string> map;
    Parse::enum_str(std::move(in), "\n", [&map](char *token){
        map.push_back({ token });
    });

    *part1_out = std::to_string(part1(map));
    *part2_out = part2(map);

    return 0;
}

}
