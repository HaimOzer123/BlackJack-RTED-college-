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

int insurance_spec_main() {
    test_offer_insurance();
    printf("All |insurance spec| tests passed!\n");
    return 0;
}
