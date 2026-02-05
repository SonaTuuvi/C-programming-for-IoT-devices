// ------------------------------------------------------------
// Author:      The Legend... named Sona
// Date:        05.02.2026
// Project:     Guess My (Imaginary) Fortune – Deluxe Edition
// ------------------------------------------------------------
//
// Description:
//  A very serious simulation of wealth-based telepathy.
//  User attempts to guess how rich the program is.
//  Program lies with confidence: "I have 2x your guess + 20 euros."
//  After 3 invalid inputs, it emotionally withdraws from society.
//
// Notes:
//  - Uses a struct, because we’re civilized.
//  - Input is validated. Barely.
//  - No actual euros were harmed in this simulation.
//
// Usage:
//  Compile, run, guess wildly, get mocked.
// ------------------------------------------------------------

#include <stdio.h>
#include "Exercise_7.h"

// Ask user to enter a positive number
// If it's valid and positive -> store via pointer, return true
// If invalid or negative -> return false and make no promises
bool read_positive_number(int *user_input) {
    int number_attempt;
    char leftover_character;

    printf("Enter a positive number: ");

    if (scanf("%d%c", &number_attempt, &leftover_character) == 2 &&
        (leftover_character == '\n' || leftover_character == ' ')) {

        if (number_attempt > 0) {
            *user_input = number_attempt;
            return true;
        }
    }

    // Clean up whatever chaos is left in the input buffer
    while (getchar() != '\n');
    return false;
}

void run_exercise_7(void) {
    RichGuessingGame game = { .guessed_amount = 0, .invalid_input_counter = 0 };

    while (game.invalid_input_counter < 3) {
        printf("\nGuess how much money I have!\n");

        if (read_positive_number(&game.guessed_amount)) {
            int imaginary_wallet = game.guessed_amount * 2 + 20;
            printf("You didn’t get it right. I have %d euros.\n", imaginary_wallet);
        } else {
            printf("Incorrect input\n");
            game.invalid_input_counter++;
        }
    }

    printf("I give up! See you later!\n");
}
