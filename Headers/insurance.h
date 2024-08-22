#ifndef INSURANCE_H
#define INSURANCE_H

#include "hand.h"  // Include the header where CardList is defined

#ifdef TESTING
int offer_insurance(int cash, int original_bet, int auto_accept);
#else
int offer_insurance(int cash, int original_bet);
#endif

int offer_insurance_impl(int cash, int original_bet, int auto_accept);
int check_insurance_payout(CardList *dealer_hand, int insurance_bet);

#endif // INSURANCE_H
