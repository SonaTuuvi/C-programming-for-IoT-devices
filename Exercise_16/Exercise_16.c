#include <stdio.h>      /* printf, fprintf, fgets */
#include <stdlib.h>     /* malloc, free, strtol, exit */
#include <string.h>     /* strcmp, strcspn, strlen */
#include <ctype.h>      /* isspace */
#include "Exercise_16.h"

/*
 * -------------------------------------------------------------
 * Author:      Sona (patient explainer mode)
 * File:        Exercise_16.c
 * -------------------------------------------------------------
 *
 * MISSION:
 * Ask the user to enter numbers.
 *
 * The user can type:
 *      - a number
 *      - "end"
 *
 * If the user types:
 *      "end"
 * Stop reading input.
 *
 * If the user types:
 *      anything else that is NOT a number
 * Print an error message and ignore the input.
 *
 * Every valid number is stored inside a LINKED LIST.
 *
 * Important requirement of the task:
 *      every node must be dynamically allocated
 *      (so yes, malloc is involved).
 *
 * When the user types "end":
 *      1) I print all stored numbers
 *      2) I free the allocated memory
 *      3) program ends peacefully
 *
 * No memory leaks allowed. Refuse.
 * -------------------------------------------------------------
 */


/*
 * -------------------------------------------------------------
 * Structure definition
 * -------------------------------------------------------------
 *
 * This is a classic linked list node.
 *
 * Each node contains:
 *      number  -> the integer value
 *      next    -> pointer to the next node
 *
 * If next == NULL
 * then this node is the last one in the list.
 *
 * I use typedef so I can write "nnode"
 * instead of "struct node".
 * -------------------------------------------------------------
 */
typedef struct node
{
    int number;
    struct node *next;
} nnode;


/*
 * -------------------------------------------------------------
 * Function declarations (prototypes)
 * -------------------------------------------------------------
 *
 * I keep helper functions static so they stay private
 * to this file.
 *
 * Nobody outside this file should call them.
 * That is intentional.
 * -------------------------------------------------------------
 */

static void trim_whitespace_in_place(char *text);

static int user_input_is_end(const char *text);

static int parse_int_from_text(
            const char *text,
            int *result);

static nnode* create_node(int number);

static void append_node(
            nnode **head,
            nnode **tail,
            nnode *new_node);

static void print_list(const nnode *head);

static void free_list(nnode *head);

/*
 * -------------------------------------------------------------
 * Function: clear_input_buffer
 * -------------------------------------------------------------
 * I remove any leftover characters from stdin until I reach
 * a newline or EOF.
 *
 * This is useful when the program previously used scanf().
 * scanf often leaves the newline character '\n' in the input
 * buffer, which can break the next fgets() call.
 *
 * Without clearing the buffer, fgets() might immediately read
 * that leftover newline and return an empty string.
 *
 * In short: I clean up stdin so the next input behaves normally.
 * -------------------------------------------------------------
 */

static void clear_input_buffer(void)
{
    int ch;

    /* discard everything until newline or EOF */
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        /* nothing */
    }
}

/*
 * -------------------------------------------------------------
 * Function: run_exercise_16
 * -------------------------------------------------------------
 *
 * This is the main function of the exercise.
 * It will be called from the program menu.
 *
 * Steps performed here:
 *
 *      Ask the user for numbers repeatedly.
 *
 *      If the user types "end":
 *              stop reading input
 *
 *      If the user types a valid integer:
 *              store it in the linked list
 *
 *      If the user types invalid text:
 *              print an error message
 *              ignore the input
 *
 *      After input ends:
 *              print stored numbers
 *              free memory
 * -------------------------------------------------------------
 */
void run_exercise_16(void)
{
    char buffer[256];

    nnode *head = NULL;
    nnode *tail = NULL;

    /* Because menu used scanf before calling this exercise,
       there is a leftover '\n' sitting in stdin. */
    clear_input_buffer();

    printf("Enter numbers.\n");
    printf("Type \"end\" to stop.\n\n");

    while (1)
    {
        int number;

        printf("Enter number (or end): ");

        /*
         * fgets reads a full line from stdin.
         *
         * I prefer fgets instead of scanf
         * because scanf has a habit of leaving garbage
         * inside the input buffer.
         *
         * fgets is boring but reliable.
         */
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
            printf("\nInput ended unexpectedly.\n");
            break;
        }

        /*
         * fgets usually keeps the newline '\n'.
         * I remove it because it gets annoying later.
         */
        buffer[strcspn(buffer, "\n")] = '\0';

        /*
         * Remove leading and trailing spaces.
         * Example:
         *      "   123   " -> "123"
         *      "   end  "  -> "end"
         */
        trim_whitespace_in_place(buffer);

        /*
         * If the string is empty, user probably pressed Enter.
         * That is not a number and not "end".
         */
        if (strlen(buffer) == 0)
        {
            fprintf(stderr, "Error: empty input.\n");
            continue;
        }

        /*
         * Check if the user wants to stop.
         */
        if (user_input_is_end(buffer))
        {
            break;
        }

        /*
         * Attempt to convert text into an integer.
         */
        if (!parse_int_from_text(buffer, &number))
        {
            fprintf(stderr,
                    "Error: \"%s\" is not a valid number.\n",
                    buffer);
            continue;
        }

        /*
         * If we reach this point,
         * the input is a valid integer.
         *
         * I create a new node and append it
         * to the linked list.
         */
        {
            nnode *node = create_node(number);
            append_node(&head, &tail, node);
        }
    }

    printf("\nNumbers entered:\n");
    print_list(head);

    /*
     * I free the entire linked list.
     * Memory leaks are unacceptable.
     */
    free_list(head);

    printf("\nMemory freed. Program finished.\n");
}


/*
 * -------------------------------------------------------------
 * Function: user_input_is_end
 * -------------------------------------------------------------
 *
 * This function checks whether the user typed "end".
 *
 * strcmp returns 0 when strings are identical.
 * -------------------------------------------------------------
 */
static int user_input_is_end(const char *text)
{
    if (text == NULL)
        return 0;

    return strcmp(text, "end") == 0;
}


/*
 * -------------------------------------------------------------
 * Function: parse_int_from_text
 * -------------------------------------------------------------
 *
 * I convert a string into an integer.
 *
 * Instead of using atoi() I use strtol()
 * because strtol is safer and more informative.
 *
 * It allows me to detect cases like:
 *
 *      "123abc"
 *
 * which should NOT be accepted as a number.
 *
 * Return value:
 *      1  -> success
 *      0  -> failure
 * -------------------------------------------------------------
 */
static int parse_int_from_text(
            const char *text,
            int *result)
{
    char *endptr;
    long value;

    /*
     * I attempt to convert the input string into a number.
     *
     * strtol() reads a number from the beginning of the string.
     *
     * Parameters:
     *      text    -> input string from the user
     *      &endptr -> pointer that will point to the first character
     *                 AFTER the parsed number
     *      10      -> base (decimal number system)
     *
     * Example:
     *
     *      input: "123abc"
     *
     *      value  = 123
     *      endptr -> points to 'a'
     *
     * I later check endptr to detect invalid inputs like:
     *      "123abc"
     *      "667aaaa"
     *      "hello"
     */

    value = strtol(text, &endptr, 10);

    if (endptr == text)
        return 0;

    while (*endptr != '\0')
    {
        if (!isspace((unsigned char)*endptr))
            return 0;

        endptr++;
    }

    *result = (int)value;
    return 1;
}


/*
 * -------------------------------------------------------------
 * Function: create_node
 * -------------------------------------------------------------
 *
 * I allocate memory for a new node.
 *
 * If malloc fails I terminate the program.
 * Because without memory the program cannot continue.
 * -------------------------------------------------------------
 */
static nnode* create_node(int number)
{
    nnode *node;

    node = malloc(sizeof(nnode));

    if (node == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    node->number = number;
    node->next = NULL;

    return node;
}


/*
 * -------------------------------------------------------------
 * Function: append_node
 * -------------------------------------------------------------
 *
 * This function appends a node to the end of the list.
 *
 * I keep both head and tail pointers.
 *
 * Why?
 * Because appending then becomes O(1)
 * instead of walking the entire list every time.
 *
 * That would be inefficient and mildly annoying.
 * -------------------------------------------------------------
 */
static void append_node(
            nnode **head,
            nnode **tail,
            nnode *new_node)
{
    if (*head == NULL)
    {
        *head = new_node;
        *tail = new_node;
        return;
    }

    (*tail)->next = new_node;
    *tail = new_node;
}


/*
 * -------------------------------------------------------------
 * Function: print_list
 * -------------------------------------------------------------
 *
 * I traverse the linked list and print each value.
 *
 * Traversal rule:
 *      start at head
 *      move through next pointers
 *      stop when NULL is reached
 * -------------------------------------------------------------
 */
static void print_list(const nnode *head)
{
    const nnode *current = head;

    if (current == NULL)
    {
        printf("(No numbers entered)\n");
        return;
    }

    while (current != NULL)
    {
        printf("%d\n", current->number);
        current = current->next;
    }
}


/*
 * -------------------------------------------------------------
 * Function: free_list
 * -------------------------------------------------------------
 *
 * This function releases all nodes from memory.
 *
 * Important detail:
 *
 * I must store the next pointer BEFORE calling free().
 *
 * After free(), accessing the node would be undefined behavior.
 * -------------------------------------------------------------
 */
static void free_list(nnode *head)
{
    nnode *current = head;

    while (current != NULL)
    {
        nnode *next = current->next;
        free(current);
        current = next;
    }
}


/*
 * -------------------------------------------------------------
 * Function: trim_whitespace_in_place
 * -------------------------------------------------------------
 *
 * This helper removes whitespace characters
 * from the beginning and the end of a string.
 *
 * The operation happens "in place":
 * meaning the original buffer is modified.
 *
 * Example:
 *
 *      "   123   "  -> "123"
 *      "  end   "   -> "end"
 *
 * I do not allocate new memory.
 * I simply shift characters inside the array.
 *
 * isspace() checks whether a character is a whitespace character.
 * This includes: space, tab, newline, etc.
 *
 * I cast to (unsigned char) because functions from <ctype.h>
 * expect either EOF or an unsigned char value.
 * Using plain char can sometimes cause undefined behavior
 * if char happens to be signed on this system.
 * -------------------------------------------------------------
 */
static void trim_whitespace_in_place(char *text)
{
    int start = 0;
    int end;
    int len;

    if (text == NULL)
        return;

    len = strlen(text);

    while (isspace((unsigned char)text[start]))
        start++;

    if (text[start] == '\0')
    {
        text[0] = '\0';
        return;
    }

    end = len - 1;

    while (end >= 0 && isspace((unsigned char)text[end]))
        end--;

    if (start > 0)
    {
        int i = 0;

        while (text[start] != '\0')
        {
            text[i++] = text[start++];
        }

        text[i] = '\0';
    }

    len = strlen(text);
    end = len - 1;

    while (end >= 0 && isspace((unsigned char)text[end]))
    {
        text[end] = '\0';
        end--;
    }
}