#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "card.h"

Card *card_new(int rank, int suit) {
    Card *new_card = (Card *)malloc(sizeof(Card));
    new_card->data = (rank << 4) | suit;  // Encode rank in upper 4 bits and suit in lower 4 bits
    new_card->next = NULL;
    return new_card;
}


void card_free(Card *card) {
    free(card);
}

int get_rank_value(uint8_t data) {
    int rank = data >> 4;  // Extract rank from upper 4 bits
    if (rank >= JACK) return 10;  // JACK, QUEEN, KING all count as 10
    return rank == ACE ? 1 : rank;  // ACE counts as 1
}

int get_suit_value(uint8_t data) {
    int suit = data & 0x0F;  // Extract the suit from the lower 4 bits
    switch (suit) {
        case HEARTS: return 1;
        case CLUBS: return 2;
        case DIAMONDS: return 3;
        case SPADES: return 4;
        default: return 0;  // Invalid suit
    }
}

int compare_cards(Card *card1, Card *card2) {
    return card1->data - card2->data;
}

Card *card_draw(CardList *list) {
    size_t index = rand() % list->len;
    return card_remove_at(list, index);
}

const char* get_suit_name(uint8_t data) {
    int suit = data & 0x0F;  // Extract the suit from the lower 4 bits
    switch (suit) {
        case HEARTS: return "Hearts";
        case CLUBS: return "Clubs";
        case DIAMONDS: return "Diamonds";
        case SPADES: return "Spades";
        default: return "Unknown Suit";
    }
}

void print_card(Card *card) {
    int rank = card->data >> 4;  // Extract rank from upper 4 bits
    const char *ranks[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
    const char *suit_name = get_suit_name(card->data);
    printf("%s of %s", ranks[rank], suit_name);
}
