#include "menu_io.h"
#include "input_utils.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*-------------------------------------------------------------
Menu input/output functions
Author: Sona

This file is responsible for:
- reading the filename from the user
- opening the file for reading
- loading menu items from the file
- parsing each line into a menu item
-------------------------------------------------------------*/

#define EXERCISE_FOLDER_NAME "Exercise_19"

static FILE* try_open_reading_with_guess_paths(const char *filename_from_user);
static int parse_line_into_menu_item(const char *line_from_file,
                                     menu_item *menu_item_to_fill);

/*-------------------------------------------------------------
Function: read_filename_from_user

Asks the user to enter a filename and stores it in the buffer.

What it does:
- prints a message asking for a filename
- reads one line from the keyboard
- checks that the entered text is not empty

Parameters:
- filename_buffer -> array where the filename is stored
- buffer_size     -> size of the filename buffer

Returns:
- 1 if a filename was entered successfully
- 0 if input failed or the filename is empty
-------------------------------------------------------------*/
int read_filename_from_user(char *filename_buffer, int buffer_size)
{
    printf("Enter filename:\n");

    if (!read_line(filename_buffer, buffer_size))
        return 0;

    if (strlen(filename_buffer) == 0)
        return 0;

    return 1;
}


/*-------------------------------------------------------------
Function: open_file_for_reading_or_exit

Tries to open the file for reading.

What it does:
- calls a helper function that tries different possible paths
- if the file is found, returns the opened FILE pointer
- if the file is not found, prints an error message and ends
  the program

Why it is useful:
- allows the program to search for the file in a few common
  folders instead of failing immediately

Parameter:
- filename_from_user -> name of the file entered by the user

Returns:
- pointer to the opened file

Note:
- if the file cannot be opened, the program exits with error
-------------------------------------------------------------*/
FILE* open_file_for_reading_or_exit(const char *filename_from_user)
{
    FILE *fp = try_open_reading_with_guess_paths(filename_from_user);

    if (fp == NULL)
    {
        fprintf(stderr,
                "Error: cannot open file \"%s\" for reading.\n",
                filename_from_user);

        fprintf(stderr,
                "Hint: I also tried:\n"
                "  " EXERCISE_FOLDER_NAME "/%s\n"
                "  ../" EXERCISE_FOLDER_NAME "/%s\n"
                "  ../../" EXERCISE_FOLDER_NAME "/%s\n",
                filename_from_user,
                filename_from_user,
                filename_from_user);

        exit(1);
    }

    return fp;
}


/*-------------------------------------------------------------
Function: read_menu_items_from_file

Reads menu items from the opened file into an array.

What it does:
- reads the file line by line
- tries to convert each line into a menu_item structure
- stores valid items in the array
- skips invalid lines and prints a warning

Parameters:
- opened_file      -> already opened file
- menu_items_array -> array where menu items are stored

Returns:
- the number of successfully read menu items

Note:
- reading stops when the file ends or the array is full
-------------------------------------------------------------*/
int read_menu_items_from_file(FILE *opened_file,
                              menu_item menu_items_array[MAX_MENU_ITEMS])
{
    char line_buffer[256];
    int total = 0;

    while (total < MAX_MENU_ITEMS)
    {
        if (fgets(line_buffer, sizeof(line_buffer), opened_file) == NULL)
            break;

        if (parse_line_into_menu_item(line_buffer, &menu_items_array[total]))
        {
            total++;
        }
        else
        {
            fprintf(stderr, "Warning: skipping invalid line: %s", line_buffer);
        }
    }

    return total;
}


/*-------------------------------------------------------------
Helper Function: try_open_reading_with_guess_paths

Tries to open the file using several possible paths.

What it does:
- first tries the exact filename entered by the user
- if that fails, tries the file inside Exercise_19/
- then tries ../Exercise_19/
- then tries ../../Exercise_19/

Why it is useful:
- sometimes the working directory is different
- this helper increases the chance of finding the file

Parameter:
- filename_from_user -> name of the file to open

Returns:
- FILE pointer if successful
- NULL if the file could not be opened

Note:
- if the filename already contains '/' or '\\', the function
  does not try extra guessed paths
-------------------------------------------------------------*/
static FILE* try_open_reading_with_guess_paths(const char *filename_from_user)
{
    FILE *fp;

    fp = fopen(filename_from_user, "r");
    if (fp != NULL)
        return fp;

    if (strchr(filename_from_user, '/') != NULL ||
        strchr(filename_from_user, '\\') != NULL)
    {
        return NULL;
    }

    {
        char path[512];

        snprintf(path, sizeof(path),
                 EXERCISE_FOLDER_NAME "/%s", filename_from_user);

        fp = fopen(path, "r");
        if (fp != NULL)
            return fp;

        snprintf(path, sizeof(path),
                 "../" EXERCISE_FOLDER_NAME "/%s", filename_from_user);

        fp = fopen(path, "r");
        if (fp != NULL)
            return fp;

        snprintf(path, sizeof(path),
                 "../../" EXERCISE_FOLDER_NAME "/%s", filename_from_user);

        fp = fopen(path, "r");
        if (fp != NULL)
            return fp;
    }

    return NULL;
}


/*-------------------------------------------------------------
Helper Function: parse_line_into_menu_item

Converts one line from the file into a menu_item structure.

Expected line format:
name ; price

Example:
Pizza ; 12.50

What it does:
- copies the input line into a local buffer
- removes the newline character
- searches for the ';' separator
- splits the line into name part and price part
- removes extra spaces from both parts
- converts the price text into a number
- stores the result into the menu_item structure

Parameters:
- line_from_file     -> one line read from the file
- menu_item_to_fill  -> structure that will receive the data

Returns:
- 1 if the line was parsed successfully
- 0 if the line format is invalid

Note:
- the function rejects lines without ';'
- the function rejects empty names
- the function rejects invalid prices
-------------------------------------------------------------*/
static int parse_line_into_menu_item(const char *line_from_file,
                                     menu_item *menu_item_to_fill)
{
    char local[256];
    char *semi;

    char *name_part;
    char *price_part;

    char *endptr;
    double price;

    if (line_from_file == NULL || menu_item_to_fill == NULL)
        return 0;

    strncpy(local, line_from_file, sizeof(local) - 1);
    local[sizeof(local) - 1] = '\0';

    local[strcspn(local, "\n")] = '\0';

    semi = strchr(local, ';');
    if (semi == NULL)
        return 0;

    *semi = '\0';

    name_part = local;
    price_part = semi + 1;

    trim_whitespace_in_place(name_part);
    trim_whitespace_in_place(price_part);

    if (strlen(name_part) == 0)
        return 0;

    price = strtod(price_part, &endptr);
    if (endptr == price_part)
        return 0;

    strncpy(menu_item_to_fill->name, name_part, MAX_NAME_LENGTH - 1);
    menu_item_to_fill->name[MAX_NAME_LENGTH - 1] = '\0';
    menu_item_to_fill->price = price;

    return 1;
}