#include <assert.h>
#include <stdio.h>
#include "game_state.h"
#include "card.h"
#include "hand.h"
#include "deck.h"

void test_init_game_state() {
    GameState game_state;
    init_game_state(&game_state);

    assert(game_state.cash == 1000);
    assert(game_state.pot == 0);
    assert(game_state.deck.len == 52);

    clear_game_state(&game_state);
}

void test_reset_game_state() {
    GameState game_state;
    init_game_state(&game_state);

    // Simulate a round where the player draws a card
    card_push(&game_state.player_hand, card_draw(&game_state.deck));
    reset_game_state(&game_state);

    assert(game_state.pot == 0);
    assert(game_state.player_hand.len == 0);

    clear_game_state(&game_state);
}

int game_state_spec_main() {
    test_init_game_state();
    test_reset_game_state();
    printf("All |game state spec| tests passed!\n");
    return 0;
}
