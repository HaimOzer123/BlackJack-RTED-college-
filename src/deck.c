// Haim Ozer
// Id: 316063569 
// RETD - C Language For Embedded: Final project - BlackJack game 
// Date: 18/08/2024 ~ 20/9/2024 
// Lecturer: Shmuel 

//      Description:
//      The deck is represented as a linked list of cards.
//      The fill_deck function initializes the deck with all 52 cards.
//      The card_draw function randomly selects a card from the deck and removes it.
//      The deck is shuffled by randomly selecting a card from the deck and moving it to the end.
//      The deck is reshuffled when it runs out of cards.
//      The deck is freed when the game is over.

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
