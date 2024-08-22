#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include "card.h"  // Include the implementation file

void test_get_rank_value() {
    assert(get_rank_value(0x1F) == 1);  // Ace
    assert(get_rank_value(0x2F) == 2);  // 2
    assert(get_rank_value(0xBF) == 10); // Jack
    assert(get_rank_value(0xCF) == 10); // Queen
    assert(get_rank_value(0xDF) == 10); // King
}

void test_get_suit_value() {
    assert(get_suit_value(0x01) == 1);  // Hearts
    assert(get_suit_value(0x02) == 2);  // Clubs
    assert(get_suit_value(0x04) == 3);  // Diamonds
    assert(get_suit_value(0x08) == 4);  // Spades
    assert(get_suit_value(0x00) == 0);  // Invalid suit
}

void test_get_suit_name() {
    assert(strcmp(get_suit_name(0x01), "Hearts") == 0);
    assert(strcmp(get_suit_name(0x02), "Clubs") == 0);
    assert(strcmp(get_suit_name(0x04), "Diamonds") == 0);
    assert(strcmp(get_suit_name(0x08), "Spades") == 0);
    assert(strcmp(get_suit_name(0x00), "Unknown Suit") == 0);
}

void test_print_card() {
    Card card;
    card.data = 0x1F;  // Ace of Hearts
    printf("Expected: Ace of Hearts, Got: ");
    print_card(&card);
    printf("\n");

    card.data = 0x2F;  // 2 of Hearts
    printf("Expected: 2 of Hearts, Got: ");
    print_card(&card);
    printf("\n");

    card.data = 0xBF;  // Jack of Hearts
    printf("Expected: Jack of Hearts, Got: ");
    print_card(&card);
    printf("\n");
}

int card_spec_main() {
    test_get_rank_value();
    test_get_suit_value();
    test_get_suit_name();
    test_print_card();
    printf("All |card spec| tests passed!\n");
    return 0;
}