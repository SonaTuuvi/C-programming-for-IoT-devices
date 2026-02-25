#include <stdio.h>      // for printf, fprintf, fgets, fopen, fclose, snprintf
#include <stdlib.h>     // for exit, strtod
#include <string.h>     // for strcspn, strlen, strchr, strncpy
#include <ctype.h>      // for isspace
#include "Exercise_15.h"

/*
 * -------------------------------------------------------------
 * Author:      Sona (patient explainer mode)
 * File:        Exercise_15.c
 * -------------------------------------------------------------
 *
 * MISSION: Read a menu from file, store it neatly, print it nicely
 *
 * TASK (Ex15):
 *  - Read data from a text file into an array of structures.
 *  - The array has 40 elements.
 *
 * Structure definition (given in task):
 *      typedef struct menu_item_ {
 *          char name[50];
 *          double price;
 *      } menu_item;
 *
 * File format:
 *  - Each line contains one menu item.
 *  - Members are separated by a semicolon.
 *  - Example line:
 *        Mega double burger with bacon and cheese; 23.50
 *
 * Program steps:
 *      Ask user for filename.
 *      Open file for reading ("r").
 *       - If open fails: print error to stderr + exit.
 *      Read lines until:
 *        - end of file, OR
 *        - array is full (40 items)
 *      Close file.
 *      Print the content in formatted columns:
 *        - price is field width 8, two decimals
 *        - followed by item name
 *      Do not print unused elements.
 *
 * EXTRA FEATURE (same as Ex13/Ex14):
 *  - If user types only "menu.txt",
 *    we also try common locations:
 *        Exercise_15/menu.txt
 *        ../Exercise_15/menu.txt
 *        ../../Exercise_15/menu.txt
 *
 * Because IDE working directories like to prank students.
 * -------------------------------------------------------------
 */


/*
 * -------------------------------------------------------------
 * Constants
 * -------------------------------------------------------------
 */

#define MAX_MENU_ITEMS 40
#define MAX_NAME_LENGTH 50

#define EXERCISE_FOLDER_NAME "Exercise_15"


/*
 * -------------------------------------------------------------
 * Structure definition
 * -------------------------------------------------------------
 */
typedef struct menu_item_
{
    char name[MAX_NAME_LENGTH];
    double price;
} menu_item;

/*
 * -------------------------------------------------------------
 * Function declarations (prototypes)
 * -------------------------------------------------------------
 */

static void clear_input_buffer(void);

static int read_filename_from_user(
            char *filename_buffer,
            int buffer_size);

static FILE* open_file_for_reading_or_exit_program(
            const char *filename_from_user);

static FILE* try_open_reading_with_guess_paths(
            const char *filename_from_user);

static int read_menu_items_from_file(
            FILE *opened_file,
            menu_item menu_items_array[MAX_MENU_ITEMS]);

static int parse_line_into_menu_item(
            const char *line_from_file,
            menu_item *menu_item_to_fill);

static void print_menu_items_in_columns(
            const menu_item menu_items_array[MAX_MENU_ITEMS],
            int total_items_read);

/* A tiny helper: remove leading/trailing spaces from a string in-place */
static void trim_whitespace_in_place(char *text_to_trim);


/*
 * -------------------------------------------------------------
 * Function: run_exercise_15
 * -------------------------------------------------------------
 * This is the main function of this exercise.
 * It is called from main() through the menu.
 * -------------------------------------------------------------
 */
void run_exercise_15(void)
{
    char filename_buffer[256];
    FILE *opened_file = NULL;

    menu_item menu_items_array[MAX_MENU_ITEMS];
    int total_items_read = 0;

    /*
     * If the menu previously used scanf,
     * there might be a leftover newline in input buffer.
     * We remove it so fgets works correctly.
     */
    clear_input_buffer();

    /*
     * Ask the user for filename.
     */
    if (!read_filename_from_user(filename_buffer,
                                 sizeof(filename_buffer)))
    {
        printf("Input failed.\n");
        return;
    }

    /*
     * STEP 1:
     * Open file for reading.
     */
    opened_file =
        open_file_for_reading_or_exit_program(filename_buffer);

    /*
     * STEP 2:
     * Read items into the array.
     */
    total_items_read =
        read_menu_items_from_file(opened_file, menu_items_array);

    /*
     * STEP 3:
     * Close file when done reading.
     */
    fclose(opened_file);

    /*
     * STEP 4:
     * Print results in formatted columns.
     * Unused elements are not printed because we only print [0..total_items_read-1].
     */
    print_menu_items_in_columns(menu_items_array, total_items_read);
}


/*
 * -------------------------------------------------------------
 * Function: clear_input_buffer
 * -------------------------------------------------------------
 * Removes characters from stdin until newline or EOF.
 * Useful when switching from scanf() to fgets().
 * -------------------------------------------------------------
 */
static void clear_input_buffer(void)
{
    int leftover_character;

    while ((leftover_character = getchar()) != '\n' &&
           leftover_character != EOF)
    {
        /* discard quietly */
    }
}


/*
 * -------------------------------------------------------------
 * Function: read_filename_from_user
 * -------------------------------------------------------------
 * Reads a filename safely using fgets.
 *
 * Returns:
 *      1 -> success
 *      0 -> failure
 * -------------------------------------------------------------
 */
static int read_filename_from_user(
            char *filename_buffer,
            int buffer_size)
{
    printf("Enter filename:\n");

    if (fgets(filename_buffer,
              buffer_size,
              stdin) == NULL)
    {
        return 0;
    }

    /*
     * Remove newline if present.
     */
    filename_buffer[
        strcspn(filename_buffer, "\n")] = '\0';

    /*
     * Empty input is not a useful filename.
     */
    if (strlen(filename_buffer) == 0)
        return 0;

    return 1;
}


/*
 * -------------------------------------------------------------
 * Function: try_open_reading_with_guess_paths
 * -------------------------------------------------------------
 * Tries to open a file for reading.
 *
 * It tries:
 *   1) filename_from_user
 *
 * If user typed ONLY a filename (no / or \\),
 * it also tries:
 *   2) Exercise_15/<filename>
 *   3) ../Exercise_15/<filename>
 *   4) ../../Exercise_15/<filename>
 *
 * Returns:
 *   - FILE* if success
 *   - NULL  if all attempts fail
 * -------------------------------------------------------------
 */
static FILE* try_open_reading_with_guess_paths(
            const char *filename_from_user)
{
    FILE *temporary_file_pointer = NULL;

    /*
     * Try exactly what user typed first.
     */
    temporary_file_pointer =
        fopen(filename_from_user, "r");

    if (temporary_file_pointer != NULL)
        return temporary_file_pointer;

    /*
     * If user already typed a path (contains / or \\),
     * do not guess additional paths.
     */
    if (strchr(filename_from_user, '/') != NULL ||
        strchr(filename_from_user, '\\') != NULL)
    {
        return NULL;
    }

    /*
     * Guess common locations relative to working directory.
     */
    {
        char guessed_full_path[512];

        snprintf(guessed_full_path,
                 sizeof(guessed_full_path),
                 EXERCISE_FOLDER_NAME "/%s",
                 filename_from_user);

        temporary_file_pointer =
            fopen(guessed_full_path, "r");

        if (temporary_file_pointer != NULL)
            return temporary_file_pointer;

        snprintf(guessed_full_path,
                 sizeof(guessed_full_path),
                 "../" EXERCISE_FOLDER_NAME "/%s",
                 filename_from_user);

        temporary_file_pointer =
            fopen(guessed_full_path, "r");

        if (temporary_file_pointer != NULL)
            return temporary_file_pointer;

        snprintf(guessed_full_path,
                 sizeof(guessed_full_path),
                 "../../" EXERCISE_FOLDER_NAME "/%s",
                 filename_from_user);

        temporary_file_pointer =
            fopen(guessed_full_path, "r");

        if (temporary_file_pointer != NULL)
            return temporary_file_pointer;
    }

    return NULL;
}


/*
 * -------------------------------------------------------------
 * Function: open_file_for_reading_or_exit_program
 * -------------------------------------------------------------
 * Opens the file in read mode.
 * If it fails, print to stderr and exit.
 * -------------------------------------------------------------
 */
static FILE* open_file_for_reading_or_exit_program(
            const char *filename_from_user)
{
    FILE *temporary_file_pointer =
        try_open_reading_with_guess_paths(filename_from_user);

    if (temporary_file_pointer == NULL)
    {
        fprintf(stderr,
                "Error: cannot open file \"%s\" for reading.\n",
                filename_from_user);

        fprintf(stderr,
                "Hint: If you typed only a filename, I also tried:\n"
                "      " EXERCISE_FOLDER_NAME "/%s\n"
                "      ../" EXERCISE_FOLDER_NAME "/%s\n"
                "      ../../" EXERCISE_FOLDER_NAME "/%s\n"
                "But the file is still playing hide and seek.\n",
                filename_from_user,
                filename_from_user,
                filename_from_user);

        exit(1);
    }

    return temporary_file_pointer;
}


/*
 * -------------------------------------------------------------
 * Function: read_menu_items_from_file
 * -------------------------------------------------------------
 * Reads lines from file and converts each line into one menu_item.
 *
 * Stops when:
 *  - end of file
 *  - array is full (MAX_MENU_ITEMS)
 *
 * Returns:
 *  - number of menu items successfully read and parsed
 * -------------------------------------------------------------
 */
static int read_menu_items_from_file(
            FILE *opened_file,
            menu_item menu_items_array[MAX_MENU_ITEMS])
{
    char line_buffer[256];
    int total_items_read = 0;

    /*
     * Read file line by line.
     * Each line is expected to look like:
     *      Name of item; 12.34
     */
    while (total_items_read < MAX_MENU_ITEMS)
    {
        if (fgets(line_buffer,
                  sizeof(line_buffer),
                  opened_file) == NULL)
        {
            /*
             * NULL means end-of-file (most common) or read error.
             * For this exercise, end-of-file is normal.
             */
            break;
        }

        /*
         * Try to parse this line into a menu item.
         * If parsing fails, we skip the line (we do not crash).
         * Because one broken line should not ruin your whole day.
         */
        if (parse_line_into_menu_item(line_buffer,
                                      &menu_items_array[total_items_read]))
        {
            total_items_read++;
        }
        else
        {
            /*
             * Optional: print a warning about the bad line.
             * (You can comment this out if you prefer silence.)
             */
            fprintf(stderr,
                    "Warning: skipping invalid line: %s",
                    line_buffer);
        }
    }

    return total_items_read;
}


/*
 * -------------------------------------------------------------
 * Function: parse_line_into_menu_item
 * -------------------------------------------------------------
 * Converts one text line into a menu_item structure.
 *
 * Expected line format:
 *      name; price
 *
 * Example:
 *      Mega double burger with bacon and cheese; 23.50
 *
 * Returns:
 *      1 -> success
 *      0 -> failure (missing ';', missing price, etc.)
 * -------------------------------------------------------------
 */
static int parse_line_into_menu_item(
            const char *line_from_file,
            menu_item *menu_item_to_fill)
{
    char local_copy_of_line[256];
    char *semicolon_position = NULL;

    char *name_part_pointer = NULL;
    char *price_part_pointer = NULL;

    char *price_parse_end_pointer = NULL;
    double parsed_price = 0.0;

    /*
     * We copy the line into a local buffer because:
     *  - we want to modify it (insert '\0' at semicolon)
     *  - modifying the original const char* is not allowed
     */
    strncpy(local_copy_of_line, line_from_file, sizeof(local_copy_of_line) - 1);
    local_copy_of_line[sizeof(local_copy_of_line) - 1] = '\0';

    /*
     * Remove newline at end, if present.
     * (fgets often keeps '\n' in the string.)
     */
    local_copy_of_line[strcspn(local_copy_of_line, "\n")] = '\0';

    /*
     * Find the semicolon that separates name and price.
     */
    semicolon_position = strchr(local_copy_of_line, ';');
    if (semicolon_position == NULL)
    {
        return 0;
    }

    /*
     * Split into two strings:
     *  name_part  -> before ';'
     *  price_part -> after ';'
     *
     * We replace ';' with '\0' so the name becomes a normal C-string.
     */
    *semicolon_position = '\0';

    name_part_pointer = local_copy_of_line;
    price_part_pointer = semicolon_position + 1;

    /*
     * Trim spaces from both parts.
     * (Because humans love adding random spaces.)
     */
    trim_whitespace_in_place(name_part_pointer);
    trim_whitespace_in_place(price_part_pointer);

    /*
     * Validate name.
     */
    if (strlen(name_part_pointer) == 0)
    {
        return 0;
    }

    /*
     * Convert price string into double.
     * strtod is safer than atof because it tells where parsing stopped.
     */
    parsed_price = strtod(price_part_pointer, &price_parse_end_pointer);

    /*
     * If price_parse_end_pointer == price_part_pointer,
     * it means no conversion happened (not a number).
     */
    if (price_parse_end_pointer == price_part_pointer)
    {
        return 0;
    }

    /*
     * Store data into structure.
     *
     * Name:
     *  - max 49 characters + '\0'
     *  - We use strncpy to avoid overflow.
     */
    strncpy(menu_item_to_fill->name,
            name_part_pointer,
            MAX_NAME_LENGTH - 1);

    menu_item_to_fill->name[MAX_NAME_LENGTH - 1] = '\0';

    menu_item_to_fill->price = parsed_price;

    return 1;
}


/*
 * -------------------------------------------------------------
 * Helper: trim_whitespace_in_place
 * -------------------------------------------------------------
 * Removes leading and trailing whitespace from a string.
 *
 * Example:
 *   "   coffee   "  -> "coffee"
 *
 * This is done in-place (we modify the same buffer).
 * -------------------------------------------------------------
 */
static void trim_whitespace_in_place(char *text_to_trim)
{
    int start_index = 0;
    int end_index = 0;
    int string_length = 0;

    if (text_to_trim == NULL)
        return;

    string_length = (int)strlen(text_to_trim);
    if (string_length == 0)
        return;

    /*
     * Find first non-space character.
     */
    while (text_to_trim[start_index] != '\0' &&
           isspace((unsigned char)text_to_trim[start_index]))
    {
        start_index++;
    }

    /*
     * If the string was all spaces, make it empty.
     */
    if (text_to_trim[start_index] == '\0')
    {
        text_to_trim[0] = '\0';
        return;
    }

    /*
     * Find last non-space character.
     */
    end_index = string_length - 1;
    while (end_index >= 0 &&
           isspace((unsigned char)text_to_trim[end_index]))
    {
        end_index--;
    }

    /*
     * Now we have:
     *   start_index -> first useful char
     *   end_index   -> last useful char
     *
     * We shift the text left if needed.
     */
    if (start_index > 0)
    {
        int write_index = 0;
        while (text_to_trim[start_index] != '\0')
        {
            text_to_trim[write_index] = text_to_trim[start_index];
            write_index++;
            start_index++;
        }
        text_to_trim[write_index] = '\0';
    }

    /*
     * Recalculate length after possible left shift.
     */
    string_length = (int)strlen(text_to_trim);
    end_index = string_length - 1;

    /*
     * Cut trailing spaces by placing '\0' after the last useful char.
     */
    while (end_index >= 0 &&
           isspace((unsigned char)text_to_trim[end_index]))
    {
        text_to_trim[end_index] = '\0';
        end_index--;
    }
}


/*
 * -------------------------------------------------------------
 * Function: print_menu_items_in_columns
 * -------------------------------------------------------------
 * Prints the menu items in formatted columns.
 *
 * Requirement:
 *  - Price printed in a field of 8 characters with two decimals
 *  - Followed by the name of the item
 *
 * Example output:
 *    23.50  Mega double burger with bacon and cheese
 *
 * We print only items that were actually read.
 * -------------------------------------------------------------
 */
static void print_menu_items_in_columns(
            const menu_item menu_items_array[MAX_MENU_ITEMS],
            int total_items_read)
{
    int item_index;

    if (total_items_read <= 0)
    {
        printf("No menu items were read from the file.\n");
        return;
    }

    for (item_index = 0; item_index < total_items_read; item_index++)
    {
        printf("%8.2f  %s\n",
               menu_items_array[item_index].price,
               menu_items_array[item_index].name);
    }
}