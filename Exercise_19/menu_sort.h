#ifndef MENU_SORT_H
#define MENU_SORT_H

#include "menu_types.h"

/*-------------------------------------------------------------
Menu sorting definitions
Author: Sona

This header defines structures and functions used for
sorting menu items.

It allows the user to:
- choose what field to sort by (name or price)
- choose the sorting order (ascending or descending)
-------------------------------------------------------------*/


/*-------------------------------------------------------------
Enum: sort_field

Defines which field of the menu item will be used
for sorting.

Values:
SORT_FIELD_NAME  -> sort items alphabetically by name
SORT_FIELD_PRICE -> sort items by price
-------------------------------------------------------------*/
typedef enum sort_field_
{
    SORT_FIELD_NAME  = 1,
    SORT_FIELD_PRICE = 2
} sort_field;


/*-------------------------------------------------------------
Enum: sort_order

Defines the direction of sorting.

Values:
SORT_ORDER_ASC  -> ascending order
SORT_ORDER_DESC -> descending order
-------------------------------------------------------------*/
typedef enum sort_order_
{
    SORT_ORDER_ASC  = 1,
    SORT_ORDER_DESC = 2
} sort_order;


/*-------------------------------------------------------------
Structure: sort_settings

Stores the sorting configuration selected by the user.

Members:
field -> which property to sort by (name or price)
order -> sorting direction (ascending or descending)

This structure is passed to the sorting function so it
knows how to perform the sorting.
-------------------------------------------------------------*/
typedef struct sort_settings_
{
    sort_field field;
    sort_order order;
} sort_settings;


/*-------------------------------------------------------------
Function: ask_user_for_sort_settings

Asks the user how the menu should be sorted.

The function usually asks:
1) sort by name or price
2) ascending or descending order

Returns:
A sort_settings structure containing the user's choices.
-------------------------------------------------------------*/
sort_settings ask_user_for_sort_settings(void);


/*-------------------------------------------------------------
Function: sort_menu_items

Sorts an array of menu_item structures.

Uses the sorting settings provided by the user and
typically relies on qsort() internally.

Parameters:
items    -> array of menu items
count    -> number of items in the array
settings -> sorting configuration (field and order)
-------------------------------------------------------------*/
void sort_menu_items(menu_item *items, int count, sort_settings settings);

#endif