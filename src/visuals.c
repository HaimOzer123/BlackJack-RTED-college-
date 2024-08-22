// Haim Ozer
// Id: 316063569 
// RETD - C Language For Embedded: Final project - BlackJack game 
// Date: 18/08/2024 ~ 20/9/2024 
// Lecturer: Shmuel 

// Description:
// The visuals are printed to the console to provide feedback to the player.

#include <stdio.h>
#include <stdlib.h> 
#include "visuals.h"

void print_blackjack() {
    printf("******************************\n");
    printf("*         BLACK JACK!        *\n");
    printf("******************************\n");
}

void print_bust() {
    printf("******************************\n");
    printf("*           BUST!            *\n");
    printf("******************************\n");
}

void print_dealer_bust() {
    printf("******************************\n");
    printf("*    DEALER BUSTS! YOU WIN!   *\n");
    printf("******************************\n");
}

void print_dealer_wins() {
    printf("******************************\n");
    printf("*       DEALER WINS!         *\n");
    printf("******************************\n");
}

void print_player_wins() {
    printf("******************************\n");
    printf("*        YOU WIN!            *\n");
    printf("******************************\n");
}

void print_tie() {
    printf("******************************\n");
    printf("*          TIE!              *\n");
    printf("******************************\n");
}
