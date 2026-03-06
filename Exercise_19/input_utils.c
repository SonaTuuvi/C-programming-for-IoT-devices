#include "input_utils.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/*------------------------------------------------------------------
Input Utility Functions
Author: Sona

Helper functions for safe user input handling.
------------------------------------------------------------------*/


/*------------------------------------------------------------------
Function: read_line

Reads a line from stdin using fgets() and removes the newline
character so the string is easier to use later.

Returns:
1  -> success
0  -> failure or EOF
------------------------------------------------------------------*/
int read_line(char *buffer, int buffer_size)
{
    if (fgets(buffer, buffer_size, stdin) == NULL)
        return 0;

    buffer[strcspn(buffer, "\n")] = '\0';
    return 1;
}


/*------------------------------------------------------------------
Function: clear_input_buffer

Removes leftover characters from the input buffer.
Useful after scanf() to avoid input problems.
------------------------------------------------------------------*/
void clear_input_buffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        /* discard */
    }
}


/*------------------------------------------------------------------
Function: trim_whitespace_in_place

Removes spaces at the beginning and end of a string.

Example:
"   pizza   " -> "pizza"
------------------------------------------------------------------*/
void trim_whitespace_in_place(char *text)
{
    int start = 0;
    int end;
    int len;

    if (text == NULL)
        return;

    len = (int)strlen(text);

    while (text[start] != '\0' && isspace((unsigned char)text[start]))
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
            text[i++] = text[start++];

        text[i] = '\0';
    }

    len = (int)strlen(text);
    end = len - 1;

    while (end >= 0 && isspace((unsigned char)text[end]))
    {
        text[end] = '\0';
        end--;
    }
}


/*------------------------------------------------------------------
Function: read_int_from_user

Safely reads an integer from the user using fgets + strtol.
If invalid input is entered, the user is asked again.

Returns:
1 -> valid number read
0 -> failure
------------------------------------------------------------------*/
int read_int_from_user(const char *prompt, int *out_value)
{
    char line[64];
    long value;
    char *endptr;

    if (out_value == NULL)
        return 0;

    while (1)
    {
        printf("%s", prompt);

        if (!read_line(line, (int)sizeof(line)))
            return 0;

        endptr = NULL;
        value = strtol(line, &endptr, 10);

        if (endptr == line)
        {
            printf("Invalid input. Please type a number.\n");
            continue;
        }

        while (*endptr != '\0')
        {
            if (!isspace((unsigned char)*endptr))
            {
                printf("Invalid input. Please type a clean integer.\n");
                value = 999999;
                break;
            }
            endptr++;
        }

        if (value == 999999)
            continue;

        *out_value = (int)value;
        return 1;
    }
}