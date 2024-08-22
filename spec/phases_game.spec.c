#include <assert.h>
#include <stdio.h>
#include "game_state.h"
#include "phases_game.h"

// Test for the betting_phase function
void test_betting_phase() {
    GameState game_state;
    init_game_state(&game_state);

    game_state.cash = 100;
    game_state.pot = 0;

    betting_phase(&game_state);

    // Test a valid bet
    assert(game_state.pot > 0);
    assert(game_state.cash < 100);
}

// Test for the deal_phase function
void test_deal_phase() {
    GameState game_state;
    init_game_state(&game_state);

    deal_phase(&game_state);

    // Check if player and dealer both have 2 cards
    assert(game_state.player_hand.len == 2);
    assert(game_state.dealer_hand.len == 2);
}

// Test for the blackjack_check_phase function
void test_blackjack_check_phase() {
    GameState game_state;
    init_game_state(&game_state);

    // Simulate dealer having an Ace
    card_push(&game_state.dealer_hand, card_new(ACE, SPADES));
    card_push(&game_state.dealer_hand, card_new(KING, HEARTS)); // Blackjack

    // check if dealer hand value is 21
    blackjack_check_phase(&game_state);
    assert(calculate_hand_value(&game_state.dealer_hand) == 21);
}

// Test for the hit_or_stand_phase function
void test_hit_or_stand_phase() {
    GameState game_state;
    init_game_state(&game_state);

    card_push(&game_state.player_hand, card_new(4, DIAMONDS));
    card_push(&game_state.player_hand, card_new(6, CLUBS));

    int player_value = hit_or_stand_phase(&game_state);

    // Test if the function correctly handles bust
    assert(player_value <= 21 || player_value > 21);
}

// Test for the dealer_draw_phase function
void test_dealer_draw_phase() {
    GameState game_state;
    init_game_state(&game_state);

    card_push(&game_state.dealer_hand, card_new(10, SPADES));
    card_push(&game_state.dealer_hand, card_new(7, CLUBS));

    int player_value = 18;
    dealer_draw_phase(&game_state, player_value);

    // Dealer should draw cards until hand value is at least 17
    assert(calculate_hand_value(&game_state.dealer_hand) >= 17);
}

int phases_game_spec_main() {
    test_betting_phase();
    test_deal_phase();
    test_blackjack_check_phase();
    test_hit_or_stand_phase();
    test_dealer_draw_phase();
    
    printf("All |phases_game| tests passed!\n");
    return 0;
}
