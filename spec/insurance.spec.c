#include <assert.h>
#include <stdio.h>
#include "insurance.h"
#include "hand.h"

void test_offer_insurance() {
    int cash = 100;
    int original_bet = 10;
    int auto_accept = 1;

    // Player has enough cash to afford insurance
    int insurance_bet = offer_insurance(cash, original_bet, auto_accept);
    assert(insurance_bet == 10);  // Insurance bet is half of the original bet

    // Player does not have enough cash to afford insurance
    cash = 4;
    insurance_bet = offer_insurance(cash, original_bet, auto_accept);
    assert(insurance_bet == 0);  // No insurance bet

    // Check if player chose not to accept insurance
    auto_accept = 0;
    insurance_bet = offer_insurance(cash, original_bet, auto_accept);
    assert(insurance_bet == 0);  // No insurance bet
}

void test_check_insurance_payout() {
    CardList dealer_hand;
    init_cardlist(&dealer_hand);

    // Dealer has Blackjack
    card_push(&dealer_hand, card_new(ACE, SPADES));  // Ace
    card_push(&dealer_hand, card_new(KING, HEARTS)); // 10-value card

    int payout = check_insurance_payout(&dealer_hand, 10);
    assert(payout == 20);  // Insurance pays 2:1

    // Dealer does not have Blackjack
    clear_cardlist(&dealer_hand);
    card_push(&dealer_hand, card_new(ACE, SPADES));
    card_push(&dealer_hand, card_new(9, HEARTS)); // Non-10-value card

    payout = check_insurance_payout(&dealer_hand, 10);
    assert(payout == 0);  // No payout

    clear_cardlist(&dealer_hand);
}

int insurance_spec_main() {
    test_offer_insurance();
    test_check_insurance_payout();
    printf("All |insurance spec| tests passed!\n");
    return 0;
}
