#ifndef RUN_EXERCISE_8_H
#define RUN_EXERCISE_8_H

// ---------------------------------------------
// Author: The One Who Structures All Things
// Date: 05.02.2026
// Mission: Print numbers, but make it art
// ---------------------------------------------

// Struct to hold a legendary array and its magical size
typedef struct {
    int numbers[15];
    int count;
} NumberArray;

// Function to print all numbers with dramatic spacing
void print_numbers(const NumberArray* array);

// Function that runs the whole circus
void run_exercise_8(void);

#endif // RUN_EXERCISE_8_H
