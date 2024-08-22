// Haim Ozer
// Id: 316063569 
// RETD - C Language For Embedded: Final project - BlackJack game 
// Date: 18/08/2024 ~ 20/9/2024 
// Lecturer: Shmuel 

// Test Suite Functions for Blackjack Game
//   print_bitwise_card(Card *card):  Prints the bitwise representation of the card’s data to verify that suits and ranks are encoded correctly.
//   test_suit_encoding():  Tests if the suit is correctly encoded in the data field and properly decoded when printing.
//   test_rank_encoding():  Verifies that the ranks are correctly encoded in the data field.
//   test_linked_list_operations():   Tests basic linked list operations like drawing cards from the deck.
//   test_scoring():  Validates the correct calculation of hand values, including the special handling of Aces. 

#include <stdio.h>
#include <stdlib.h>
#include "card.h"
#include "deck.h"
#include "hand.h"

// Helper function to display the bitwise representation of a card
void print_bitwise_card(Card *card) {
    printf("Card data (bitwise): ");
    for (int i = 7; i >= 0; i--) {
        printf("%d", (card->data >> i) & 1);
    }
    printf("\n");
}

// Test function for suit encoding/decoding
void test_suit_encoding() {
    printf("\n=== Testing Suit Encoding ===\n");

    Card *hearts = card_new(1, HEARTS);
    Card *clubs = card_new(1, CLUBS);
    Card *diamonds = card_new(1, DIAMONDS);
    Card *spades = card_new(1, SPADES);

    printf("Expected: Hearts | ");
    print_card(hearts);
    print_bitwise_card(hearts);

    printf("Expected: Clubs | ");
    print_card(clubs);
    print_bitwise_card(clubs);

    printf("Expected: Diamonds | ");
    print_card(diamonds);
    print_bitwise_card(diamonds);

    printf("Expected: Spades | ");
    print_card(spades);
    print_bitwise_card(spades);

    card_free(hearts);
    card_free(clubs);
    card_free(diamonds);
    card_free(spades);
}

// Test function for rank encoding/decoding
void test_rank_encoding() {
    printf("\n=== Testing Rank Encoding ===\n");

    for (int rank = ACE; rank <= KING; rank++) {
        Card *card = card_new(rank, HEARTS);  // Use any suit for testing
        printf("Expected Rank: %d | ", rank);
        print_card(card);
        print_bitwise_card(card);
        card_free(card);
    }
}

// Test function for linked list operations
void test_linked_list_operations() {
    printf("\n=== Testing Linked List Operations ===\n");

    CardList deck;
    init_cardlist(&deck);
    fill_deck(&deck);

    printf("Deck before drawing cards:\n");
    print_hand(&deck, 0);

    Card *drawn_card1 = card_draw(&deck);
    printf("Drew a card: ");
    print_card(drawn_card1);
    printf("\nDeck after drawing one card:\n");
    print_hand(&deck, 0);

    Card *drawn_card2 = card_draw(&deck);
    printf("Drew a second card: ");
    print_card(drawn_card2);
    printf("\nDeck after drawing two cards:\n");
    print_hand(&deck, 0);

    card_free(drawn_card1);
    card_free(drawn_card2);
    clear_cardlist(&deck);
}

// Test function for scoring
void test_scoring() {
    printf("\n=== Testing Scoring ===\n");

    CardList hand;
    init_cardlist(&hand);

    card_push(&hand, card_new(ACE, HEARTS));
    card_push(&hand, card_new(KING, SPADES));
    printf("Hand with Ace and King (should be 21):\n");
    print_hand(&hand, 0);
    printf("Hand value: %d\n", calculate_hand_value(&hand));

    clear_cardlist(&hand);

    card_push(&hand, card_new(ACE, HEARTS));
    card_push(&hand, card_new(KING, SPADES));
    card_push(&hand, card_new(KING, CLUBS));
    printf("Hand with Ace, King, King (should be 21):\n");
    print_hand(&hand, 0);
    printf("Hand value: %d\n", calculate_hand_value(&hand));

    clear_cardlist(&hand);
}

int main() {
    test_suit_encoding();
    test_rank_encoding();
    test_linked_list_operations();
    test_scoring();

    return 0;
}
