#include <stdio.h>      // for printf, fprintf, fgets, fputs, fopen, fclose, snprintf
#include <stdlib.h>     // for exit
#include <string.h>     // for strcspn, strlen, strchr
#include <ctype.h>      // for toupper
#include "Exercise_14.h"

/*
 * -------------------------------------------------------------
 * Author:      Sona (patient explainer mode)
 * Date:        25.02.2026
 * Mission:     Read text, reshape it, return it louder (turn ordinary text into uppercase power).
 * -------------------------------------------------------------
 *
 * TASK:
 *  - Read lines of text into an array of strings.
 *  - Maximum line length: 80 characters
 *  - Maximum number of lines: 100
 *
 * Program steps:
 *      Ask user for filename.
 *      Open file for reading ("r").
 *          - If opening fails: print error to stderr and exit.
 *      Read lines until:
 *          - end of file, OR
 *          - 100 lines read (array full)
 *      Close file.
 *      Convert all letters to uppercase (toupper()).
 *      Open same file for writing ("w") (overwrites file).
 *      Write lines back to file.
 *      Close file.
 *
 * EXTRA FEATURE:
 *  - If user types only "Exercise_14.txt",
 *    we also try common locations:
 *        Exercise_14/Exercise_14.txt
 *        ../Exercise_14/Exercise_14.txt
 *        ../../Exercise_14/Exercise_14.txt
 *
 * Why? Because IDE working directories like to prank us.
 * -------------------------------------------------------------
 *
 * IMPORTANT FIX (why it didn’t overwrite before):
 *  - The program might READ from a guessed path (like ../Exercise_14/...)
 *  - But then WRITE using only what the user typed.
 *  - Result: two different files.
 *
 * Solution:
 *  - Remember the real path that successfully opened.
 *  - Write back to THAT exact path.
 * -------------------------------------------------------------
 */


/*
 * -------------------------------------------------------------
 * Constants for this exercise
 * -------------------------------------------------------------
 */

#define MAX_LINE_LENGTH 80
#define MAX_LINES 100

#define EXERCISE_FOLDER_NAME "Exercise_14"


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
            const char *filename_from_user,
            char *resolved_path,
            int resolved_path_size);

static FILE* open_file_for_writing_or_exit_program(
            const char *resolved_path);

static FILE* try_open_reading_with_guess_paths(
            const char *filename_from_user,
            char *resolved_path,
            int resolved_path_size);

static int read_lines_into_array(
            FILE *opened_file,
            char lines_array[MAX_LINES][MAX_LINE_LENGTH + 2]);

static void convert_all_lines_to_uppercase(
            char lines_array[MAX_LINES][MAX_LINE_LENGTH + 2],
            int total_lines_read);

static void write_lines_back_to_file(
            FILE *opened_file,
            char lines_array[MAX_LINES][MAX_LINE_LENGTH + 2],
            int total_lines_to_write);

/*
 * -------------------------------------------------------------
 * Function: run_exercise_14
 * -------------------------------------------------------------
 * This is the main function for this exercise.
 * It is called from main() through the menu.
 * -------------------------------------------------------------
 */
void run_exercise_14(void)
{

    char filename_buffer[256];

    /*
     * resolved_path:
     *   This will store the REAL path of the file we opened.
     *   Not just what the user typed.
     *
     * Why do we need this?
     *   Because IDE working directories like to play hide and seek.
     */
    char resolved_path[512];

    /*
     * lines_array:
     *   We store up to 100 lines.
     *
     *   Each line can be up to 80 characters.
     *
     * Why +2?
     *   - +1 for '\n' (newline) if it exists in the file
     *   - +1 for '\0' (string terminator)
     */
    char lines_array[MAX_LINES][MAX_LINE_LENGTH + 2];

    FILE *opened_file = NULL;
    int total_lines_read = 0;

    /*
     * If the menu used scanf earlier,
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
     * Open file for reading.
     */
    opened_file =
        open_file_for_reading_or_exit_program(
            filename_buffer,
            resolved_path,
            sizeof(resolved_path));

    /*
     * Read lines into array.
     */
    total_lines_read =
        read_lines_into_array(opened_file, lines_array);

    /*
     * Close after reading.
     */
    fclose(opened_file);

    /*
     * Convert all letters to uppercase.
     */
    convert_all_lines_to_uppercase(lines_array, total_lines_read);

    /*
     * Open same file for writing ("w").
     * WARNING:
     *   "w" overwrites the file.
     *   That is what the task asks for.
     */
    opened_file =
        open_file_for_writing_or_exit_program(resolved_path);

    /*
     * Write all stored lines back into the file.
     */
    write_lines_back_to_file(opened_file, lines_array, total_lines_read);

    /*
     * Close after writing.
     */
    fclose(opened_file);

    printf("Done. %d line(s) were converted to uppercase and written back.\n",
           total_lines_read);
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
 * This helper tries to open a file for reading.
 *
 * Updated logic:
 *   If user typed ONLY a filename (no / or \\),
 *   we FIRST try to open it from Exercise_14 folder
 *   (source directory structure),
 *   and ONLY AFTER THAT try the local working directory.
 *
 * Why?
 *   Because CMake copies Exercise_14.txt into build folder,
 *   and without this change the program would always open
 *   the build copy instead of the original source file.
 *
 * Returns:
 *   - FILE* if success
 *   - NULL  if all attempts fail
 * -------------------------------------------------------------
 */
static FILE* try_open_reading_with_guess_paths(
            const char *filename_from_user,
            char *resolved_path,
            int resolved_path_size)
{
    FILE *temporary_file_pointer = NULL;

    /*
     * If user already typed a path (contains / or \\),
     * do NOT guess anything.
     * Just try exactly what they typed.
     */
    if (strchr(filename_from_user, '/') != NULL ||
        strchr(filename_from_user, '\\') != NULL)
    {
        temporary_file_pointer =
            fopen(filename_from_user, "r");

        if (temporary_file_pointer != NULL)
        {
            snprintf(resolved_path,
                     resolved_path_size,
                     "%s",
                     filename_from_user);

            return temporary_file_pointer;
        }

        return NULL;
    }

    /*
     * User typed only a filename.
     *
     * IMPORTANT:
     *   We FIRST try source-style paths,
     *   and ONLY AFTER that try local working directory.
     *
     *   This ensures the original Exercise_14.txt
     *   (inside Exercise_14 folder) is used,
     *   not the copied one in build directory.
     */

    {
        char guessed_full_path[512];

        /*
         * 1) Try: Exercise_14/<filename>
         */
        snprintf(guessed_full_path,
                 sizeof(guessed_full_path),
                 EXERCISE_FOLDER_NAME "/%s",
                 filename_from_user);

        temporary_file_pointer =
            fopen(guessed_full_path, "r");

        if (temporary_file_pointer != NULL)
        {
            snprintf(resolved_path,
                     resolved_path_size,
                     "%s",
                     guessed_full_path);

            return temporary_file_pointer;
        }

        /*
         * 2) Try: ../Exercise_14/<filename>
         */
        snprintf(guessed_full_path,
                 sizeof(guessed_full_path),
                 "../" EXERCISE_FOLDER_NAME "/%s",
                 filename_from_user);

        temporary_file_pointer =
            fopen(guessed_full_path, "r");

        if (temporary_file_pointer != NULL)
        {
            snprintf(resolved_path,
                     resolved_path_size,
                     "%s",
                     guessed_full_path);

            return temporary_file_pointer;
        }

        /*
         * 3) Try: ../../Exercise_14/<filename>
         */
        snprintf(guessed_full_path,
                 sizeof(guessed_full_path),
                 "../../" EXERCISE_FOLDER_NAME "/%s",
                 filename_from_user);

        temporary_file_pointer =
            fopen(guessed_full_path, "r");

        if (temporary_file_pointer != NULL)
        {
            snprintf(resolved_path,
                     resolved_path_size,
                     "%s",
                     guessed_full_path);

            return temporary_file_pointer;
        }
    }

    /*
     * LAST RESORT:
     *   Try exactly what user typed
     *   (this will open build copy if it exists there).
     */
    temporary_file_pointer =
        fopen(filename_from_user, "r");

    if (temporary_file_pointer != NULL)
    {
        snprintf(resolved_path,
                 resolved_path_size,
                 "%s",
                 filename_from_user);

        return temporary_file_pointer;
    }

    /*
     * If we reach this point,
     * file is still hiding from us.
     */
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
            const char *filename_from_user,
            char *resolved_path,
            int resolved_path_size)
{
    FILE *temporary_file_pointer =
        try_open_reading_with_guess_paths(
            filename_from_user,
            resolved_path,
            resolved_path_size);

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
 * Function: open_file_for_writing_or_exit_program
 * -------------------------------------------------------------
 * Opens the file in write mode ("w").
 *
 * IMPORTANT:
 *  - "w" overwrites the file.
 *  - This is expected in this exercise.
 *
 * If it fails, print to stderr and exit.
 * -------------------------------------------------------------
 */
static FILE* open_file_for_writing_or_exit_program(
            const char *resolved_path)
{
    FILE *temporary_file_pointer =
        fopen(resolved_path, "w");

    if (temporary_file_pointer == NULL)
    {
        fprintf(stderr,
                "Error: cannot open file \"%s\" for writing.\n",
                resolved_path);

        fprintf(stderr,
                "Possible reasons:\n"
                "  - wrong path\n"
                "  - no write permission\n"
                "  - file is protected by mysterious forces\n");

        exit(1);
    }

    return temporary_file_pointer;
}


/*
 * -------------------------------------------------------------
 * Function: read_lines_into_array
 * -------------------------------------------------------------
 * Reads lines from file into array.
 *
 * Stops when:
 *  - fgets returns NULL (EOF or error)
 *  - OR we already read MAX_LINES lines
 *
 * Returns:
 *  - number of lines read
 * -------------------------------------------------------------
 */
static int read_lines_into_array(
            FILE *opened_file,
            char lines_array[MAX_LINES][MAX_LINE_LENGTH + 2])
{
    int total_lines_read = 0;

    while (total_lines_read < MAX_LINES)
    {
        if (fgets(lines_array[total_lines_read],
                  (MAX_LINE_LENGTH + 2),
                  opened_file) == NULL)
        {
            /*
             * NULL usually means end-of-file.
             * That is totally fine here.
             */
            break;
        }

        total_lines_read++;
    }

    return total_lines_read;
}


/*
 * -------------------------------------------------------------
 * Function: convert_all_lines_to_uppercase
 * -------------------------------------------------------------
 * Converts every character in every line to uppercase.
 *
 * We use toupper() from <ctype.h>.
 *
 * NOTE:
 *  - We cast to (unsigned char) before toupper.
 *    This avoids undefined behavior for negative char values.
 * -------------------------------------------------------------
 */
static void convert_all_lines_to_uppercase(
            char lines_array[MAX_LINES][MAX_LINE_LENGTH + 2],
            int total_lines_read)
{
    int line_index;

    for (line_index = 0; line_index < total_lines_read; line_index++)
    {
        int character_index = 0;

        while (lines_array[line_index][character_index] != '\0')
        {
            unsigned char current_character =
                (unsigned char)lines_array[line_index][character_index];

            lines_array[line_index][character_index] =
                (char)toupper(current_character);

            character_index++;
        }
    }
}


/*
 * -------------------------------------------------------------
 * Function: write_lines_back_to_file
 * -------------------------------------------------------------
 * Writes all stored lines back to the file.
 *
 * Parameters:
 *   opened_file          - already opened FILE* in write mode ("w")
 *   lines_array          - array containing all processed lines
 *   total_lines_to_write - number of valid lines in the array
 *
 * Important details:
 *   - We assume the file was opened successfully before.
 *   - Mode "w" overwrites the file completely.
 *   - Each line may or may not already contain '\n'.
 *     We do NOT add newline automatically.
 * -------------------------------------------------------------
 */
static void write_lines_back_to_file(
            FILE *opened_file,
            char lines_array[MAX_LINES][MAX_LINE_LENGTH + 2],
            int total_lines_to_write)
{
    int line_index;

    /*
     * Iterate through all valid lines in the array.
     */
    for (line_index = 0;
         line_index < total_lines_to_write;
         line_index++)
    {
        /*
         * fputs writes a null-terminated string to the file.
         *
         * It does NOT automatically append '\n'.
         * So if the string already contains newline,
         * it will be written.
         */
        if (fputs(lines_array[line_index],
                  opened_file) == EOF)
        {
            /*
             * If fputs returns EOF,
             * something went wrong during writing.
             */
            perror("fputs failed");
        }
    }

    /*
     * After writing all lines,
     * check the file stream error indicator.
     *
     * ferror() returns non-zero
     * if a write error occurred.
     */
    if (ferror(opened_file))
    {
        perror("write error");
    }

    /*
     * fflush forces buffered data to be written
     * from memory buffer to the actual file.
     *
     * Why useful?
     *   - Ensures data is physically pushed out
     *     before fclose().
     *   - Helpful during debugging.
     *
     * Note:
     *   fclose() would also flush automatically,
     *   but explicit fflush() makes the intention clear.
     */
    fflush(opened_file);
}


