#include <stdio.h>
#include "card.spec.c"
#include "deck.spec.c"
#include "hand.spec.c"
#include "game_state.spec.c"
#include "insurance.spec.c"
#include "split.spec.c"

int card_spec_main();
int deck_spec_main();
int hand_spec_main();
int game_state_spec_main();
int insurance_spec_main();
int split_spec_main();

int main() {
    card_spec_main();
    deck_spec_main();
    hand_spec_main();
    game_state_spec_main();
    insurance_spec_main();
    split_spec_main();

    printf("All tests passed!\n");
    return 0;
}

