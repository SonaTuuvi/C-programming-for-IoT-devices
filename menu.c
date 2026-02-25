#include <stdio.h>
#include "Exercise_1/Exercise_1.h"
#include "Exercise_2/Exercise_2.h"
#include "Exercise_3/Exercise_3.h"
#include "Exercise_4/Exercise_4.h"
#include "Exercise_5/Exercise_5.h"
#include "Exercise_6/Exercise_6.h"
#include "Exercise_7/Exercise_7.h"
#include "Exercise_8/Exercise_8.h"
#include "Exercise_9/Exercise_9.h"
#include "Exercise_10/Exercise_10.h"
#include "Exercise_11/Exercise_11.h"
#include "Exercise_12/Exercise_12.h"
#include "Exercise_13/Exercise_13.h"
#include "Exercise_14/Exercise_14.h"
#include "Exercise_15/Exercise_15.h"

void show_exercise_menu(void) {
    int user_choice = -1;

    while (1) {
        printf("\nWelcome to the Exercise Chooser 3000\n");
        printf("Pick your flavor of pain today:\n");
        printf(" 1 - Exercise 1\n");
        printf(" 2 - Exercise 2\n");
        printf(" 3 - Exercise 3\n");
        printf(" 4 - Exercise 4\n");
        printf(" 5 - Exercise 5\n");
        printf(" 6 - Exercise 6\n");
        printf(" 7 - Exercise 7\n");
        printf(" 8 - Exercise 8\n");
        printf(" 9 - Exercise 9\n");
        printf(" 10 - Exercise 10\n");
        printf(" 11 - Exercise 11\n");
        printf(" 12 - Exercise 12\n");
        printf(" 13 - Exercise 13\n");
        printf(" 14 - Exercise 14\n");
        printf(" 15 - Exercise 15\n");
        printf(" 0 - Exit, because sanity matters\n");
        printf("Your choice: ");

        if (scanf("%d", &user_choice) != 1) {
            printf("Invalid input. Next time, try a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (user_choice) {
            case 1: run_exercise_1(); break;
            case 2: run_exercise_2(); break;
            case 3: run_exercise_3(); break;
            case 4: run_exercise_4(); break;
            case 5: run_exercise_5(); break;
            case 6: run_exercise_6(); break;
            case 7: run_exercise_7(); break;
            case 8: run_exercise_8(); break;
            case 9: run_exercise_9(); break;
            case 10: run_exercise_10(); break;
            case 11: run_exercise_11(); break;
            case 12: run_exercise_12(); break;
            case 13: run_exercise_13(); break;
            case 14: run_exercise_14(); break;
            case 15: run_exercise_15(); break;
            case 0:
                printf("Adieu! Come back when you're ready for more confusion.\n");
                return;
            default:
                printf("Not on the list. Try again, brave soul.\n");
        }
    }
}
