# RETD college - C Language For Embedded: Final project, BlackJack game.
Haim Ozer
Student I.D: 316063569  
Date: 18/08/2024 ~ 20/9/2024 
Lecturer: Shmuel 
--------------------------------------------------------------------------

# BlackJack
Running the Blackjack Game
To compile and run the Blackjack game, use the following commands:

1. Compile the game:
 gcc -I Headers -o blackjack src/main.c src/game.c src/deck.c src/hand.c src/card.c src/split.c src/visuals.c src/insurance.c src/quitting_choice.c src/game_state.c

2. Run the game:
   ./blackjack.exe
--------------------------------------------------------------------------
Running the Test Suite
To compile and run the test suite for verifying the card encoding, linked list operations, and scoring logic, use the following commands:

1. Compile the test suite:
   gcc -I Headers -o test_blackjack src/tests/test_blackjack.c src/card.c src/deck.c src/hand.c

2. Run the test suite:
   ./test_blackjack.exe
--------------------------------------------------------------------------
Running the Test for game state (one full game round) 

1. Compile the test: 
   gcc -I Headers -o test_gamestate src/tests/test_gamestate.c src/card.c src/deck.c src/hand.c src/game_state.c

2. Run the test:
   ./test_gamestate