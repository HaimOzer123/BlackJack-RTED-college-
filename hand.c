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
    int value = 0, ace_count = 0;
    for (Card *curr = hand->head; curr != NULL; curr = curr->next) {
        int rank_value = get_rank_value(curr->data);
        value += rank_value;
        if (rank_value == 1) ace_count++;
    }
    if (ace_count > 0 && value + 10 <= 21) value += 10;
    return value;
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

