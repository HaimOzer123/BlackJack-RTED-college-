// Haim Ozer
// Id: 316063569 
// RETD - C Language For Embedded: Final project - BlackJack game 
// Date: 18/08/2024 ~ 20/9/2024 
// Lecturer: Shmuel 

// Test Suite for GameState Changes in Blackjack Game

#include <stdio.h>
#include <stdlib.h>
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "game_state.h" 

// Helper function to print the current state of the game
void print_gamestate(GameState *state) {
    printf("\n=== Current GameState ===\n");
    printf("Cash: %d\n", state->cash);
    printf("Pot: %d\n", state->pot);
    printf("Dealer's hand: ");
    print_hand(&(state->dealer_hand), 0);
    printf("Player's hand: ");
    print_hand(&(state->player_hand), 0);
    printf("Deck size: %d\n", state->deck.len);
    printf("========================\n");
}

// Test function to observe GameState changes
void test_gamestate_changes() {
    printf("\n=== Testing GameState Changes ===\n");

    GameState state;
    init_game_state(&state);  // Initialize the game state

    // Set initial cash
    state.cash = 1000;

    // Initial Deal Phase
    card_push(&(state.player_hand), card_draw(&(state.deck)));
    card_push(&(state.dealer_hand), card_draw(&(state.deck)));
    card_push(&(state.player_hand), card_draw(&(state.deck)));
    card_push(&(state.dealer_hand), card_draw(&(state.deck)));
    print_gamestate(&state);

    // Simulate a betting phase
    state.pot = 100;
    state.cash -= 100;
    print_gamestate(&state);

    // Simulate a player hit
    card_push(&(state.player_hand), card_draw(&(state.deck)));
    print_gamestate(&state);

    // Simulate a dealer draw
    while (calculate_hand_value(&(state.dealer_hand)) < 17) {
        card_push(&(state.dealer_hand), card_draw(&(state.deck)));
    }
    print_gamestate(&state);

    // Simulate the end of a round
    while (state.player_hand.head != NULL) {
        card_push(&(state.deck), card_remove_at(&(state.player_hand), 0));
    }
    while (state.dealer_hand.head != NULL) {
        card_push(&(state.deck), card_remove_at(&(state.dealer_hand), 0));
    }
    state.pot = 0;
    print_gamestate(&state);

    // Clean up
    clear_game_state(&state);  // Clear the game state
}

int main() {
    test_gamestate_changes();
    return 0;
}
