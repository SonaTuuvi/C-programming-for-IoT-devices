#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Exercise_6.h"

/*
 * --------------------------------------------------------------------------
 * Author:      The Legend... named Sona
 * Date:        05.02.2026
 * Project:     Exercise 6 – Menu, Dice, and Decisions
 * --------------------------------------------------------------------------
 *
 * Description:
 *      Displays a menu. Lets the user roll D6 or D10.
 *      Or they can quit. We respect boundaries.
 *
 * Notes:
 *      This version is structured, separated, and sarcastic.
 *      No structs here — didn't feel right. Just good old functions.
 */

// Just enough validation to catch user rebellion
static int get_valid_choice(void) {
    int choice;
    char leftover;

    while (1) {
        printf("\nMenu:\n");
        printf("1 - Roll D6\n");
        printf("2 - Roll D10\n");
        printf("3 - Quit\n");
        printf("Choose wisely: ");

        if (scanf("%d%c", &choice, &leftover) == 2 && (leftover == '\n' || leftover == ' ')) {
            if (choice >= 1 && choice <= 3) {
                return choice;
            } else {
                printf("Out of range. Try 1, 2 or 3. Not rocket science.\n");
            }
        } else {
            printf("Invalid input. Numbers only. Keyboard smashes won’t help.\n");
            while (getchar() != '\n'); // flush leftover chaos
        }
    }
}

// Rips a random number from the void (inclusive range)
static int roll_dice(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Controls the fate of the session
void run_exercise_6(void) {
    srand((unsigned int)time(NULL)); // Let chaos begin

    int still_alive = 1;

    while (still_alive) {
        int choice = get_valid_choice();

        if (choice == 1) {
            // D6 for classic players
            printf("You rolled (D6): %d\n", roll_dice(1, 6));
        } else if (choice == 2) {
            // D10 — extra spice
            printf("You rolled (D10): %d\n", roll_dice(1, 10));
        } else if (choice == 3) {
            // Escape hatch
            printf("You chose to quit. Wise.\n");
            still_alive = 0;
        }
    }
}
