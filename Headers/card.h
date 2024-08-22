#ifndef CARD_H
#define CARD_H

#include <stdint.h>

#define HEARTS 0x01
#define CLUBS 0x02
#define DIAMONDS 0x04
#define SPADES 0x08

#define ACE 1
#define JACK 11
#define QUEEN 12
#define KING 13

typedef struct Card {
    uint8_t data;
    struct Card *next;
} Card;

Card *card_new(int rank, int suit);
void card_free(Card *card);
int get_rank_value(uint8_t data);
void print_card(Card *card);
int get_suit_value(uint8_t data);
const char* get_suit_name(uint8_t data);


#endif // CARD_H
