#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game_state.h"

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

        // Show dealer's first card and player's hand
        printf("Dealer's hand: ");
        print_hand(&game_state.dealer_hand, 1); // Show only the first card of the dealer
        printf("Player's hand: ");
        print_hand(&game_state.player_hand, 0);

        int player_value = calculate_hand_value(&game_state.player_hand);
        if (player_value == 21)
        {
            printf("Blackjack!\n");
            game_state.cash += game_state.pot + (game_state.pot / 2);
            game_state.pot = 0;

            // Reset Cards Phase
            reset_game_state(&game_state);

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
                    printf("Bust! You lose.\n");

                    // Show the dealer's full hand after the player busts
                    printf("Dealer's full hand: ");
                    print_hand(&game_state.dealer_hand, 0);

                    game_state.pot = 0;

                    reset_game_state(&game_state);

                    break; // Exit this round
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
                printf("Dealer busts! You win.\n");
                game_state.cash += 2 * game_state.pot;
            }
            else if (dealer_value > player_value)
            {
                printf("Dealer wins.\n");
            }
            else if (dealer_value < player_value)
            {
                printf("You win!\n");
                game_state.cash += 2 * game_state.pot;
            }
            else
            {
                printf("It's a tie.\n");
                game_state.cash += game_state.pot;
            }

            printf("Player's hand sum: %d\n", player_value);
            printf("Dealer's hand sum: %d\n", dealer_value);
        }

        // Reset Cards Phase
        reset_game_state(&game_state);

        // Check if the player wants to quit or continue
        printf("Cash: %d. Do you want to continue playing? (y/n): ", game_state.cash);
        scanf("%s", choice);
        if (choice[0] != 'Y' && choice[0] != 'y')
        {
            break;
        }
    }

    clear_game_state(&game_state); // clear the game state at the end of the game
}
