// Haim Ozer
// Id: 316063569
// RETD - C Language For Embedded: Final project - BlackJack game
// Date: 18/08/2024 ~ 20/9/2024
// Lecturer: Shmuel

// Description:
// The game is played between the player and the dealer.
// The player can place bets, hit or stand, and win or lose money based on the outcome of the game.
// The game also supports splitting and insurance bets.
// The game continues until the player runs out of cash or decides to quit.
// The game is implemented using a linked list of cards for the deck, player hand, and dealer hand.
// The game logic is implemented in the play_game function, which handles the flow of the game.
// The game state is stored in a GameState struct, which contains the deck, player hand, dealer hand, cash, and pot.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game_state.h"
#include "split.h"
#include "visuals.h"
#include "insurance.h"
#include "quitting_choice.h"
#include "phases_game.h" 

void play_game()
{
    GameState game_state;
    init_game_state(&game_state);
    srand(time(NULL));

    while (1)
    {
        // Check if the player is out of cash and the pot is 0
        if (game_state.cash < 10 && game_state.pot == 0) {
            printf("Out of cash. Game Over.\n");
            break; // Exit the game loop
        }

        betting_phase(&game_state);         // Betting Phase
        deal_phase(&game_state);            // Initial Deal Phase
        blackjack_check_phase(&game_state); // Blackjack Check Phase

        int player_value = hit_or_stand_phase(&game_state); // Hit or Stand Phase

        if (player_value == -1) {
            break; // Player chose to quit
        }

        if (player_value <= 21) {
            dealer_draw_phase(&game_state, player_value); // Dealer's Draw Phase
        }

        // After the round, reset the game state before continuing
        reset_game_state(&game_state);

        // Ask the player if they want to continue or quit
        if (get_quitting_choice(game_state.cash)) {
            break;
        }

        printf("Starting a new round...\n");
    }

    clear_game_state(&game_state); // Clear the game state at the end of the game
}
