// Haim Ozer
// Id: 316063569
// RETD - C Language For Embedded: Final project - BlackJack game
// Date: 18/08/2024 ~ 20/9/2024
// Lecturer: Shmuel

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_state.h"
#include "split.h"
#include "visuals.h"
#include "insurance.h"
#include "quitting_choice.h"

// Function to handle the betting phase
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

// Function to handle the initial dealing phase
void deal_phase(GameState *game_state) {
    card_push(&game_state->player_hand, card_draw(&game_state->deck));
    card_push(&game_state->dealer_hand, card_draw(&game_state->deck));
    card_push(&game_state->player_hand, card_draw(&game_state->deck));
    card_push(&game_state->dealer_hand, card_draw(&game_state->deck));

    printf("Dealer's hand: ");
    print_hand(&game_state->dealer_hand, 1); // Show only the first card of the dealer
    printf("Player's hand: ");
    print_hand(&game_state->player_hand, 0);
}

// Function to handle the Blackjack check phase
void blackjack_check_phase(GameState *game_state) {
    int insurance_bet = 0;
    if (get_rank_value(game_state->dealer_hand.head->data) == 1) {
        printf("Dealer shows an Ace. You can choose whether to place an insurance bet.\n");
        insurance_bet = offer_insurance(game_state->cash, game_state->pot);
        game_state->cash -= insurance_bet;

        if (insurance_bet > 0) {
            game_state->cash += check_insurance_payout(&game_state->dealer_hand, insurance_bet);
        }
    }
}

// Function to handle the hit or stand phase
int hit_or_stand_phase(GameState *game_state) {
    int player_value = calculate_hand_value(&game_state->player_hand);
    char choice[10];

    while (player_value < 21) {
        printf("Hit or Stand? ");
        scanf("%s", choice);
        while ((getchar()) != '\n'); // Flush the input buffer
        if (choice[0] == 'S' || choice[0] == 's') break;
        if (choice[0] == 'H' || choice[0] == 'h') {
            card_push(&game_state->player_hand, card_draw(&game_state->deck));
            printf("Player's hand: ");
            print_hand(&game_state->player_hand, 0);
            player_value = calculate_hand_value(&game_state->player_hand);
            if (player_value > 21) {
                print_bust();
                printf("Player's hand sum: %d\n", player_value);

                // Show the dealer's full hand after the player busts
                printf("Dealer's full hand: ");
                print_hand(&game_state->dealer_hand, 0);
                printf("Dealer's hand sum: %d\n", calculate_hand_value(&game_state->dealer_hand));
                game_state->pot = 0;

                reset_game_state(game_state);
                if (get_quitting_choice(game_state->cash)) {
                     exit(0); // Exit the game if the player chooses to quit
                }
            }
        }
    }

    return player_value;
}

// Function to handle the dealer's draw phase
void dealer_draw_phase(GameState *game_state, int player_value) {
    int dealer_value = calculate_hand_value(&game_state->dealer_hand);
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
    
    reset_game_state(game_state);

    // Check if the player wants to quit or continue
    if (get_quitting_choice(game_state->cash)) {
        exit(0); // Exit the game if the player chooses to quit
    }
}
