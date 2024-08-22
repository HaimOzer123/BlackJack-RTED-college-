// Haim Ozer
// Id: 316063569 
// RETD - C Language For Embedded: Final project - BlackJack game 
// Date: 18/08/2024 ~ 20/9/2024 
// Lecturer: Shmuel 

//      Description:
//      The player can split their hand if they have two cards of the same rank.
//      The second card is removed from the first hand and added to the second hand.
//      The player then draws a new card for each hand.
//      The hands are printed to the console.


#include "split.h"
#include "deck.h"
#include <stdio.h>

int can_split(CardList *hand) {
    if (hand->len == 2) {
        Card *first_card = hand->head;
        Card *second_card = first_card->next;
        
        // Extract the actual ranks (without using get_rank_value)
        int first_card_rank = first_card->data >> 4;  // Rank from upper 4 bits
        int second_card_rank = second_card->data >> 4;  // Rank from upper 4 bits
        
        // Only allow split if both cards have the same rank
        if (first_card_rank == second_card_rank) {
            return 1;  // Can split
        }
    }
    return 0; // Cannot split
}

void perform_split(CardList *hand, CardList *hand2, CardList *deck) {
    // Remove the second card from the first hand and add it to the second hand
    card_push(hand2, card_remove_at(hand, 1));
    card_push(hand, card_draw(deck));
    card_push(hand2, card_draw(deck));

    // Print the hands
    printf("Player's first hand: ");
    print_hand(hand, 0);
    printf("Player's second hand: ");
    print_hand(hand2, 0);
}
