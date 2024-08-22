// Haim Ozer
// Id: 316063569
// RETD - C Language For Embedded: Final project - BlackJack game
// Date: 18/08/2024 ~ 20/9/2024
// Lecturer: Shmuel

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game_state.h"
#include "game_phases.h"

void play_game() {
    GameState game_state;
    init_game_state(&game_state);
    srand(time(NULL));

    while (1) {
        betting_phase(&game_state);
        initial_deal(&game_state);
        blackjack_check(&game_state);
        player_turn(&game_state);
        dealer_turn(&game_state);
        round_reset(&game_state);

        if (game_state.cash < 10) {
            printf("Out of cash. Game Over.\n");
            break;
        }
    }

    clear_game_state(&game_state);
}