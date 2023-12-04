#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

#define WIN_COUNT 5
#define PICK_COUNT 8

struct Card {
    int id;

    int winNums[WIN_COUNT];
    int pickNums[PICK_COUNT];
};

std::string part1(std::span<Card> cards) {
    return "NotCompleted";
}

std::string part2(std::span<Card> cards) {
    return "NotCompleted";
}

Card parse_card(char *line) {
    Card card;
    //printf("[CARD] %s\n", line);
    sscanf_s(line, "Card %i", &card.id);
    //printf("[CARD] with id = %i\n", card.id);

    std::vector<char*> nums = Parse::split_char(strstr(line, ": ") + 2, " | ");
    sscanf_s(nums[0], "%i %i %i %i %i",
             &card.winNums[0], &card.winNums[1], &card.winNums[2], &card.winNums[3], &card.winNums[4]);
    sscanf_s(nums[1], "%i %i %i %i %i %i %i %i",
             &card.pickNums[0], &card.pickNums[1], &card.pickNums[2], &card.pickNums[3], &card.pickNums[4], &card.pickNums[5], &card.pickNums[6], &card.pickNums[7]);

    //for (int win : card.winNums) {
    //    printf("[W] '%i'\n", win);
    //}
    //for (int pick : card.pickNums) {
    //    printf("[P] '%i'\n", pick);
    //}
    return card;
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(".\\inputs\\day4_demo1.txt");
    std::vector<Card> cards;

    Parse::enum_str(std::move(in), "\n", [&cards](char *token) {
        cards.push_back(parse_card(token));
    });

    *part1_out = part1(cards);
    *part2_out = part2(cards);

    return 0;
}

}
