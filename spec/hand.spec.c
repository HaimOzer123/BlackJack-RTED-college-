#include <stdio.h>
#include <assert.h>
#include "hand.h"
#include "card.h"


void test_card_push() {
    CardList hand;
    init_cardlist(&hand);

    Card *card = card_new(ACE, HEARTS);
    card_push(&hand, card);
    assert(hand.len == 1);
    assert(hand.head == card);

    clear_cardlist(&hand);
}

void test_card_remove_at() {
    CardList hand;
    init_cardlist(&hand);

    Card *card1 = card_new(ACE, HEARTS);
    Card *card2 = card_new(KING, SPADES);
    card_push(&hand, card1);
    card_push(&hand, card2);

    Card *removed_card = card_remove_at(&hand, 1);
    assert(removed_card == card1);
    assert(hand.len == 1);

    card_free(removed_card);
    clear_cardlist(&hand);
}

void test_calculate_hand_value() {
    CardList hand;
    init_cardlist(&hand);

    card_push(&hand, card_new(ACE, HEARTS));
    card_push(&hand, card_new(KING, SPADES));

    int value = calculate_hand_value(&hand);
    assert(value == 21);

    clear_cardlist(&hand);
}

int hand_spec_main() {
    test_card_push();
    test_card_remove_at();
    test_calculate_hand_value();
    printf("All |hand spec| tests passed!\n");
    return 0;
}
