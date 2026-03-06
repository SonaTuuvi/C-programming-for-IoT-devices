#include "Exercise_18.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * -------------------------------------------------------------
 * Author: Sona (grumpy programmer mode)
 * File:   Exercise_18.c
 * -------------------------------------------------------------
 *
 * MISSION:
 * User enters a number between 0 and 15.
 *
 * Program then:
 *   1) generates a random number (0..255)
 *   2) prints it in HEX
 *   3) shifts the number RIGHT by user amount
 *   4) keeps only bits 0..5 (mask 0x3F)
 *   5) prints the final result
 *
 * If user enters a negative number -> program exits.
 *
 * NOTE:
 * This version uses fgets + strtol for safer input handling.
 * -------------------------------------------------------------
 *
 * BIT MASK EXPLANATION
 *
 * Mask used:
 *      00111111
 *      0x3F
 *
 * Because bits 0..5 = 6 bits.
 *
 * Using:
 *      value & 0x3F
 *
 * keeps the lowest 6 bits and clears all higher bits.
 * -------------------------------------------------------------
 */


/*
 * -------------------------------------------------------------
 * Helper function prototypes
 * -------------------------------------------------------------
 */

static int ask_user_for_shift_amount(void);
static unsigned int generate_random_byte_value(void);
static unsigned int shift_number_right(unsigned int value, int shift_amount);
static unsigned int keep_only_bits_zero_to_five(unsigned int value);
static void print_hex_two_digits(const char *label, unsigned int value);

static void trim_newline(char *text);


/*
 * -------------------------------------------------------------
 * Function: run_exercise_18
 * -------------------------------------------------------------
 * Main function of this module.
 * Acts like the boss: it tells helper functions what to do.
 * -------------------------------------------------------------
 */
void run_exercise_18(void)
{
    srand((unsigned int)time(NULL));

    while (1)
    {
        int user_shift_amount = ask_user_for_shift_amount();

        if (user_shift_amount < 0)
        {
            printf("Negative number detected. Program exits.\n");
            break;
        }

        {
            unsigned int random_number = generate_random_byte_value();

            print_hex_two_digits("Random number (hex)", random_number);

            {
                unsigned int shifted_value =
                    shift_number_right(random_number, user_shift_amount);

                unsigned int masked_value =
                    keep_only_bits_zero_to_five(shifted_value);

                print_hex_two_digits("Result after shift and mask", masked_value);
            }

            printf("\n\n");
        }
    }
}


/*
 * -------------------------------------------------------------
 * Function: ask_user_for_shift_amount
 * -------------------------------------------------------------
 *
 * Asks user for a number.
 *
 * Valid input:
 *      0..15  -> continue
 *      <0     -> stop program (returned as negative)
 *
 * If user enters >15 or invalid text, we complain and ask again.
 * -------------------------------------------------------------
 */
static int ask_user_for_shift_amount(void)
{
    char line[64];
    long value;
    char *endptr;

    while (1)
    {
        printf("Enter number (0..15) or negative number to stop: ");

        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            /*
             * If input stream ends (EOF),
             * we stop the program by returning negative.
             */
            return -1;
        }

        trim_newline(line);

        /*
         * strtol converts string -> long.
         * endptr points to the first character after the number.
         */
        endptr = NULL;
        value = strtol(line, &endptr, 10);

        /*
         * If endptr == line, no digits were read -> invalid input.
         */
        if (endptr == line)
        {
            printf("Invalid input. Please type a number.\n");
            continue;
        }

        /*
         * If there are leftover non-space characters,
         * input is not a clean integer.
         */
        while (*endptr != '\0')
        {
            if (*endptr != ' ' && *endptr != '\t')
            {
                printf("Invalid input. Please type a clean integer.\n");
                value = 9999; /* force retry */
                break;
            }
            endptr++;
        }

        if (value == 9999)
            continue;

        if (value > 15)
        {
            printf("Number must be between 0 and 15. Try again.\n");
            continue;
        }

        return (int)value;
    }
}


/*
 * -------------------------------------------------------------
 * Function: generate_random_byte_value
 * -------------------------------------------------------------
 *
 * Generates random number between 0 and 255.
 *
 * Because 255 fits perfectly in one byte.
 * -------------------------------------------------------------
 */
static unsigned int generate_random_byte_value(void)
{
    unsigned int random_value = (unsigned int)(rand() % 256);
    return random_value;
}


/*
 * -------------------------------------------------------------
 * Function: shift_number_right
 * -------------------------------------------------------------
 *
 * Performs bitwise RIGHT shift.
 *
 * Example:
 *      10110010 >> 2 = 00101100
 *
 * Bits that fall off the right side are gone forever.
 * -------------------------------------------------------------
 */
static unsigned int shift_number_right(unsigned int value, int shift_amount)
{
    unsigned int shifted_value = value >> shift_amount;
    return shifted_value;
}


/*
 * -------------------------------------------------------------
 * Function: keep_only_bits_zero_to_five
 * -------------------------------------------------------------
 *
 * Masks everything except bits 0..5.
 *
 * Mask:
 *      00111111
 *      0x3F
 * -------------------------------------------------------------
 */
static unsigned int keep_only_bits_zero_to_five(unsigned int value)
{
    unsigned int mask = 0x3F;
    unsigned int masked_result = value & mask;
    return masked_result;
}


/*
 * -------------------------------------------------------------
 * Function: print_hex_two_digits
 * -------------------------------------------------------------
 *
 * Prints number as HEX with exactly two digits.
 *
 * %02X means:
 *      X -> hex
 *      2 -> width 2
 *      0 -> leading zero
 * -------------------------------------------------------------
 */
static void print_hex_two_digits(const char *label, unsigned int value)
{
    printf("%s: %02X\n", label, value);
}


/*
 * -------------------------------------------------------------
 * Function: trim_newline
 * -------------------------------------------------------------
 *
 * Removes trailing '\n' if present.
 * -------------------------------------------------------------
 */
static void trim_newline(char *text)
{
    size_t i;

    if (text == NULL)
        return;

    for (i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '\n')
        {
            text[i] = '\0';
            return;
        }
    }
}