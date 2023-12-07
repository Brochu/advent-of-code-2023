#include "day.h"
#include "parsing.h"

#include <algorithm>
#include <span>

namespace Solution {

#define DEMO 1
#if DEMO == 0 // ------------------------------------
#define FILE_PATH ".\\inputs\\day7_demo1.txt"
#else // ------------------------------------
#define FILE_PATH ".\\inputs\\day7.txt"
#endif // ------------------------------------
#define HAND_COUNT 5
#define HAND_FORMAT "%c%c%c%c%c %i"
#define HAND_EXPAND(c, b) &c[0], 1, &c[1], 1, &c[2], 1, &c[3], 1, &c[4], 1, &b
#define FIND(span, val) std::find(std::begin(span), std::end(span), val) != std::end(span)

enum Type { HighCard, OnePair, TwoPairs, ThreeOfAKind, FullHouse, FourOfAKind, FiveOfAKind, };

struct Hand {
    char cards[HAND_COUNT];
    int bet;
    Type type;
};
void debug_hands(std::span<Hand> hands) {
    for (Hand &hand : hands) {
        printf("(%i)[%i] %c%c%c%c%c\n", hand.type, hand.bet, hand.cards[0], hand.cards[1], hand.cards[2], hand.cards[3], hand.cards[4]);
    }
}

int card_value(char card) {
    if (card == '2') return 2;
    else if (card == '3') return 3;
    else if (card == '4') return 4;
    else if (card == '5') return 5;
    else if (card == '6') return 6;
    else if (card == '7') return 7;
    else if (card == '8') return 8;
    else if (card == '9') return 9;
    else if (card == 'T') return 10;
    else if (card == 'J') return 11;
    else if (card == 'Q') return 12;
    else if (card == 'K') return 13;
    else if (card == 'A') return 14;
    else return -1;
}

std::string part1(std::vector<Hand> hands) {
    auto pred = [](Hand &left, Hand &right) {
        if (left.type == right.type) {
            int idx = 0;
            while (left.cards[idx] == right.cards[idx]) { idx++; }
            return card_value(left.cards[idx]) < card_value(right.cards[idx]);
        }
        return left.type < right.type;
    };
    std::sort(hands.begin(), hands.end(), pred);

    debug_hands(hands);
    u64 winnings = 0;
    for (int i = 0; i < hands.size(); i++) {
        winnings += hands[i].bet * (i + 1);
    }

    return std::to_string(winnings);;
}

std::string part2() {
    return "NotCompleted";
}

Type find_type(std::span<char> cards) {
    int counts[15] { 0 };
    for (char c : cards) {
        counts[card_value(c)]++;
    }

    if (FIND(counts, 5)) {
        return Type::FiveOfAKind;
    } else if (FIND(counts, 4)) {
        return Type::FourOfAKind;
    } else if (FIND(counts, 3)) {
        if (FIND(counts, 2)) {
            return Type::FullHouse;
        } else {
            return Type::ThreeOfAKind;
        }
    } else if (FIND(counts, 2)) {
        int pairCount = 0;
        for (int i = card_value('2'); i <= card_value('A'); i++) {
            if (counts[i] == 2) pairCount++;
        }
        if (pairCount == 2) {
            return Type::TwoPairs;
        } else {
            return Type::OnePair;
        }
    }
    return Type::HighCard;
};

std::vector<Hand> parse_hands(std::vector<char*> data) {
    std::vector<Hand> hands;

    for (char *entry : data) {
        Hand h { 0 };
        sscanf_s(entry, HAND_FORMAT, HAND_EXPAND(h.cards, h.bet));
        h.type = find_type(h.cards);
        hands.push_back(h);
    }

    return hands;
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<char*> data = Parse::split_str(std::move(in), "\n");

    std::vector<Hand> hands = parse_hands(data);

    *part1_out = part1(hands);
    *part2_out = part2();

    return 0;
}

}
