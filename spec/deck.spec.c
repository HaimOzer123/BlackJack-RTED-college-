#include <stdio.h>
#include <assert.h>
#include "deck.h"
#include "hand.h"
#include "card.h"

void test_fill_deck() {
    CardList deck;
    init_cardlist(&deck);
    fill_deck(&deck);
    assert(deck.len == 52);  // The deck should contain 52 cards
    clear_cardlist(&deck);
}

void test_card_draw() {
    CardList deck;
    init_cardlist(&deck);
    fill_deck(&deck);

    Card *card = card_draw(&deck);
    assert(card != NULL);  // Ensure a card is drawn
    assert(deck.len == 51);  // Deck should now have 51 cards

    card_free(card);
    clear_cardlist(&deck);
}

int deck_spec_main() {
    test_fill_deck();
    test_card_draw();
    printf("All |deck spec| tests passed!\n");
    return 0;
}
