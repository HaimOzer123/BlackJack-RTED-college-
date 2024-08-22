#ifndef PHASES_GAME_H
#define PHASES_GAME_H

void betting_phase(GameState *game_state);
void deal_phase(GameState *game_state);
void blackjack_check_phase(GameState *game_state);
int hit_or_stand_phase(GameState *game_state);
void dealer_draw_phase(GameState *game_state, int player_value);

#endif // PHASES_GAME_H
