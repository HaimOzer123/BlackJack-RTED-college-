// Haim Ozer
// Id: 316063569
// RETD - C Language For Embedded: Final project - BlackJack game
// Date: 18/08/2024 ~ 20/9/2024
// Lecturer: Shmuel

// Description:
// The game is played between the player and the dealer.
// The player can place bets, hit or stand, and win or lose money based on the outcome of the game.
// The game also supports splitting and insurance bets.
// The game continues until the player runs out of cash or decides to quit.
// The game is implemented using a linked list of cards for the deck, player hand, and dealer hand.
// The game logic is implemented in the play_game function, which handles the flow of the game.
// The game is played in the console with text-based visuals to provide feedback to the player.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game_state.h"
#include "split.h"
#include "visuals.h"
#include "insurance.h"
#include "quitting_choice.h"

void play_game()
{
    // Initialize the game state
    GameState game_state;
    init_game_state(&game_state);
    srand(time(NULL));

    while (1)
    {
        // Betting Phase
        printf("Cash: %d, Pot: %d\n", game_state.cash, game_state.pot);
        if (game_state.pot == 0 && game_state.cash < 10)
        {
            printf("Out of cash. Game Over.\n");
            break;
        }

        int bet = 0;
        int valid_input = 0;
        char buffer[100];
        do
        {
            printf("Enter bet amount (multiple of 10, up to %d): ", game_state.cash);
            if (fgets(buffer, sizeof(buffer), stdin))
            {
                buffer[strcspn(buffer, "\n")] = 0;

                if (sscanf(buffer, "%d", &bet) == 1 && bet > 0 && bet <= game_state.cash && bet % 10 == 0)
                {
                    valid_input = 1;
                }
                else
                {
                    printf("Invalid bet amount. Please enter a valid multiple of 10.\n");
                }
            }
            else
            {
                clearerr(stdin);
            }
        } while (!valid_input);

        game_state.cash -= bet;
        game_state.pot += bet;

        // Initial Deal Phase
        card_push(&game_state.player_hand, card_draw(&game_state.deck));
        card_push(&game_state.dealer_hand, card_draw(&game_state.deck));
        card_push(&game_state.player_hand, card_draw(&game_state.deck));
        card_push(&game_state.dealer_hand, card_draw(&game_state.deck));
        // print dealers hand and players hand
        printf("Dealer's hand: ");
        print_hand(&game_state.dealer_hand, 1); // Show only the first card of the dealer
        printf("Player's hand: ");
        print_hand(&game_state.player_hand, 0);

        // Blackjack Check Phase
        int insurance_bet = 0;
        if (get_rank_value(game_state.dealer_hand.head->data) == 1)
        {
            printf("Dealer shows an Ace. You can choose whether to place an insurance bet.\n");
            insurance_bet = offer_insurance(game_state.cash, bet);
            game_state.cash -= insurance_bet;

            if (insurance_bet > 0)
            {
                game_state.cash += check_insurance_payout(&game_state.dealer_hand, insurance_bet);
            }
        }

        // Check if the player can split
        if (can_split(&game_state.player_hand))
        {
            char choice[10];
            printf("You have two cards of the same value. Do you want to split? (y/n): ");
            scanf("%s", choice);
            while ((getchar()) != '\n')
                ; // Flush the input buffer
            if (choice[0] == 'Y' || choice[0] == 'y')
            {
                perform_split(&game_state.player_hand, &game_state.player_hand2, &game_state.deck);
            }
        }

        int player_value = calculate_hand_value(&game_state.player_hand);
        if (player_value == 21)
        {
            print_blackjack();
            game_state.cash += game_state.pot + (game_state.pot / 2);
            game_state.pot = 0;
            printf("Player's hand sum: %d\n", player_value);
            printf("Dealer's hand sum: %d\n", calculate_hand_value(&game_state.dealer_hand));

            // Reset Cards Phase
            reset_game_state(&game_state);

            // Check if the player wants to quit or continue
            if (get_quitting_choice(game_state.cash))
            {
                break;
            }

            continue;
        }

        // Hit or Stand Phase
        char choice[10];
        while (player_value < 21)
        {
            printf("Hit or Stand? ");
            scanf("%s", choice);
            while ((getchar()) != '\n')
                ; // Flush the input buffer
            if (choice[0] == 'S' || choice[0] == 's')
                break;
            if (choice[0] == 'H' || choice[0] == 'h')
            {
                card_push(&game_state.player_hand, card_draw(&game_state.deck));
                printf("Player's hand: ");
                print_hand(&game_state.player_hand, 0);
                player_value = calculate_hand_value(&game_state.player_hand);
                if (player_value > 21)
                {
                    print_bust();
                    printf("Player's hand sum: %d\n", player_value);

                    // Show the dealer's full hand after the player busts
                    printf("Dealer's full hand: ");
                    print_hand(&game_state.dealer_hand, 0);

                    printf("Dealer's hand sum: %d\n", calculate_hand_value(&game_state.dealer_hand));
                    game_state.pot = 0;

                    reset_game_state(&game_state);

                    break; // Exit this round, no need to ask for quit here
                }
            }
        }

        // Dealer's Draw Phase
        if (player_value <= 21)
        {
            int dealer_value = calculate_hand_value(&game_state.dealer_hand);
            while (dealer_value < 17)
            {
                card_push(&game_state.dealer_hand, card_draw(&game_state.deck));
                dealer_value = calculate_hand_value(&game_state.dealer_hand);
            }

            printf("Dealer's full hand: ");
            print_hand(&game_state.dealer_hand, 0); // Show all dealer's cards

            if (dealer_value > 21)
            {
                print_dealer_bust();
                game_state.cash += 2 * game_state.pot;
            }
            else if (dealer_value > player_value)
            {
                print_dealer_wins();
            }
            else if (dealer_value < player_value)
            {
                print_player_wins();
                game_state.cash += 2 * game_state.pot;
            }
            else
            {
                print_tie();
                game_state.cash += game_state.pot;
            }

            printf("Player's hand sum: %d\n", player_value);
            printf("Dealer's hand sum: %d\n", dealer_value);
        }

        // Reset Cards Phase
        reset_game_state(&game_state);

        // Check if the player wants to quit or continue
        if (get_quitting_choice(game_state.cash))
        {
            break;
        }
    }

    clear_game_state(&game_state); // clear the game state at the end of the game
}
