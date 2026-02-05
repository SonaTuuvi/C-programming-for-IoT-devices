#ifndef SADNESS_HEADER_H
#define SADNESS_HEADER_H

/*
 * -------------------------------------------------------------
 * Author:      Sona (emotionally stable, allegedly)
 * Date:        Today was long...
 * File:        Exercise_8.h
 * -------------------------------------------------------------
 *
 * Description:
 *      Declares things we pretend will make life easier.
 *      Mostly arrays. Mostly disappointment.
 *
 * Notes:
 *      We do NOT pass array size because we trust zero to end things.
 *      Just like motivation usually does.
 *
 * -------------------------------------------------------------
 */

// Struct exists because chaos needs boundaries
// Also because the author likes structs and refuses therapy
typedef struct{
    unsigned int tragic_values[20];   // 19 numbers + 1 emotional support zero
}OneMoreNumberArray;


// Searches for a number in an array
// Stops when it finds the number or loses hope (hits zero)
int find_first(const unsigned int *array, unsigned int what);
// Runs program here...
void run_exercise_9(void);

#endif // SADNESS_HEADER_H
