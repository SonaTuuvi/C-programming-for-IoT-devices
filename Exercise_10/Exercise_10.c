//
// Created by Sona on 10/2/2026 AD.
//

/*
 * Author: You know who
 * Date: This misery was written in 10.2.2026
 * Project: Talk to me, Baby- String lenght Judge
 *
 * Description:
 *  - Politely asks the user for input.
 *  - Tells them how long their thoughts are.
 *  - Stops when the user finally says "stop".
 *
 * Notes:
 *  - Uses fgets like an adult.
 *  - Trims the newline a barbarian with manners.
 *  - To read strings until the user says “stop” or the programmer cries. Whichever comes first.
 */

#include <stdio.h>
#include <string.h>
#include "Exercise_10.h"

// Remove the trailing newline, because fgets just had to include it
void trim_newline(UserInput *user_input) {
    size_t len_of_line = strlen(user_input->buffer);    // classic strlen, manually counting characters like it's 1985
    if (len_of_line > 0 && user_input->buffer[len_of_line - 1] == '\n') {
        user_input->buffer[len_of_line - 1] = '\0';     //Snip snip - good riddance
    }
}

// Analyze what the user typed. Is it "stop"? Is it a cry for help?
void analyze_input(UserInput *user_input) {
    trim_newline(user_input);                           // First, make it less awful
    user_input->length = strlen(user_input->buffer);    // yep, counting again
    user_input->is_stop_signal = (strcmp(user_input->buffer,"stop") == 0);
    // strcmp returns 0 if the strings match exactly — no surprises, hopefully
}

void run_exersise_10() {
    UserInput current_user_input;   // using a struct for one string because why not overengineer
    // I'm already dying of boredom… isn't there a law against making experienced programmers suffer like this?

    while (1) {
        printf("Say something (type 'stop' to exit this nightmare): ");

        // fgets reads from stdin and throws in a newline like a prank
        // returns NULL if the world ends or the user hits Ctrl+D
        if (fgets(current_user_input.buffer, INPUT_LIMIT, stdin) == NULL) {
            // Apparently, the user broke stdin. Nice!
            printf("Couldn't read input. Try harder.\n");
            continue;   // back to the top we go
        }

        analyze_input(&current_user_input);
        printf("Length: %lu characters.\n", current_user_input.length);
        // %lu for size_t, because C doesn't want life to be simple

        if (current_user_input.is_stop_signal) {
            //Finally! Sweet silence.
            printf("You said stop. Thank you. BAY!\n");
            break;  // direct escape from the loop — no flag nonsense needed
        }

    }
}

