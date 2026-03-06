#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

/*
 * -------------------------------------------------------------
 * Purpose: safe user input helpers
 * -------------------------------------------------------------
 */

int read_line(char *buffer, int buffer_size);
void clear_input_buffer(void);
void trim_whitespace_in_place(char *text);

/*
 * Reads integer from user using fgets + strtol.
 * Returns 1 if success, 0 if input ended (EOF).
 */
int read_int_from_user(const char *prompt, int *out_value);

#endif