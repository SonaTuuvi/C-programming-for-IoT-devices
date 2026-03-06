#include "menu_sort.h"
#include "input_utils.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * -------------------------------------------------------------
 * qsort comparator needs only (a,b).
 * To support ASC/DESC without global variables:
 * we store current settings in a static file-scope variable.
 *
 * This is safe here because we sort once per run in one thread.
 * -------------------------------------------------------------
 */
static sort_settings g_current_sort_settings;

static int compare_menu_items(const void *a, const void *b);

sort_settings ask_user_for_sort_settings(void)
{
    sort_settings settings;
    int choice;

    /*
     * Ask field.
     */
    while (1)
    {
        printf("\nChoose sorting field:\n");
        printf("  1) Sort by name\n");
        printf("  2) Sort by price\n");

        if (!read_int_from_user("Your choice: ", &choice))
        {
            settings.field = SORT_FIELD_NAME;
            settings.order = SORT_ORDER_ASC;
            return settings;
        }

        if (choice == 1)
        {
            settings.field = SORT_FIELD_NAME;
            break;
        }

        if (choice == 2)
        {
            settings.field = SORT_FIELD_PRICE;
            break;
        }

        printf("Invalid choice. Please type 1 or 2.\n");
    }

    /*
     * Ask order (the “плюшка”).
     */
    while (1)
    {
        printf("\nChoose sorting order:\n");
        printf("  1) Ascending\n");
        printf("  2) Descending\n");

        if (!read_int_from_user("Your choice: ", &choice))
        {
            settings.order = SORT_ORDER_ASC;
            return settings;
        }

        if (choice == 1)
        {
            settings.order = SORT_ORDER_ASC;
            return settings;
        }

        if (choice == 2)
        {
            settings.order = SORT_ORDER_DESC;
            return settings;
        }

        printf("Invalid choice. Please type 1 or 2.\n");
    }
}


void sort_menu_items(menu_item *items, int count, sort_settings settings)
{
    if (items == NULL || count <= 1)
        return;

    g_current_sort_settings = settings;

    qsort(items,
          (size_t)count,
          sizeof(menu_item),
          compare_menu_items);
}


/*
 * -------------------------------------------------------------
 * Comparator: compare_menu_items
 * -------------------------------------------------------------
 * Applies selected field and then direction.
 *
 * For price we do safe double comparisons (no casting).
 * For name we use strcmp.
 * -------------------------------------------------------------
 */
static int compare_menu_items(const void *a, const void *b)
{
    const menu_item *item_a = (const menu_item *)a;
    const menu_item *item_b = (const menu_item *)b;

    int result = 0;

    if (g_current_sort_settings.field == SORT_FIELD_NAME)
    {
        result = strcmp(item_a->name, item_b->name);
    }
    else
    {
        if (item_a->price < item_b->price)
            result = -1;
        else if (item_a->price > item_b->price)
            result = 1;
        else
            result = strcmp(item_a->name, item_b->name);
    }

    if (g_current_sort_settings.order == SORT_ORDER_DESC)
        result = -result;

    return result;
}