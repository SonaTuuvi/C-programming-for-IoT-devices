#include <stdio.h>      
/*
 * printf()   - prints formatted text to stdout (normal console output)
 * fprintf()  - prints formatted text to a specific stream (stderr here)
 * fgets()    - safely reads a whole line from stdin into a buffer
 * getchar()  - reads ONE character from stdin (used to clear input buffer)
 */

#include <stdlib.h>     
/*
 * rand()   - generates a pseudo-random integer
 * srand()  - sets the starting seed for rand()
 */

#include <string.h>     
/*
 * strlen()   - returns the length of a string (not counting '\0')
 * strcmp()   - compares two strings (returns 0 if equal)
 * strcspn()  - finds the first position of a character from a set
 *              I use it to remove '\n' after fgets
 * memcpy()   - copies raw bytes from one memory area to another
 */

#include <ctype.h>      
/*
 * isspace()  - checks if a character is whitespace
 *              (space, tab, newline, etc.)
 */

#include <stdbool.h>    
/*
 * bool  - boolean type
 * true  - boolean true value
 * false - boolean false value
 */

#include <time.h>       
/*
 * time(NULL) - returns current time in seconds
 *              I use it as a seed for srand()
 */

#include "Exercise_17.h"


/*
* -------------------------------------------------------------
 * Author: Sona (grumpy programmer mode)
 * File:   Exercise_18.c
 * -------------------------------------------------------------
 *
 * MISSION:
 * The program repeatedly asks the user to enter a word.
 *
 * If the user types:
 *      "stop"
 * the program stops.
 *
 * Otherwise the program generates a password containing
 * the given word.
 *
 * Password rule:
 *
 *      password_length = (length_of_word * 2) + 1
 *
 * Pattern:
 *
 *      random_char
 *      letter_from_word
 *      random_char
 *      letter_from_word
 *      ...
 *      random_char
 *
 * Example for word "cat":
 *
 *      #c%a!t$
 *
 * Printable characters are ASCII 33..126.
 * -------------------------------------------------------------
 */


/*
 * -------------------------------------------------------------
 * Helper function prototypes
 * -------------------------------------------------------------
 */

static void clear_input_buffer(void);
static void trim_whitespace_in_place(char *text);
static char random_printable_character(void);

static bool generate_password(
        char *password_output,
        int output_size,
        const char *word);



/*
 * -------------------------------------------------------------
 * Function: run_exercise_17
 * -------------------------------------------------------------
 * This function runs the entire exercise.
 * -------------------------------------------------------------
 */
void run_exercise_17(void)
{
    char word_buffer[32];      /* requirement: input buffer must be 32 */
    char password_buffer[128]; /* large enough for generated password */
    int seeded = 0;

    /*
     * If previous code used scanf(),
     * there may be leftover '\n' in stdin.
     * I remove it using getchar().
     */
    clear_input_buffer();

    printf("Enter a word to include in the password.\n");
    printf("Type \"stop\" to stop.\n\n");

    while (1)
    {
        printf("Enter word (or stop): ");

        /*
         * fgets() reads a full line from stdin.
         * It stores it in word_buffer and always
         * terminates the string with '\0'.
         */
        if (fgets(word_buffer, sizeof(word_buffer), stdin) == NULL)
        {
            printf("\nInput ended.\n");
            break;
        }

        /*
         * Remove newline if fgets stored it.
         *
         * strcspn finds the index of '\n'.
         */
        word_buffer[strcspn(word_buffer, "\n")] = '\0';

        trim_whitespace_in_place(word_buffer);

        if (strlen(word_buffer) == 0)
        {
            fprintf(stderr, "Error: empty input.\n");
            continue;
        }

        /*
         * strcmp compares two strings.
         * If result == 0 → strings are identical.
         */
        if (strcmp(word_buffer, "stop") == 0)
        {
            printf("Stopping.\n");
            break;
        }

        /*
         * I seed rand() once using current time.
         * srand() makes sure random numbers change each run.
         */
        if (!seeded)
        {
            srand((unsigned int)time(NULL));
            seeded = 1;
        }

        if (generate_password(password_buffer,
                              sizeof(password_buffer),
                              word_buffer))
        {
            printf("Generated password: %s\n\n", password_buffer);
        }
        else
        {
            fprintf(stderr,
                    "Error: password does not fit in output buffer.\n\n");
        }
    }
}


/*
 * -------------------------------------------------------------
 * Function: generate_password
 * -------------------------------------------------------------
 *
 * Generates the password using the required pattern.
 *
 * Returns:
 *      true  -> password generated
 *      false -> password does not fit
 * -------------------------------------------------------------
 */
static bool generate_password(
        char *password_output,
        int output_size,
        const char *word)
{
    size_t word_length;
    size_t password_length;
    size_t needed;

    char temp[256];
    size_t i;

    if (password_output == NULL || word == NULL)
        return false;

    /*
     * strlen() returns the number of characters
     * in a string until '\0'.
     */
    word_length = strlen(word);

    password_length = (word_length * 2) + 1;
    needed = password_length + 1;

    if ((size_t)output_size < needed)
        return false;

    /*
     * First character is random printable.
     */
    temp[0] = random_printable_character();

    for (i = 0; i < word_length; i++)
    {
        size_t letter_index = (2 * i) + 1;
        size_t random_index = (2 * i) + 2;

        temp[letter_index] = word[i];
        temp[random_index] = random_printable_character();
    }

    /*
     * Add string terminator.
     */
    temp[password_length] = '\0';

    /*
     * memcpy copies raw bytes.
     * Here I copy the finished password
     * into the output buffer.
     */
    memcpy(password_output, temp, needed);

    return true;
}


/*
 * -------------------------------------------------------------
 * Function: random_printable_character
 * -------------------------------------------------------------
 *
 * Generates a random printable ASCII character.
 *
 * ASCII printable range:
 *      33  -> '!'
 *      126 -> '~'
 * -------------------------------------------------------------
 */
static char random_printable_character(void)
{
    int min = 33;
    int max = 126;
    int range = max - min + 1;

    /*
     * rand() returns pseudo-random number.
     * % range restricts it to desired interval.
     */
    return (char)(min + rand() % range);
}


/*
 * -------------------------------------------------------------
 * Function: clear_input_buffer
 * -------------------------------------------------------------
 *
 * Removes leftover characters from stdin.
 *
 * getchar() reads characters one by one
 * until newline or EOF.
 * -------------------------------------------------------------
 */
static void clear_input_buffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        /* discard characters */
    }
}


/*
 * -------------------------------------------------------------
 * Function: trim_whitespace_in_place
 * -------------------------------------------------------------
 *
 * Removes whitespace from beginning and end of string.
 *
 * isspace() checks whether a character is whitespace.
 * -------------------------------------------------------------
 */
static void trim_whitespace_in_place(char *text)
{
    int start = 0;
    int end;
    int len;

    if (text == NULL)
        return;

    len = strlen(text);

    while (isspace((unsigned char)text[start]))
        start++;

    if (text[start] == '\0')
    {
        text[0] = '\0';
        return;
    }

    end = len - 1;

    while (end >= 0 && isspace((unsigned char)text[end]))
        end--;

    if (start > 0)
    {
        int i = 0;

        while (text[start] != '\0')
        {
            text[i++] = text[start++];
        }

        text[i] = '\0';
    }

    len = strlen(text);
    end = len - 1;

    while (end >= 0 && isspace((unsigned char)text[end]))
    {
        text[end] = '\0';
        end--;
    }
}