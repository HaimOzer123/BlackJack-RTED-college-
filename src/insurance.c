// Haim Ozer
// Id: 316063569 
// RETD - C Language For Embedded: Final project - BlackJack game 
// Date: 18/08/2024 ~ 20/9/2024 
// Lecturer: Shmuel 

//      Description:
//      The player can choose to take insurance when the dealer shows an Ace.
//      If the dealer has Blackjack, the insurance bet pays 2:1.
//      Otherwise, the player loses the insurance bet.


#include <stdio.h>
#include "insurance.h"
#include "hand.h"  

#ifdef TESTING
int offer_insurance(int cash, int original_bet, int auto_accept) {
    return offer_insurance_impl(cash, original_bet, auto_accept);
}
#else
int offer_insurance(int cash, int original_bet) {
    return offer_insurance_impl(cash, original_bet, 0);  // auto_accept is always 0 in production
}
#endif

int offer_insurance_impl(int cash, int original_bet, int auto_accept) {
    int insurance_bet = 0;

    if (cash >= original_bet / 2) {
        if (auto_accept == 1) {
            // Auto-accept insurance bet, skip input
            insurance_bet = original_bet / 2;
        } else {
            // Log or print to verify that the function reaches this point
            printf("Prompting user for input...\n");

            // Prompt the player for input
            char choice[10];
            printf("Dealer shows an Ace. Do you want to take insurance? [y/n]: ");
            scanf("%s", choice);
            if (choice[0] == 'Y' || choice[0] == 'y') {
                // Calculate the insurance bet
                insurance_bet = original_bet / 2;
            }
        }

        // Check if the insurance bet is not a multiple of 10
        if (insurance_bet % 10 != 0) {
            int uneven_amount = insurance_bet % 10;
            insurance_bet = (insurance_bet / 10 + 1) * 10;
            printf("The insurance bet was uneven by %d. It has been rounded up to the nearest multiple of 10.\n", uneven_amount);
            printf("The current insurance bet is now %d.\n", insurance_bet);
        } else if (insurance_bet > 0) {
            printf("You placed an insurance bet of %d.\n", insurance_bet);
        }
    } else {
        printf("Not enough cash for insurance.\n");
    }
    
    return insurance_bet;
}

int check_insurance_payout(CardList *dealer_hand, int insurance_bet) {
    int dealer_value = calculate_hand_value(dealer_hand);

    // Check if dealer's hand is a Blackjack
    if (dealer_value == 21 && get_rank_value(dealer_hand->head->next->data) == 10) {
        printf("Dealer has Blackjack! Insurance bet pays 2:1.\n");
        return 2 * insurance_bet;
    } else {
        printf("Dealer does not have Blackjack. You lose the insurance bet.\n");
        return 0;
    }
}
