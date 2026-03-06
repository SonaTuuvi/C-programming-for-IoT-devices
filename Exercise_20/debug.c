//
// Created by Sona on 5/3/2026 AD.
//
#include "debug.h"

#include <stdio.h>
#include <stdarg.h>

/*-------------------------------------------------------------
This file implements debug support functions.

It contains:
- a static variable for storing the current debug level
- a function to set that level
- a function similar to printf that prints messages only
  when the requested debug level is allowed
-------------------------------------------------------------*/


/*-------------------------------------------------------------
Static variable: g_debug_level

Stores the current debug level for this file.

Why static:
- visible only inside debug.c
- cannot be accessed directly from other files
- can still be used by all functions in this file

Default value:
0
-------------------------------------------------------------*/
static int g_debug_level = 0;


/*-------------------------------------------------------------
Function: set_debug_level

Sets the current debug level.

What this function does:
- receives a debug level as an integer
- stores it in the file-static variable g_debug_level

Parameter:
- debug_level -> new debug level value

Note:
- after this function is called, dprintf() uses this value
  to decide whether a message should be printed
-------------------------------------------------------------*/
void set_debug_level(int debug_level)
{
    g_debug_level = debug_level;
}


/*-------------------------------------------------------------
Function: dprintf

Works like printf, but with one extra parameter:
the debug level of the message.

What this function does:
- checks whether the given debug level is less than or equal
  to the stored debug level
- if yes, prints the message to stderr
- adds a prefix in the format [DBGx]
- if not, prints nothing and returns 0

Parameters:
- debug_level -> level of this message
- fmt         -> format string
- ...         -> additional values for formatting

Returns:
- number of printed characters if output was printed
- 0 if nothing was printed

Example:
If stored level is 3:
- dprintf(2, "Hello\n") -> prints
- dprintf(4, "Hello\n") -> prints nothing
-------------------------------------------------------------*/
int dprintf(int debug_level, const char *fmt, ...)
{
    int printed_chars = 0;

    if (fmt == NULL)
        return 0;

    if (debug_level <= g_debug_level)
    {
        va_list args;

        printed_chars += fprintf(stderr, "[DBG%d] ", debug_level);

        va_start(args, fmt);
        printed_chars += vfprintf(stderr, fmt, args);
        va_end(args);

        return printed_chars;
    }

    return 0;
}