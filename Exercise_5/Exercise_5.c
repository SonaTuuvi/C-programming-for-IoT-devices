#include <stdio.h>
#include "Exercise_5.h"

/*
 * --------------------------------------------------------------------------
 * Author:      The Legend... named Sona
 * Date:        05.02.2026
 * Project:     Exercise 5 – Dice Game (rigged and proud)
 * --------------------------------------------------------------------------
 *
 * Description:
 *      User rolls a die. Program rolls higher. Always.
 *      If you roll a 6 – we pretend it’s a tie to avoid lawsuits.
 *
 * Notes:
 *      - Input is validated, but feelings are not.
 *      - Game lasts 3 rounds or until emotional collapse.
 */


// Reads a number between low and high (inclusive)
// If user fails to follow basic instructions — we try again, forever
int read_range(int low, int high) {
    int value;
    char leftover;

    while (1) {
        // Politely ask for input
        printf("Enter a number between %d and %d: ", low, high);

        // Read number + extra character to detect junk like "3abc"
        if (scanf("%d%c", &value, &leftover) == 2 && (leftover == '\n' || leftover == ' ')) {
            if (value >= low && value <= high) {
                return value; // valid input — let's go
            } else {
                printf("Nope. That’s out of range.\n"); // math exists, use it
            }
        } else {
            printf("Invalid. Try again, but better.\n"); // softly judged
            while (getchar() != '\n'); // yeet the leftovers
        }
    }
}


// Launches the game logic
// Loops 3 rounds. User rolls. Program responds... unfairly.
void run_exercise_5(void) {
    printf("Let's play!\n");

    for (int round = 0; round < 3; round++) {
        printf("Roll a die and enter your result.\n");
        int user_roll = read_range(1, 6); // hope lives here

        if (user_roll == 6) {
            // We don't dare cheat a 6. Too risky.
            printf("I got 6. It is a tie!\n");
        } else {
            // “Random” response +1. Suspiciously consistent.
            printf("I got %d. I win!\n", user_roll + 1);
        }
    }

    printf("Better luck next time. Bye!\n"); // classic emotional closure
}
