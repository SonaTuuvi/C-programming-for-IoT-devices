#include <stdio.h>      // for printf, fgets
#include <string.h>     // for strstr, strlen, strcmp, strcspn
#include "Exercise_12.h" // our header, because we are organized (theoretically)

/*
 * -------------------------------------------------------------
 * Author:      Sona (professional word counter)
 * Date:        Still surviving
 * File:        Exercise_12.c
 * -------------------------------------------------------------
 *
 * Description:
 *      Counts how many times one word appears inside a string.
 *      Uses strstr because assignment said so.
 *      Moves pointer forward to avoid counting same match twice.
 *
 * Emotional status:
 *      stable but suspicious
 *
 * -------------------------------------------------------------
 */


/*
 * Function: count_words
 * -----------------------------------------
 * str  -> main string where we search
 * word -> word we are searching for
 *
 * Returns:
 *      number of occurrences of "word" inside "str"
 */
int count_words(const char *str, const char *word)
{
    int count = 0;                      // stores how many matches we found
    const char *current_position = str; // pointer used to scan through string

    // if either pointer is NULL, we do nothing
    if (str == NULL || word == NULL)
        return 0;

    // if word is empty string, searching makes no sense
    if (word[0] == '\0')
        return 0;

    // loop while strstr keeps finding matches
    while ((current_position = strstr(current_position, word)) != NULL)
    {
        count++;   // found one match, increase counter

        // move pointer forward by length of word
        // this ensures we skip current match
        // and continue searching after it
        current_position += strlen(word);
    }

    return count;  // return total number of matches found
}


/*
 * Function: run_exercise_12
 * -----------------------------------------
 * Handles user input and calls count_words.
 * Repeats until user types "stop".
 */
void run_exercise_12(void)
{
    char user_string[300];      // buffer to store main input string
    char user_word[100];        // buffer to store search word
    int leftover_character;     // used to clean input buffer after scanf in menu

    /*
       If menu used scanf,
       it left '\n' in input buffer.
       We remove it so fgets works properly.
    */
    while ((leftover_character = getchar()) != '\n' &&
           leftover_character != EOF)
    {
        // discarding unwanted leftover characters
    }

    // repeat until user types "stop"
    while (1)
    {
        printf("\nEnter a string:\n");   // ask user for main string

        // read full line safely
        if (fgets(user_string, sizeof(user_string), stdin) == NULL)
        {
            printf("Input failed.\n");   // error message
            break;                      // exit loop
        }

        // remove newline character left by fgets
        user_string[strcspn(user_string, "\n")] = '\0';

        printf("Enter a word (type \"stop\" to exit):\n"); // ask for search word

        if (fgets(user_word, sizeof(user_word), stdin) == NULL)
        {
            printf("Input failed.\n");
            break;
        }

        // remove newline from second input
        user_word[strcspn(user_word, "\n")] = '\0';

        // check if user wants to stop program
        if (strcmp(user_word, "stop") == 0)
        {
            printf("Program stopped.\n");
            break;  // exit infinite loop
        }

        // call counting function
        int result = count_words(user_string, user_word);

        // print result
        printf("The word \"%s\" appears %d times.\n",
               user_word, result);
    }
}
