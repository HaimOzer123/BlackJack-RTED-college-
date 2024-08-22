// Haim Ozer
// Id: 316063569 
// RETD - C Language For Embedded: Final project - BlackJack game 
// Date: 18/08/2024 ~ 20/9/2024 
// Lecturer: Shmuel 

//      Description:
//      The hand is represented as a linked list of cards.
//      The hand value is calculated based on the rank of the cards.
//      The hand can be printed with the option to hide the second card.
//      The hand is cleared when the game is over.

#include <stdlib.h>
#include <stdio.h>
#include "hand.h"

void init_cardlist(CardList *cardlist) {
    cardlist->head = NULL;
    cardlist->len = 0;
}

void card_push(CardList *cardlist, Card *card) {
    card->next = cardlist->head;
    cardlist->head = card;
    cardlist->len++;
}

Card *card_remove_at(CardList *cardlist, size_t index) {
    if (index >= cardlist->len) return NULL;

    Card *prev = NULL;
    Card *curr = cardlist->head;

    for (size_t i = 0; i < index; i++) {
        prev = curr;
        curr = curr->next;
    }

    if (prev == NULL) {
        cardlist->head = curr->next;
    } else {
        prev->next = curr->next;
    }

    cardlist->len--;
    return curr;
}

void clear_cardlist(CardList *cardlist) {
    while (cardlist->len > 0) {
        Card *card = card_remove_at(cardlist, 0);
        card_free(card);
    }
}

int calculate_hand_value(CardList *hand) {
    int sum = 0;
    int aces = 0;
    Card *current = hand->head;

    while (current != NULL) {
        int rank_value = get_rank_value(current->data);
        if (rank_value == 1) {  // If Ace
            aces++;
            sum += 11; // Assume Ace is 11 initially
        } else {
            sum += rank_value;
        }
        current = current->next;
    }

    // Adjust for Aces if sum is greater than 21
    while (sum > 21 && aces > 0) {
        sum -= 10; // Change one Ace from 11 to 1
        aces--;
    }

    return sum;
}

void print_hand(CardList *hand, int hide_second) {
    int count = 0;
    for (Card *curr = hand->head; curr != NULL; curr = curr->next) {
        if (count == 1 && hide_second) {
            printf(" ??????");
        } else {
            print_card(curr);
        }
        if (curr->next != NULL) {
            printf(", "); // Print a comma only if there's another card
        }
        count++;
    }
    printf("\n"); // Print a newline only after all cards are printed
}

