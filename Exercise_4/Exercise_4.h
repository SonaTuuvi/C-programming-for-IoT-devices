/*
* --------------------------------------------------------------------------
 * Author:      The Legend... named Sona
 * Date:        30.01.2026
 * Header:      Exercise_4.h
 * --------------------------------------------------------------------------
 *
 * Description:
 *      Declarations for Exercise 4: dynamic number handling & average calculation.
 *      This header provides the structure and function prototypes used
 *      for collecting integers, storing them dynamically, and computing
 *      the average value of all positive entries.
 *
 * Contents:
 *      - DataNumbers struct for dynamic storage
 *      - read_integer() for validated input
 *      - put_integer() to store each value
 *      - culculate_average() to compute the average (yes, typo included)
 *      - display_average() to present results
 *      - run_exercise_4() to launch the chaos
 *
 * Notes:
 *      - Typo in "culculate" stays — it's part of the legend now
 *      - Assumes caller has enough patience for user input
 *      - Memory safety is attempted (but still: test wisely)
 */

#ifndef EXERCISE_4_H
#define EXERCISE_4_H

typedef struct {
    int* numbers;
    int count;
    int capacity;
} DataNumbers;

int  read_integer(void);
void put_integer(DataNumbers* numbers, int number);
double culculate_average(DataNumbers* numbers);
void display_average(DataNumbers* numbers, double average);
void run_exercise_4(void);

#endif //EXERCISE_4_H
