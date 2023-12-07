#include "day.h"
#include "parsing.h"

#include <algorithm>
#include <span>

namespace Solution {

#define DEMO 0
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
    Type type2;
};
void debug_hands(std::span<Hand> hands) {
    for (Hand &hand : hands) {
        printf("(%i, %i)[%i] %c%c%c%c%c\n", hand.type, hand.type2,
               hand.bet,
               hand.cards[0], hand.cards[1], hand.cards[2], hand.cards[3], hand.cards[4]
       );
    }
}

int card_value(char card, bool is_p2 = false) {
    if (card >= '0' && card <= '9') return card - '0';
    else if (card == 'T') return 10;
    else if (card == 'J') return is_p2 ? 1 : 11;
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

    //debug_hands(hands);
    u64 winnings = 0;
    for (int i = 0; i < hands.size(); i++) {
        winnings += hands[i].bet * (i + 1);
    }

    return std::to_string(winnings);;
}

std::string part2(std::vector<Hand> hands) {
    auto pred = [](Hand &left, Hand &right) {
        if (left.type2 == right.type2) {
            int idx = 0;
            while (left.cards[idx] == right.cards[idx]) { idx++; }
            return card_value(left.cards[idx], true) < card_value(right.cards[idx], true);
        }
        return left.type2 < right.type2;
    };
    std::sort(hands.begin(), hands.end(), pred);

    //debug_hands(hands);
    u64 winnings = 0;
    for (int i = 0; i < hands.size(); i++) {
        winnings += hands[i].bet * (i + 1);
    }

    return std::to_string(winnings);;
}

Type find_type(std::span<char> cards) {
    int counts[15] { 0 };
    for (char c : cards) {
        counts[card_value(c)]++;
    }

    if (FIND(counts, 5)) { return Type::FiveOfAKind; }
    else if (FIND(counts, 4)) { return Type::FourOfAKind; }
    else if (FIND(counts, 3)) {
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

Type find_type_2(std::span<char> cards) {
    bool is_p2 = false;

    //TODO: Handle jokers
    int counts[15] { 0 };
    int jokers = 0;
    for (char c : cards) {
        if (c == 'J') jokers++;
        else counts[card_value(c, is_p2)]++;
    }

    for (char c : cards) {
        printf("%c ", c);
    }
    printf("\n");
    printf("jokers: %i\n", jokers);

    printf("Counts: ");
    for (int i = card_value('2', is_p2); i <= card_value('A', is_p2); i++) {
        printf("%i ", counts[i]);
    }
    printf("\n");

    if (FIND(counts, 5)) { return Type::FiveOfAKind; }
    else if (FIND(counts, 4)) { return Type::FourOfAKind; }
    else if (FIND(counts, 3)) {
        if (FIND(counts, 2)) {
            return Type::FullHouse;
        } else {
            return Type::ThreeOfAKind;
        }
    } else if (FIND(counts, 2)) {
        int pairCount = 0;
        for (int i = card_value('2', is_p2); i <= card_value('A', is_p2); i++) {
            if (counts[i] == 2) pairCount++;
        }
        if (pairCount == 2) {
            return Type::TwoPairs;
        } else {
            return Type::OnePair;
        }
    }
    return Type::HighCard;
}

std::vector<Hand> parse_hands(std::vector<char*> data) {
    std::vector<Hand> hands;

    for (char *entry : data) {
        Hand h { 0 };
        sscanf_s(entry, HAND_FORMAT, HAND_EXPAND(h.cards, h.bet));
        h.type = find_type(h.cards);
        h.type2 = find_type_2(h.cards);
        hands.push_back(h);
    }

    return hands;
}

int run(std::string *part1_out, std::string *part2_out) {
    std::string in = INCLUDE_STR(FILE_PATH);
    std::vector<char*> data = Parse::split_str(std::move(in), "\n");

    std::vector<Hand> hands = parse_hands(data);

    *part1_out = part1(hands);
    *part2_out = part2(hands);

    return 0;
}

}
