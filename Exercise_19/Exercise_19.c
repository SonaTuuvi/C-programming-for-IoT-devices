/*
 * =============================================================
 *  Exercise 19 — The Legendary Menu Sorting Mission
 * =============================================================
 *
 *  Author: Sona
 *
 *  Date of Completion:
 *  (Insert the heroic day when this code finally compiled without errors)
 *
 * -------------------------------------------------------------
 *  Mission Brief
 * -------------------------------------------------------------
 *  The objective of this totally not dramatic assignment is
 *  to read a menu from a file and allow the user to decide
 *  how they want to see it sorted.
 *
 *  The user can choose to sort the menu:
 *      1) By name   (alphabetical order like civilized people)
 *      2) By price  (for those who check their wallet first)
 *
 *  After the choice is made, the program uses the legendary
 *  C standard library function `qsort()` to bring order to chaos.
 *
 * -------------------------------------------------------------
 *  File Responsibilities (a.k.a. The Avengers of this Program)
 * -------------------------------------------------------------
 *
 *  Exercise_19.c
 *      The main commander. Coordinates everything.
 *
 *  menu_io.c
 *      Reads menu items from the file.
 *
 *  menu_sort.c
 *      Handles sorting logic using qsort(). This is where
 *      the real magic happens.
 *
 *  menu_print.c
 *      Prints the menu in a nice column layout so humans
 *      can actually read it without crying.
 *
 *  input_utils.c
 *      Responsible for safe user input and preventing the
 *      classic C tragedy known as the "input buffer disaster".
 *
 * -------------------------------------------------------------
 *  Program Flow (How the Mission Unfolds)
 * -------------------------------------------------------------
 *
 *  Step 1:
 *      Clear the input buffer.
 *      (Because leftover input is the villain of many programs.)
 *
 *  Step 2:
 *      Ask the user for the menu filename.
 *      Hopefully the user types something that actually exists.
 *
 *  Step 3:
 *      Open the file.
 *      If the file does not exist… well… sadness happens.
 *
 *  Step 4:
 *      Read menu items into an array.
 *      Delicious data is now stored in memory.
 *
 *  Step 5:
 *      Ask the user how the menu should be sorted.
 *      Name or price — the eternal philosophical question.
 *
 *  Step 6:
 *      Call qsort() with the correct comparison function.
 *
 *  Step 7:
 *      Print the sorted menu in a beautiful column format.
 *
 * -------------------------------------------------------------
 *  Important Note
 * -------------------------------------------------------------
 *
 *  If something crashes, it was probably not the code.
 *  It was definitely the user. Or the file. Or the compiler.
 *  (But mostly the user.)
 *
 * -------------------------------------------------------------
 *  Author's Personal Note
 * -------------------------------------------------------------
 *
 *  Dear future me (or whoever reads this code):
 *
 *  Yes, this could probably be written in fewer lines.
 *  Yes, there are probably more efficient ways.
 *
 *  But the goal here is clarity, structure, and passing
 *  the assignment without emotional damage.
 *
 *  Mission status: SUCCESS (hopefully).
 *
 * =============================================================
 */

#include "Exercise_19.h"

#include <stdio.h>

#include "menu_types.h"
#include "menu_io.h"
#include "menu_sort.h"
#include "menu_print.h"
#include "input_utils.h"


void run_exercise_19(void)
{
    char filename[256];
    FILE *fp;

    menu_item items[MAX_MENU_ITEMS];
    int count;

    sort_settings settings;

    /* clearing buffer because C likes to surprise us with leftover input */
    clear_input_buffer();

    /* ask user for filename (hopefully something that actually exists) */
    if (!read_filename_from_user(filename, (int)sizeof(filename)))
    {
        printf("Input failed. Maybe the keyboard is shy today.\n");
        return;
    }

    /* opening file like opening the fridge — hoping there is food inside */
    fp = open_file_for_reading_or_exit(filename);

    /* read menu items from file */
    count = read_menu_items_from_file(fp, items);

    fclose(fp);  /* always close files — computers appreciate manners */

    if (count <= 0)
    {
        printf("No menu items were read from the file.\n");
        printf("Either the file is empty or the universe is against us today.\n");
        return;
    }

    /* ask user how they want the menu sorted */
    settings = ask_user_for_sort_settings();

    /* sorting happens here (qsort enters the chat) */
    sort_menu_items(items, count, settings);

    /* finally print the beautifully sorted menu */
    print_menu_items_in_columns(items, count);
}
