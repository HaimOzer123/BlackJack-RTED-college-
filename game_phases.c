// Haim Ozer
// Id: 316063569
// RETD - C Language For Embedded: Final project - BlackJack game
// Date: 18/08/2024 ~ 20/9/2024
// Lecturer: Shmuel

// Description:
// The game_phases module provides functions for the different phases of the game, such as betting, dealing, and playing turns.
// The module includes functions for handling the flow of the game, such as the betting phase, initial deal, and player and dealer turns.
// The game logic is implemented in these functions, which interact with the game state to update the player's hand, dealer's hand, and cash balance.
// The module also includes a function for resetting the game state at the end of each round.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game_state.h"
#include "visuals.h"
#include "game_phases.h"

void betting_phase(GameState *game_state) {
    printf("Cash: %d, Pot: %d\n", game_state->cash, game_state->pot);
    int bet = 0;
    int valid_input = 0;
    char buffer[100];

    do {
        printf("Enter bet amount (multiple of 10, up to %d): ", game_state->cash);
        if (fgets(buffer, sizeof(buffer), stdin)) {
            buffer[strcspn(buffer, "\n")] = 0;

            if (sscanf(buffer, "%d", &bet) == 1 && bet > 0 && bet <= game_state->cash && bet % 10 == 0) {
                valid_input = 1;
            } else {
                printf("Invalid bet amount. Please enter a valid multiple of 10.\n");
            }
        } else {
            clearerr(stdin);
        }
    } while (!valid_input);

    game_state->cash -= bet;
    game_state->pot += bet;
}

void initial_deal(GameState *game_state) {
    card_push(&game_state->player_hand, card_draw(&game_state->deck));
    card_push(&game_state->dealer_hand, card_draw(&game_state->deck));
    card_push(&game_state->player_hand, card_draw(&game_state->deck));
    card_push(&game_state->dealer_hand, card_draw(&game_state->deck));

    printf("Dealer's hand: ");
    print_hand(&game_state->dealer_hand, 1); // Show only the first card of the dealer
    printf("Player's hand: ");
    print_hand(&game_state->player_hand, 0);
}

void blackjack_check(GameState *game_state) {
    int player_value = calculate_hand_value(&game_state->player_hand);
    if (player_value == 21) {
        print_blackjack();
        game_state->cash += game_state->pot + (game_state->pot / 2);
        game_state->pot = 0;
        round_reset(game_state);
    }
}

void player_turn(GameState *game_state) {
    char choice[10];

    while (1) {
        int player_value = calculate_hand_value(&game_state->player_hand);  // Recalculate hand value each loop
        if (player_value >= 21) {
            break;  // Exit loop if player has 21 or more
        }
        printf("Hit or Stand? ");
        scanf("%s", choice);
        while ((getchar()) != '\n');  // Clear input buffer
        if (choice[0] == 'S' || choice[0] == 's') {
            break;
        }
        if (choice[0] == 'H' || choice[0] == 'h') {
            card_push(&game_state->player_hand, card_draw(&game_state->deck));
            printf("Player's hand: ");
            print_hand(&game_state->player_hand, 0);
            player_value = calculate_hand_value(&game_state->player_hand);  // Recalculate hand value
            if (player_value > 21) {
                print_bust();
                printf("Dealer's full hand: ");
                print_hand(&game_state->dealer_hand, 0);
                game_state->pot = 0;
                round_reset(game_state);
                return;  // Exit the function after a bust
            }
        }
    }
}


void dealer_turn(GameState *game_state) {
    int dealer_value = calculate_hand_value(&game_state->dealer_hand);
    int player_value = calculate_hand_value(&game_state->player_hand);

    if (player_value <= 21) {
        while (dealer_value < 17) {
            card_push(&game_state->dealer_hand, card_draw(&game_state->deck));
            dealer_value = calculate_hand_value(&game_state->dealer_hand);
        }

        printf("Dealer's full hand: ");
        print_hand(&game_state->dealer_hand, 0); // Show all dealer's cards

        if (dealer_value > 21) {
            print_dealer_bust();
            game_state->cash += 2 * game_state->pot;
        } else if (dealer_value > player_value) {
            print_dealer_wins();
        } else if (dealer_value < player_value) {
            print_player_wins();
            game_state->cash += 2 * game_state->pot;
        } else {
            print_tie();
            game_state->cash += game_state->pot;
        }

        printf("Player's hand sum: %d\n", player_value);
        printf("Dealer's hand sum: %d\n", dealer_value);
    }
}

void round_reset(GameState *game_state) {
    reset_game_state(game_state);
}
