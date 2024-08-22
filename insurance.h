#ifndef INSURANCE_H
#define INSURANCE_H

#include "hand.h" 

int offer_insurance(int cash, int original_bet);
int check_insurance_payout(CardList *dealer_hand, int insurance_bet);

#endif
