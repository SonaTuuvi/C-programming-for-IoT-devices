#ifndef EXERCISE_11_H
#define EXERCISE_11_H


/*
 * -------------------------------------------------------------
 * Author:      Sona (modifying strings, not behavior)
 * Date:        Time exists. Unfortunately.
 * File:        Exercise_11.h
 * -------------------------------------------------------------
 *
 * Description:
 *      Replaces one character with another in a string.
 *      Counts how much damage was done.
 *
 * Notes:
 *      Second string must contain exactly 2 characters.
 *      No more. No less. Precision matters.
 */


// Struct exists because structure creates illusion of control
typedef struct{
    char dramatic_string[300];   // the string we will emotionally alter
    char replacement_pair[10];   // should contain exactly 2 characters
}StringOperationContainer;

// Replaces occurrences of repl[0] with repl[1]
// Returns number of replacements
int replace_char(char *str, const char *repl);

// Runs exercise here...
void run_exercise_11(void);

#endif //EXERCISE_11_H