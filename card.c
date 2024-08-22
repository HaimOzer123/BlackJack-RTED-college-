// Haim Ozer
// Id: 316063569 
// RETD - C Language For Embedded: Final project - BlackJack game 
// Date: 18/08/2024 ~ 20/9/2024 
// Lecturer: Shmuel 

//      Description:
//      The card module provides functions for creating, manipulating, and printing cards.
//      Each card is represented as a byte with the rank encoded in the upper 4 bits and the suit in the lower 4 bits.
//      The module provides functions for creating new cards, freeing cards, and extracting rank and suit information.
//      The print_card function displays the card rank and suit.



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "card.h"

Card *card_new(int rank, int suit) {
    // Validate that the suit is within the expected range (bitmask 1, 2, 4, 8)
    if (suit != HEARTS && suit != CLUBS && suit != DIAMONDS && suit != SPADES) {
        printf("Error: Invalid suit value (%d) in card_new\n", suit);
    }
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
    const char *ranks[] = {"", "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
    const char *suit_name = get_suit_name(card->data);
    printf("%s of %s", ranks[rank], suit_name);
}
