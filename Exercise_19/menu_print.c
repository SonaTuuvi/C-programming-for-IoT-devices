#include "menu_print.h"
#include <stdio.h>

/*-------------------------------------------------------------
Menu printing functions
Author: Sona

This file contains functions responsible for displaying
menu items on the screen in a clean column format.
-------------------------------------------------------------*/


/*-------------------------------------------------------------
Function: print_menu_items_in_columns

Prints menu items in a simple table-like format.

What this function does:
- checks if the array of items is valid
- prints a header for the menu
- loops through all menu items
- prints each item with its price and name

Output format:
price (aligned)  item name

Example:
   12.50  Pizza
    8.90  Soup

Parameters:
- items -> pointer to the array of menu items
- count -> number of items in the array

Note:
- if the array is empty or NULL, a message is printed
-------------------------------------------------------------*/
void print_menu_items_in_columns(const menu_item *items, int count)
{
    int i;

    if (items == NULL || count <= 0)
    {
        printf("No menu items to print.\n");
        return;
    }

    printf("\n----- MENU (sorted) -----\n");

    for (i = 0; i < count; i++)
    {
        printf("%8.2f  %s\n", items[i].price, items[i].name);
    }
}