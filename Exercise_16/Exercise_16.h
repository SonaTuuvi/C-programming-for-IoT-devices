#ifndef EXERCISE_16_H
#define EXERCISE_16_H

/*
 * -------------------------------------------------------------
 * Exercise_16.h
 * -------------------------------------------------------------
 * Header file for Exercise 16.
 *
 * I keep only ONE function public here:
 *
 *      run_exercise_16();
 *
 * Everything else stays private inside Exercise_16.c
 * using the keyword "static".
 *
 * Why?
 * Because helper functions are nobody else's business.
 * If someone wants to break my code, they will need
 * to work harder than that.
 *
 * Also this header uses an include guard.
 * This prevents multiple inclusion problems during compilation.
 * -------------------------------------------------------------
 */

void run_exercise_16(void);

#endif