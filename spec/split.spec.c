#include <assert.h>
#include <stdio.h>
#include "split.h"
#include "deck.h"
#include "deck.h" 

void test_can_split() {
    CardList hand;
    init_cardlist(&hand);

    // Add two cards with the same rank
    card_push(&hand, card_new(ACE, HEARTS));
    card_push(&hand, card_new(ACE, SPADES));

    assert(can_split(&hand) == 1);  // Should be able to split

    // Add a card with a different rank
    clear_cardlist(&hand);
    card_push(&hand, card_new(ACE, HEARTS));
    card_push(&hand, card_new(KING, SPADES));

    assert(can_split(&hand) == 0);  // Should not be able to split

    clear_cardlist(&hand);
}

void test_perform_split() {
    CardList hand, hand2, deck;
    init_cardlist(&hand);
    init_cardlist(&hand2);
    init_cardlist(&deck);
    fill_deck(&deck);

    // Add two cards with the same rank
    card_push(&hand, card_new(ACE, HEARTS));
    card_push(&hand, card_new(ACE, SPADES));

    perform_split(&hand, &hand2, &deck);

    assert(hand.len == 2);  // Both hands should have 1 card
    assert(hand2.len == 2);

    clear_cardlist(&hand);
    clear_cardlist(&hand2);
    clear_cardlist(&deck);
}

int split_spec_main() {
    test_can_split();
    test_perform_split();
    printf("All |split spec| tests passed!\n");
    return 0;
}
