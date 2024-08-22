#include "game_state.h"
#include <stdio.h>
#include <stdlib.h>


// Initialize the game state
void init_game_state(GameState *game_state) {
    init_cardlist(&game_state->deck);
    init_cardlist(&game_state->dealer_hand);
    init_cardlist(&game_state->player_hand);
    init_cardlist(&game_state->player_hand2);
    game_state->cash = 1000;
    game_state->pot = 0;
    fill_deck(&game_state->deck);
}

// Reset the game state after each round
void reset_game_state(GameState *game_state) {
    // Reset the game state as before
    while (game_state->player_hand.head != NULL) {
        card_push(&game_state->deck, card_remove_at(&game_state->player_hand, 0));
    }
    while (game_state->dealer_hand.head != NULL) {
        card_push(&game_state->deck, card_remove_at(&game_state->dealer_hand, 0));
    }
    
    clear_cardlist(&game_state->player_hand);
    clear_cardlist(&game_state->dealer_hand);
    game_state->pot = 0;
}



// Clear the game state when the game ends
void clear_game_state(GameState *game_state) {
    clear_cardlist(&game_state->deck);
    clear_cardlist(&game_state->dealer_hand);
    clear_cardlist(&game_state->player_hand);
    clear_cardlist(&game_state->player_hand2);
}
