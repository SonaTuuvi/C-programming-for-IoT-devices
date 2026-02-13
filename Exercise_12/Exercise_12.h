#ifndef EXERCISE_12_H
#define EXERCISE_12_H

/*
 * -------------------------------------------------------------
 * Author:      Sona (linguistically exhausted)
 * Date:        Time continues whether we like it or not
 * File:        Exercise_12.h
 * -------------------------------------------------------------
 *
 * Description:
 *      Counts how many times a word appears in a string.
 *      Because repetition is a theme.
 *
 * Notes:
 *      Uses strstr like the assignment demands.
 *      Moves pointer forward.
 *      No overlapping drama allowed.
 *
 * -------------------------------------------------------------
 */

// Counts how many times "word" appears inside "str"
// Returns the number of occurrences
int count_words(const char *str, const char *word);

// Runs exercise here...
void run_exercise_12(void);

#endif //EXERCISE_12_H