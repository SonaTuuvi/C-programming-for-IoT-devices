#include <stdio.h>      // for printf, fprintf, fgets, fscanf, fopen, fclose
#include <stdlib.h>     // for exit
#include <limits.h>     // for INT_MAX and INT_MIN
#include <string.h>     // for strcspn and strlen
#include "Exercise_13.h"

/*
 * -------------------------------------------------------------
 * Author:      Sona (patient explainer mode)
 * Date:        25.02.2026
 * Mission:     Read integers, analyze them, reveal the extremes
 * -------------------------------------------------------------
 *
 * This program:
 *  1. Asks the user to enter a filename.
 *  2. Tries to open the file in read mode.
 *  3. Reads integers from the file one by one.
 *  4. Counts how many integers were found.
 *  5. Determines the smallest and largest integer.
 *  6. Prints the results.
 *  7. Closes the file.
 *
 * If the file cannot be opened:
 *      prints error to stderr
 *      exits the program immediately
 *
 * -------------------------------------------------------------
 */


/*
 * -------------------------------------------------------------
 * Function declarations
 * -------------------------------------------------------------
 * These are "prototypes".
 * They tell the compiler that these functions exist below.
 * -------------------------------------------------------------
 */

static void clear_input_buffer(void);

static int read_filename_from_user(
            char *filename_buffer,
            int buffer_size);

static FILE* open_file_or_exit_program(
            const char *filename_from_user);

static void process_file_and_collect_statistics(
            FILE *opened_file,
            int *total_numbers_found,
            int *smallest_number_found,
            int *largest_number_found);


/*
 * -------------------------------------------------------------
 * Function: run_exercise_13
 * -------------------------------------------------------------
 * This is the main function of this exercise.
 * It is called from main() through the menu.
 * -------------------------------------------------------------
 */
void run_exercise_13(void)
{
    /*
     * filename_buffer:
     * stores the filename entered by the user.
     * 256 characters is usually more than enough.
     */
    char filename_buffer[256];

    /*
     * opened_file:
     * this is a pointer to FILE.
     * It will point to the opened file after fopen().
     */
    FILE *opened_file = NULL;

    /*
     * total_numbers_found:
     * counts how many integers we successfully read.
     */
    int total_numbers_found = 0;

    /*
     * smallest_number_found:
     * initialized to the largest possible int.
     * That way the first real number from file
     * will automatically be smaller and replace it.
     */
    int smallest_number_found = INT_MAX;

    /*
     * largest_number_found:
     * initialized to the smallest possible int.
     * That way the first real number will replace it.
     */
    int largest_number_found = INT_MIN;

    /*
     * If the menu previously used scanf,
     * there might be a leftover newline in input buffer.
     * We remove it so fgets works correctly.
     */
    clear_input_buffer();

    /*
     * Ask the user for filename.
     * If something goes wrong, stop function.
     */
    if (!read_filename_from_user(filename_buffer,
                                 sizeof(filename_buffer)))
    {
        printf("Input failed.\n");
        return;
    }

    /*
     * Try to open the file.
     * If opening fails, this function prints error
     * and exits the program completely.
     */
    opened_file =
        open_file_or_exit_program(filename_buffer);

    /*
     * Read integers from the file.
     * This function updates:
     *      total_numbers_found
     *      smallest_number_found
     *      largest_number_found
     *
     * We pass their addresses using &,
     * so the function can modify the original variables.
     */
    process_file_and_collect_statistics(
            opened_file,
            &total_numbers_found,
            &smallest_number_found,
            &largest_number_found);

    /*
     * After reading is finished,
     * check whether we found any integers.
     */
    if (total_numbers_found == 0)
    {
        printf("No integers were found in the file.\n");
    }
    else
    {
        printf("Total numbers found: %d\n",
               total_numbers_found);

        printf("Smallest number found: %d\n",
               smallest_number_found);

        printf("Largest number found: %d\n",
               largest_number_found);
    }

    /*
     * Always close the file when finished.
     * This releases system resources.
     */
    fclose(opened_file);
}

/*
 * -------------------------------------------------------------
 * Function: clear_input_buffer
 * -------------------------------------------------------------
 * Removes all characters from input until:
 *      newline ('\n')
 *      or end-of-file (EOF)
 *
 * This prevents accidental empty input.
 * -------------------------------------------------------------
 */
static void clear_input_buffer(void)
{
    int leftover_character;

    /*
     * getchar() reads one character at a time.
     * We keep reading and ignoring characters
     * until we reach newline or EOF.
     */
    while ((leftover_character = getchar()) != '\n' &&
           leftover_character != EOF)
    {
        /* do nothing, just discard */
    }
}


/*
 * -------------------------------------------------------------
 * Function: read_filename_from_user
 * -------------------------------------------------------------
 * Prompts the user to enter filename.
 * Uses fgets for safe reading.
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

    /*
     * fgets reads at most buffer_size - 1 characters
     * and automatically adds '\0' at the end.
     */
    if (fgets(filename_buffer,
              buffer_size,
              stdin) == NULL)
    {
        return 0;
    }

    /*
     * Remove newline character if present.
     * strcspn finds index of '\n'.
     */
    filename_buffer[
        strcspn(filename_buffer, "\n")] = '\0';

    /*
     * If the string is empty,
     * consider it invalid input.
     */
    if (strlen(filename_buffer) == 0)
        return 0;

    return 1;
}

/*
 * -------------------------------------------------------------
 * Function: open_file_or_exit_program
 * -------------------------------------------------------------
 *
 * This function attempts to open a file in read mode ("r").
 *
 * fopen returns:
 *      pointer to FILE  -> if success
 *      NULL             -> if failure
 *
 * In normal situations:
 *      we try to open exactly what the user typed.
 *
 * However...
 * In IDEs like CLion, the program often runs from
 * a build folder (for example: cmake-build-debug).
 *
 * That means that even if the file exists in:
 *      Exercise_13/Exercise_13.txt
 *
 * fopen("Exercise_13.txt", "r")
 * might fail — because the working directory is different.
 *
 * So we try multiple reasonable locations automatically.
 *
 * If all attempts fail:
 *      print error to stderr
 *      exit program with status 1
 *
 * -------------------------------------------------------------
 */
static FILE* open_file_or_exit_program(
            const char *filename_from_user)
{
    FILE *temporary_file_pointer;
    /*
     * ---------------------------------------------------------
     * Try to open the file exactly as user entered it.
     * ---------------------------------------------------------
     */
    temporary_file_pointer =
        fopen(filename_from_user, "r");

    if (temporary_file_pointer != NULL)
    {
        /*
         * Success.
         * No need to try anything else.
         */
        return temporary_file_pointer;
    }
    /*
     * ---------------------------------------------------------
     * If the user typed only a filename (no slashes),
     * we try common project locations.
     *
     * We check for '/' and '\\' because:
     *      '/'  -> Linux / macOS path separator
     *      '\\' -> Windows path separator
     *
     * If either is present, we assume the user already
     * provided a full or relative path intentionally.
     * ---------------------------------------------------------
     */
    if (strchr(filename_from_user, '/') == NULL &&
        strchr(filename_from_user, '\\') == NULL)
    {
        char guessed_full_path[512];

        /*
         * -----------------------------------------------------
         * Try: Exercise_13/<filename>
         *
         * This works if program runs from project root.
         * -----------------------------------------------------
         */
        snprintf(guessed_full_path,
                 sizeof(guessed_full_path),
                 "Exercise_13/%s",
                 filename_from_user);

        temporary_file_pointer =
            fopen(guessed_full_path, "r");

        if (temporary_file_pointer != NULL)
        {
            return temporary_file_pointer;
        }
        /*
         * -----------------------------------------------------
         * Try: ../Exercise_13/<filename>
         *
         * This works if program runs from cmake-build-debug.
         * "../" means:
         *      go one directory up.
         * -----------------------------------------------------
         */
        snprintf(guessed_full_path,
                 sizeof(guessed_full_path),
                 "../Exercise_13/%s",
                 filename_from_user);

        temporary_file_pointer =
            fopen(guessed_full_path, "r");

        if (temporary_file_pointer != NULL)
        {
            return temporary_file_pointer;
        }
        /*
         * -----------------------------------------------------
         * Try: ../../Exercise_13/<filename>
         *
         * "../../" means:
         *      go two directories up.
         *
         * Sometimes build folders are nested deeper.
         * -----------------------------------------------------
         */
        snprintf(guessed_full_path,
                 sizeof(guessed_full_path),
                 "../../Exercise_13/%s",
                 filename_from_user);

        temporary_file_pointer =
            fopen(guessed_full_path, "r");

        if (temporary_file_pointer != NULL)
        {
            return temporary_file_pointer;
        }
    }
    /*
     * ---------------------------------------------------------
     * If we reach this point,
     * all attempts failed.
     *
     * The file truly could not be found.
     * ---------------------------------------------------------
     */
    fprintf(stderr,
            "Error: cannot open file \"%s\"\n",
            filename_from_user);

    fprintf(stderr,
            "The file was not found in expected locations.\n");

    exit(1);
}

/*
 * -------------------------------------------------------------
 * Function: process_file_and_collect_statistics
 * -------------------------------------------------------------
 * Reads integers using fscanf.
 *
 * fscanf returns:
 *      1  -> successfully read integer
 *      0  -> invalid input
 *      EOF -> end of file
 *
 * We continue only while fscanf returns 1.
 * -------------------------------------------------------------
 */
static void process_file_and_collect_statistics(
            FILE *opened_file,
            int *total_numbers_found,
            int *smallest_number_found,
            int *largest_number_found)
{
    int current_number_from_file;

    /*
     * Loop continues while reading integer succeeds.
     */
    while (fscanf(opened_file,
                  "%d",
                  &current_number_from_file) == 1)
    {
        /*
         * Increase counter.
         * We use * because we received pointer.
         */
        (*total_numbers_found)++;

        /*
         * If current number is smaller than current minimum,
         * update minimum.
         */
        if (current_number_from_file <
            *smallest_number_found)
        {
            *smallest_number_found =
                current_number_from_file;
        }

        /*
         * If current number is larger than current maximum,
         * update maximum.
         */
        if (current_number_from_file >
            *largest_number_found)
        {
            *largest_number_found =
                current_number_from_file;
        }
    }
}