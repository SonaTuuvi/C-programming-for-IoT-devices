#ifndef RUN_EXERCISE_7_H
#define RUN_EXERCISE_7_H

// Because even games deserve structure
typedef struct {
 int guessed_amount;             // what the user thinks we have
 int invalid_input_counter;      // how many times they failed us
} RichGuessingGame;

bool read_positive_number(int *user_input);
void run_exercise_7(void);

#endif // RUN_EXERCISE_7_H
