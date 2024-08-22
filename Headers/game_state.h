#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "deck.h"
#include "hand.h"

// GameState struct definition
typedef struct {
    CardList deck;
    CardList dealer_hand;
    CardList player_hand;
    CardList player_hand2;
    int cash;
    int pot;
} GameState;

// Function prototypes
void init_game_state(GameState *game_state);
void reset_game_state(GameState *game_state);
void clear_game_state(GameState *game_state);

#endif // GAME_STATE_H
