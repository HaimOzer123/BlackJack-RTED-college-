#ifndef HAND_H
#define HAND_H

#include "card.h" 

typedef struct {
    Card *head;
    size_t len;
} CardList;

void init_cardlist(CardList *cardlist);
void card_push(CardList *cardlist, Card *card);
Card *card_remove_at(CardList *cardlist, size_t index);
void clear_cardlist(CardList *cardlist);
int calculate_hand_value(CardList *hand);
void print_hand(CardList *hand, int hide_second);

#endif
