#ifndef MENU_IO_H
#define MENU_IO_H

#include <stdio.h>
#include "menu_types.h"

/*
 * -------------------------------------------------------------
 * Purpose: open + read + parse menu from file
 * -------------------------------------------------------------
 */

int read_filename_from_user(char *filename_buffer, int buffer_size);
FILE* open_file_for_reading_or_exit(const char *filename_from_user);

int read_menu_items_from_file(FILE *opened_file,
                              menu_item menu_items_array[MAX_MENU_ITEMS]);

#endif