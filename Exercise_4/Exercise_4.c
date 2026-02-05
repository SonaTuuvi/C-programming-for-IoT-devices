/*
* --------------------------------------------------------------------------
 * Author:      The Legend... named Sona
 * Date:        05.02.2026
 * Project:     Exercise 4 – Positive Number Averager (a.k.a. sanity test)
 * --------------------------------------------------------------------------
 *
 * Description:
 *      Reads integers from a doomed user until they surrender with a negative.
 *      Validates each input using scanf sorcery.
 *      Stores all positive numbers in a dynamic array (yes, we malloc responsibly).
 *      Calculates and displays the average — even if it’s 0.000 (ouch).
 *
 * Features:
 *      - scanf loop with retry until valid integer is given
 *      - Dynamic memory handling without memory leaks (we promise)
 *      - Rounded output average to 3 decimal places
 *
 * Notes:
 *      - Based on raw persistence and C arrays
 *      - Input terminates only on negative integer (escape hatch)
 *      - Not optimized for emotional stability
 *
 * Usage:
 *      Compile, run, type numbers until your faith in input ends.
 *      Useful for anyone who wants to simulate grading or just count regrets.
 *
 * Todo:
 *      - Replace scanf with mind-reading
 *      - Automatically curve grades if average is too depressing
 *      - Add “emotional support mode” (or at least better prompts)
 */


#include <stdio.h>
#include <stdlib.h>
#include "Exercise_4.h"


// Reads a single integer from input.
// Keeps asking until valid input is provided (integer followed by newline or space).
int read_integer(void)
{
    int number;
    char terminator;

    while (1) {
        printf("Enter positive number or negative to stop: ");
        if (scanf("%d%c", &number, &terminator) == 2 && (terminator == '\n' || terminator == ' ')) {
            return number; // Valid input — finally!
        }
        // If input is invalid, it just silently loops again. Could add error message here.
    }
}

// Adds a number to the dynamic array (DataNumbers struct).
// Resizes the array if it's out of space (starts with 4, then doubles each time).
void put_integer(DataNumbers* numbers, int number)
{
    if (numbers->count >= numbers->capacity) {
        if (numbers->capacity == 0) {
            numbers->capacity = 4; // Initial capacity — small but fine
        } else {
            numbers->capacity = numbers->capacity * 2; // Classic doubling
        }

        // Try to allocate more memory
        int* resized = realloc(numbers->numbers, sizeof(int) * numbers->capacity);
        if (resized == NULL) {
            printf("Out of memory"); // Uh oh...
            free(numbers->numbers); // Clean up before exiting
            exit(1);                // Terminate program
        }

        numbers->numbers = resized; // Success — keep using new memory block
    }

    numbers->numbers[numbers->count++] = number; // Add number and increment count
};

// Calculates the average of all stored numbers.
// Returns 0.0 if no numbers were entered (to avoid division by zero).
double culculate_average(DataNumbers* numbers) {
    if (numbers->count == 0) {
        return 0.0; // No data, no math
    }

    int sum = 0;
    for (int i = 0; i < numbers->count; i++) {
        sum += numbers->numbers[i]; // Accumulate total
    }

    return (double)sum / numbers->count; // Cast to double for precision
};

// Prints the total count and average with 3 decimal places.
// (Also: typo in "entrerd" is kind of charming — left as-is!)
void display_average(DataNumbers* numbers, double average) {
    printf("You entrerd %d positive numbers. The average is: %.3f\n", numbers->count, average);
};

// Main function for running the exercise logic:
// - Read numbers using read_integer()
// - Store them using dynamic array
// - Compute average
// - Display result
void run_exercise_4(void) {
    DataNumbers numbers = {NULL, 0, 0}; // Initialize the struct to empty

    while (1) {
        int number = read_integer();
        if (number < 0) {
            break; // Negative number means we're done
        }
        put_integer(&numbers, number); // Save the number
    }

    double average = culculate_average(&numbers); // Calculate the result
    display_average(&numbers, average);           // Show the result

    free(numbers.numbers); // Free up the memory we used
};
