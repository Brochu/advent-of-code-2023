#include "day.h"
#include "parsing.h"

#include <span>

namespace Solution {

//#define WIN_COUNT 5
//#define PICK_COUNT 8
#define WIN_COUNT 10
#define PICK_COUNT 25

struct Card {
    int id;
    int winNums[WIN_COUNT];
    int pickNums[PICK_COUNT];
    int score = 0;
};

std::string part1(std::span<Card> cards) {
    size_t total = 0;

    for (Card &card : cards) {
        if (card.score > 0) {
            total += pow(2, card.score - 1);
        }
    }
    return std::to_string(total);
}

std::string part2(std::span<Card> cards) {
    int *counts = new int[cards.size()];
    // Init
    for (int i = 0; i < cards.size(); i++) {
        counts[i] = 1;
    }

    for (int i = 0; i < cards.size(); i++) {
        Card card = cards[i];
        for (int j = 1; j <= card.score; j++) {
            counts[i + j] += counts[i];
        }
    }

    size_t total = 0;
    for (int i = 0; i < cards.size(); i++) {
        total += counts[i];
    }
    delete[] counts;
    return std::to_string(total);
}

Card parse_card(char *line) {
    Card card;
    sscanf_s(line, "Card %i", &card.id);

    std::vector<char*> nums = Parse::split_char(strstr(line, ": ") + 2, " | ");
    std::vector<char*> wins = Parse::split_char(nums[0], " ");
    for (int i = 0; i < WIN_COUNT; i++) {
        card.winNums[i] = std::stoi(wins[i]);
    }
    std::vector<char*> picks = Parse::split_char(nums[1], " ");
    for (int i = 0; i < PICK_COUNT; i++) {
        card.pickNums[i] = std::stoi(picks[i]);
    }

    for (int pick : card.pickNums) {
        if (std::find(std::begin(card.winNums), std::end(card.winNums), pick) != std::end(card.winNums)) {
            card.score++;
        }
    }
    return card;
}

int run(std::string *part1_out, std::string *part2_out) {
    //std::string in = INCLUDE_STR(".\\inputs\\day4_demo1.txt");
    std::string in = INCLUDE_STR(".\\inputs\\day4.txt");
    std::vector<Card> cards;

    Parse::enum_str(std::move(in), "\n", [&cards](char *token) {
        cards.push_back(parse_card(token));
    });

    *part1_out = part1(cards);
    *part2_out = part2(cards);

    return 0;
}

}
