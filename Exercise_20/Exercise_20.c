//
// Created by Sona on 5/3/2026 AD.
//
#include "Exercise_20.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "debug.h"

/*-------------------------------------------------------------
Exercise 20 implementation

This file contains the main logic for Exercise 20.

What this program does:
- asks the user to enter a debug level (0–4)
- stores the level using set_debug_level()
- generates five messages with random debug levels
- prints messages using dprintf()

Messages are printed only if their debug level is
less than or equal to the stored debug level.
-------------------------------------------------------------*/


/*-------------------------------------------------------------
Internal helper functions (used only in this file)
-------------------------------------------------------------*/
static int read_debug_level_0_to_4_from_user(void);
static int read_int_from_user(const char *prompt, int *out_value);
static int random_debug_level_0_to_4(void);


/*-------------------------------------------------------------
Function: run_exercise_20

Main function that performs the Exercise 20 logic.

Steps performed:
1. Initialize random generator
2. Ask the user to enter debug level (0..4)
3. Store the level using set_debug_level()
4. Generate 5 messages with random debug levels
5. Print messages using dprintf()

Each message contains:
- its index number
- the random debug level
- the stored debug level
-------------------------------------------------------------*/
void run_exercise_20(void)
{
    int chosen_level;
    int message_index;

    srand((unsigned int)time(NULL));

    chosen_level = read_debug_level_0_to_4_from_user();
    set_debug_level(chosen_level);

    fprintf(stderr, "\nStored debug level = %d\n", chosen_level);
    fprintf(stderr, "Printing 5 messages to stderr using dprintf...\n\n");
    fflush(stderr);

    for (message_index = 1; message_index <= 5; message_index++)
    {
        int msg_level = random_debug_level_0_to_4();

        dprintf(msg_level,
                "Message #%d (random level=%d, stored=%d)\n",
                message_index,
                msg_level,
                chosen_level);
    }

    fflush(stderr);
    fprintf(stderr, "\nDone.\n");
    fflush(stderr);
}


/*-------------------------------------------------------------
Function: read_debug_level_0_to_4_from_user

Asks the user to enter a debug level between 0 and 4.

What it does:
- repeatedly asks the user for input
- checks that the number is between 0 and 4
- returns a valid debug level

If input ends unexpectedly:
- prints a message
- returns default level 0
-------------------------------------------------------------*/
static int read_debug_level_0_to_4_from_user(void)
{
    int level;

    while (1)
    {
        if (!read_int_from_user("Enter debug level (0..4): ", &level))
        {
            printf("Input ended. Defaulting to debug level 0.\n");
            return 0;
        }

        if (level < 0 || level > 4)
        {
            printf("Error: level must be between 0 and 4.\n");
            continue;
        }

        return level;
    }
}


/*-------------------------------------------------------------
Function: read_int_from_user

Safely reads an integer from the user.

Instead of scanf(), this function:
- reads input using fgets()
- converts the text to a number using strtol()
- validates the input

If invalid input is entered:
- an error message is shown
- the user is asked again

Parameters:
- prompt     -> message shown to the user
- out_value  -> where the integer result is stored

Returns:
1 -> valid integer was read
0 -> input failed
-------------------------------------------------------------*/
static int read_int_from_user(const char *prompt, int *out_value)
{
    char line[64];
    long value;
    char *endptr;

    if (out_value == NULL)
        return 0;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(line, sizeof(line), stdin) == NULL)
            return 0;

        line[strcspn(line, "\n")] = '\0';

        endptr = NULL;
        value = strtol(line, &endptr, 10);

        if (endptr == line)
        {
            printf("Invalid input. Please type a number.\n");
            continue;
        }

        while (*endptr != '\0')
        {
            if (*endptr != ' ' && *endptr != '\t')
            {
                printf("Invalid input. Please type a clean integer.\n");
                value = 999999;
                break;
            }
            endptr++;
        }

        if (value == 999999)
            continue;

        *out_value = (int)value;
        return 1;
    }
}


/*-------------------------------------------------------------
Function: random_debug_level_0_to_4

Generates a random debug level between 0 and 4.

Uses:
rand() % 5

Returns:
random number in range 0–4
-------------------------------------------------------------*/
static int random_debug_level_0_to_4(void)
{
    return rand() % 5;
}