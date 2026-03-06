#include "Exercise_21.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define EX21_FOLDER "Exercise_21"

/*-------------------------------------------------------------
Helper functions for checksum calculation

These functions help validate NMEA sentences by calculating
and comparing XOR checksums.
-------------------------------------------------------------*/


/*-------------------------------------------------------------
Function: hex_to_int

Converts a hexadecimal character to its integer value.
Example: 'A' -> 10, 'F' -> 15, '9' -> 9
Returns -1 if the character is not a valid hex digit.
-------------------------------------------------------------*/
static int hex_to_int(int ch)
{
    if ('0' <= ch && ch <= '9') return ch - '0';
    if ('a' <= ch && ch <= 'f') return 10 + (ch - 'a');
    if ('A' <= ch && ch <= 'F') return 10 + (ch - 'A');
    return -1;
}


/*-------------------------------------------------------------
Function: read_hex_byte

Reads two hexadecimal characters and converts them
into one byte value.
-------------------------------------------------------------*/
static int read_hex_byte(const char *text, unsigned *result)
{
    int high = hex_to_int((unsigned char)text[0]);
    int low  = hex_to_int((unsigned char)text[1]);

    if (high < 0 || low < 0)
        return 0;

    *result = (unsigned)((high << 4) | low);
    return 1;
}


/*-------------------------------------------------------------
Function: calculate_nmea_checksum

Calculates the XOR checksum of an NMEA sentence.
Checksum is computed between '$' and '*'.
-------------------------------------------------------------*/
static unsigned calculate_nmea_checksum(const char *start, const char *star)
{
    unsigned checksum = 0;

    for (const char *ptr = start; ptr < star; ++ptr)
        checksum ^= (unsigned char)(*ptr);

    return checksum;
}


/*-------------------------------------------------------------
Function: check_nmea_sentence

Verifies whether a line is a valid NMEA sentence.

Return values:
 1  -> checksum correct
-1  -> checksum incorrect
 0  -> not a valid NMEA format
-------------------------------------------------------------*/
static int check_nmea_sentence(const char *text_line)
{
    if (!text_line || text_line[0] != '$')
        return 0;

    const char *star_pos = strchr(text_line, '*');
    if (!star_pos)
        return 0;

    if (star_pos <= text_line + 1)
        return 0;

    if (star_pos[1] == '\0' || star_pos[2] == '\0')
        return 0;

    unsigned expected_checksum = 0;

    if (!read_hex_byte(star_pos + 1, &expected_checksum))
        return 0;

    unsigned real_checksum = calculate_nmea_checksum(text_line + 1, star_pos);

    return (real_checksum == expected_checksum) ? 1 : -1;
}


/*-------------------------------------------------------------
Function: read_user_line

Reads a line of text from the user.
Removes newline characters from the end.
-------------------------------------------------------------*/
static int read_user_line(const char *message, char *buffer, size_t buffer_size)
{
    if (!buffer || buffer_size == 0)
        return 0;

    printf("%s", message);
    fflush(stdout);

    if (!fgets(buffer, (int)buffer_size, stdin))
        return 0;

    buffer[strcspn(buffer, "\r\n")] = '\0';

    return (buffer[0] != '\0');
}


/*-------------------------------------------------------------
Function: try_open_file_paths

Attempts to open a file using several possible paths.
-------------------------------------------------------------*/
static FILE* try_open_file_paths(const char *user_filename)
{
    FILE *file_ptr = NULL;

    /* try the filename exactly as entered */
    file_ptr = fopen(user_filename, "r");
    if (file_ptr)
        return file_ptr;

    /* if user specified a path already, do not guess */
    if (strchr(user_filename, '/') != NULL ||
        strchr(user_filename, '\\') != NULL)
    {
        return NULL;
    }

    {
        char full_path[512];

        snprintf(full_path, sizeof(full_path),
                 EX21_FOLDER "/%s", user_filename);

        file_ptr = fopen(full_path, "r");
        if (file_ptr) return file_ptr;

        snprintf(full_path, sizeof(full_path),
                 "../" EX21_FOLDER "/%s", user_filename);

        file_ptr = fopen(full_path, "r");
        if (file_ptr) return file_ptr;

        snprintf(full_path, sizeof(full_path),
                 "../../" EX21_FOLDER "/%s", user_filename);

        file_ptr = fopen(full_path, "r");
        if (file_ptr) return file_ptr;
    }

    return NULL;
}


/*-------------------------------------------------------------
Function: open_file_or_print_error

Tries to open a file and prints an error if it fails.
-------------------------------------------------------------*/
static FILE* open_file_or_print_error(const char *user_filename)
{
    FILE *file_ptr = try_open_file_paths(user_filename);

    if (!file_ptr)
    {
        fprintf(stderr, "Error: cannot open file \"%s\" for reading.\n", user_filename);

        fprintf(stderr,
                "Hint: I also tried:\n"
                "      " EX21_FOLDER "/%s\n"
                "      ../" EX21_FOLDER "/%s\n"
                "      ../../" EX21_FOLDER "/%s\n",
                user_filename,
                user_filename,
                user_filename);
    }

    return file_ptr;
}


/*-------------------------------------------------------------
Function: run_exercise_21

Main logic of Exercise 21.

Steps:
1. Ask the user for a file name
2. Open the file
3. Read it line by line
4. Check if each line is a valid NMEA sentence
5. Print result (OK / FAIL / not NMEA)
-------------------------------------------------------------*/
void run_exercise_21(void)
{
    char input_filename[512];

    if (!read_user_line("Enter file name: ", input_filename, sizeof(input_filename)))
    {
        printf("No input.\n");
        return;
    }

    FILE *input_file = open_file_or_print_error(input_filename);

    if (!input_file)
        return;

    char file_line[2048];

    while (fgets(file_line, sizeof(file_line), input_file))
    {
        int check_result = check_nmea_sentence(file_line);

        if (check_result == 1)
            printf("[ OK ] %s", file_line);
        else if (check_result == -1)
            printf("[FAIL] %s", file_line);
        else
            printf("       %s", file_line);

        if (strchr(file_line, '\n') == NULL)
            printf("\n");
    }

    fclose(input_file);
}