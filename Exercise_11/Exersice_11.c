#include <stdio.h>
#include <string.h>
#include "Exercise_11.h"

/*
 * -------------------------------------------------------------
 * Author:      Sona (rewriting reality one char at a time)
 * Date:        Same endless timeline
 * File:        Exercise_11.c
 * -------------------------------------------------------------
 *
 * Description:
 *      Finds every occurrence of a character
 *      and replaces it with another.
 *
 *      Returns how many times we interfered.
 *
 * Emotional status:
 *      controlled destruction
 *
 * -------------------------------------------------------------
 */


int replace_char(char *str, const char *repl)
{
    int replacement_count = 0;     // counting small acts of chaos
    int current_index = 0;         // walking through string carefully

    if (str == NULL || repl == NULL)
        return 0;

    // must contain exactly 2 characters
    if (repl[0] == '\0' ||
        repl[1] == '\0' ||
        repl[2] != '\0')
        return 0;

    while (str[current_index] != '\0')
    {
        if (str[current_index] == repl[0])
        {
            str[current_index] = repl[1];   // transformation happens
            replacement_count++;
        }

        current_index++;   // keep moving forward
    }

    return replacement_count;   // report total impact
}


void run_exercise_11(void)   // function that runs exercise 11
{
    StringOperationContainer container;  // struct that stores our string and replacement pair
    int result;                          // will store how many replacements happened
    int useless_leftover;                // used to clean input buffer after scanf disaster

    /*
     * Menu used scanf.
     * scanf left '\n' behind.
     * fgets would instantly read it.
     * We refuse to let that happen again.
     */
    while ((useless_leftover = getchar()) != '\n' &&   // read characters one by one
           useless_leftover != EOF)                    // stop if input stream ends
    {
        /* swallowing leftover input like emotional trauma */
    }

    printf("Enter a string:\n");   // asking user for the main string

    /*
     * fgets reads a full line safely.
     * It waits for input.
     * Unlike scanf, it respects boundaries.
     */
    if (fgets(container.dramatic_string,              // where we store input
              sizeof(container.dramatic_string),      // max size allowed
              stdin) == NULL)                         // input source
    {
        printf("Input failed. Even typing is hard.\n"); // if reading fails
        return;                                        // exit function immediately
    }

    // fgets keeps newline.
    // We remove it because we are civilized.
    container.dramatic_string[
        strcspn(container.dramatic_string, "\n")  // find position of newline
    ] = '\0';                                     // replace newline with string terminator

    printf("Enter two characters (example: e3):\n");  // ask for replacement pair

    /*
     * Again using fgets.
     * Again being responsible adults.
     */
    if (fgets(container.replacement_pair,            // store two characters here
              sizeof(container.replacement_pair),    // buffer size (overkill, but safe)
              stdin) == NULL)                        // read from keyboard
    {
        printf("Input failed again. Incredible.\n"); // dramatic response
        return;                                      // exit function
    }

    // remove newline from second input too
    container.replacement_pair[
        strcspn(container.replacement_pair, "\n")
    ] = '\0';

    // call the actual logic function
    result = replace_char(container.dramatic_string,
                          container.replacement_pair);

    // check if something was actually replaced
    if (result > 0)
    {
        printf("Replacements made: %d\n", result);   // show how many changes happened
        printf("Modified string:\n%s\n",
               container.dramatic_string);           // print modified string
    }
    else
    {
        printf("String was not modified.\n");        // nothing changed
        printf("Either nothing matched or rules were ignored.\n");
    }
}
