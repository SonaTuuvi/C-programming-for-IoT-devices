#ifndef MENU_TYPES_H
#define MENU_TYPES_H

/*
 * -------------------------------------------------------------
 * Purpose: common data types/constants for menu program
 * -------------------------------------------------------------
 */

#define MAX_MENU_ITEMS  40
#define MAX_NAME_LENGTH 50

typedef struct menu_item_
{
    char name[MAX_NAME_LENGTH];
    double price;
} menu_item;

#endif