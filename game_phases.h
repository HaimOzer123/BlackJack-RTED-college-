#ifndef GAME_PHASES_H
#define GAME_PHASES_H

#include "game_state.h"

void betting_phase(GameState *game_state);
void initial_deal(GameState *game_state);
void blackjack_check(GameState *game_state);
void player_turn(GameState *game_state);
void dealer_turn(GameState *game_state);
void round_reset(GameState *game_state);

#endif // GAME_PHASES_H
