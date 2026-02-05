#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Exercise_9.h"

/*
 * -------------------------------------------------------------
 * Author:      Sona (still here, somehow)
 * Date:        Time is a flat circle
 * File:        Exercise_9.c
 * -------------------------------------------------------------
 *
 * Description:
 *      This function searches an array for a number.
 *      Just like we search for meaning in life.
 *
 *      It stops if:
 *          - the number is found
 *          - or zero appears (array says "that's enough")
 *
 * Returns:
 *      index if found
 *      -1 if not found
 *
 * Emotional status:
 *      fragile but functional
 *
 * -------------------------------------------------------------
 */


int find_first(const unsigned int *array, unsigned int what)
{
    int current_index = 0;  // walking through life one index at a time

    // Continue until array says "we're done here"
    while (array[current_index] != 0)
    {
        // tiny spark of hope
        if (array[current_index] == what)
        {
            return current_index;   // success... suspicious
        }

        current_index++; // keep scrolling through existence
    }

    // we reached zero
    // nothing was found
    // expectations were too high
    return -1;
}

void run_exercise_9(void) {
    OneMoreNumberArray pain_container;
    int i = 0;

    // seeding randomness with the ever-ticking clock
    srand((unsigned int)time(NULL));

    // filling 19 slots with random hope (1 to 20)
    for (i = 0; i < 19; ++i) {
        pain_container.tragic_values[i] = (rand() % 20) + 1;
    }

    pain_container.tragic_values[19] = 0; // emotional support zero

    // show what fate has given us
    printf("Array contents (each one more random than the last):\n");
    for (i = 0; i < 20; ++i) {
        printf("%u\n", pain_container.tragic_values[i]);
    }

    // endless loop until the user says "enough"
    while (1) {
        unsigned int query = 0;

        printf("\nEnter a number to search for (0 to give up): ");
        if (scanf("%u", &query) != 1) {
            printf("I don't understand you anymore.\n");
            break;
        }

        if (query == 0) {
            printf("Fair enough. Goodbye.\n");
            break;
        }

        int found_index = find_first(pain_container.tragic_values, query);

        if (found_index == -1) {
            printf("Number %u was not found. Typical.\n", query);
        } else {
            printf("Found number %u at index %d. Miracles do happen.\n", query, found_index);
        }
    }
}

