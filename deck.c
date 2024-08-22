#include <stdlib.h> 
#include "deck.h"
#include "card.h"
#include "hand.h"

void fill_deck(CardList *deck) {
    const int suits[] = {HEARTS, CLUBS, DIAMONDS, SPADES};
    for (int suit = 0; suit < 4; suit++) {
        for (int rank = ACE; rank <= KING; rank++) {
            Card *card = card_new(rank, suits[suit]);
            card_push(deck, card);
        }
    }
}

Card *card_draw(CardList *deck) {
    if (deck->len == 0) return NULL;
    size_t index = rand() % deck->len;
    return card_remove_at(deck, index);
}
