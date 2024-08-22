#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>  // Required for Sleep on Windows
#else
    #include <unistd.h>   // Required for sleep on UNIX/Linux
#endif

// Function to pause for a specified number of seconds
void pause_for_seconds(int seconds) {
#ifdef _WIN32
    Sleep(seconds * 1000);  // Windows Sleep takes milliseconds
#else
    sleep(seconds);  // UNIX/Linux sleep takes seconds
#endif
}

// Function to get the player's choice to continue or quit
int get_quitting_choice(int cash) {
    char choice[10];
    printf("Your current cash amount is: %d\n", cash);
    printf("Do you want to continue playing or quit? (c = continue / q = quit): ");
    scanf("%s", choice);
    while ((getchar()) != '\n');  // Flush the input buffer

    if (choice[0] == 'Q' || choice[0] == 'q') {
        printf("You chose to quit. Thanks for playing!\n");
        pause_for_seconds(1);  // Pause for 1 second
        return 1;  // Quit
    }
    return 0;  // Continue playing
}
