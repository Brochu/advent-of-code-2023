#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define WIN_COUNT 5
#define WIN_FORMAT "%i %i %i %i %i"
#define WIN_EXPAND(a) a[0], a[1], a[2], a[3], a[4]
#define PICK_COUNT 8
#define PICK_FORMAT "%i %i %i %i %i %i %i %i"
#define PICK_EXPAND(a) a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]
//#define WIN_COUNT 10
//#define WIN_FORMAT "%i %i %i %i %i %i %i %i %i %i"
//#define WIN_EXPAND(a) a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]
//#define PICK_COUNT 25
//#define PICK_FORMAT "%i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i"
//#define PICK_EXPAND(a) a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15], a[16], a[17], a[18], a[19], a[20], a[21], a[22], a[23], a[24]

struct Card {
    int id;
    int winNums[WIN_COUNT];
    int pickNums[PICK_COUNT];
};

std::string part1(std::span<Card> cards) {
    size_t total = 0;

    for (Card &card : cards) {
        size_t count = 0;

        for (int pick : card.pickNums) {
            if (std::find(std::begin(card.winNums), std::end(card.winNums), pick) != std::end(card.winNums)) {
                count ++;
            }
        }
        if (count > 0) {
            total += pow(2, count - 1);
        }
    }
    return std::to_string(total);
}

std::string part2(std::span<Card> cards) {
    return "NotCompleted";
}

Card parse_card(char *line) {
    Card card;
    sscanf_s(line, "Card %i", &card.id);

    std::vector<char*> nums = Parse::split_char(strstr(line, ": ") + 2, " | ");
    sscanf_s(nums[0], WIN_FORMAT, WIN_EXPAND(&card.winNums));
    sscanf_s(nums[1], PICK_FORMAT, PICK_EXPAND(&card.pickNums));
    return card;
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(".\\inputs\\day4_demo1.txt");
    //std::string in = INCLUDE_STR(".\\inputs\\day4.txt");
    std::vector<Card> cards;

    Parse::enum_str(std::move(in), "\n", [&cards](char *token) {
        cards.push_back(parse_card(token));
    });

    *part1_out = part1(cards);
    *part2_out = part2(cards);

    return 0;
}

}
