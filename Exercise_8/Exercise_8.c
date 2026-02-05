#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Exercise_8.h"

/*
 * This function prints each number in the array
 * in a field exactly 8 characters wide. Why 8? Because we're fancy.
 */
void print_numbers(const NumberArray* array) {
    for (int i = 0; i < array->count; i++) {
        printf("%8d\n", array->numbers[i]); // Because aesthetics matter
    }
}

/*
 * This is the master function that commands the array to exist,
 * fills it with glorious randomness, and parades it for show.
 */
void run_exercise_8(void) {
    NumberArray legendary_array;
    legendary_array.count = 15;

    // Seed the chaos machine
    srand((unsigned int)time(NULL));

    // Fill the array with the unexpected (aka rand)
    for (int i = 0; i < legendary_array.count; i++) {
        legendary_array.numbers[i] = rand() % 100; // Keep it spicy, under 100
    }

    // Time for the catwalk
    printf("✨ Behold the numbers, printed with style:\n\n");
    print_numbers(&legendary_array);
}
