#include <stdio.h>
#include <stdlib.h>
#include "Exercise_3.h"

/*
 * ----------------------------------------------------------------------------------
 *  Author:      The Legend... named Sona
 *  Date:        26.01.2026
 *  Project:     Student Grading Simulator – Painful Edition
 * ----------------------------------------------------------------------------------
 *
 *  Description:
 *      Remember school? This is that — but you’re the admin now.
 *      This program lets you:
 *          - Ask how many students you "teach"
 *          - Assign grades or cancel grading out of pity
 *          - Validate chaos in the form of invalid input
 *          - Cry when they all get -1 and nobody passes
 *
 *  Notes:
 *      - Uses arrays (yay, still legal!)
 *      - Relies on your ability to count from 1 to N without error
 *      - Absolutely no emotional support included
 *
 *  Usage:
 *      Compile, run, regret ever volunteering to be a teacher
 *
 *  Todo:
 *      - Add bell curve to make someone pass
 *      - Auto-generate tears report per student
 *      - Detect grade inflation and panic
 *
 */

// Function to request how many brave students will enter the academic arena
int summon_student_count(void) {
    int count = 0;
    printf("How many students: ");
    scanf("%d", &count);
    return count;
}

// Initializes all grades to -1, the universal symbol of apathy
void initialize_grades(StudentBatch* batch, int count) {
    for (int i = 0; i < count; ++i) {
        batch->grades[i] = GRADE_NOT_SET;
    }
}

// Main data collection loop — powered by confusion and second guesses
void gather_academic_suffering(StudentBatch* batch, int count) {
    int victim = -1;  // student number being targeted

    do {
        printf("Enter student number (1 - %d) or 0 to stop: ", count);

        if (scanf("%d", &victim) != 1) {
            while (getchar() != '\n');  // flush invalid input
            printf("Invalid input! That wasn't even a number.\n");
            continue;
        }

        if (victim == 0) break;

        if (victim < 1 || victim > count) {
            printf("Invalid student number!\n");
            continue;
        }

        int grade = -2; // Suspiciously invalid on purpose
        printf("Enter grade (0 - 5) for student %d or -1 to cancel: ", victim);

        if (scanf("%d", &grade) != 1) {
            while (getchar() != '\n');
            printf("Invalid grade input!\n");
            continue;
        }

        if (grade >= 0 && grade <= 5) {
            batch->grades[victim - 1] = grade;
        } else if (grade != GRADE_NOT_SET) {
            printf("Invalid grade!\n");
        }

    } while (1);
}

// Display results of academic attempts — or lack thereof
void display_grades(const StudentBatch* batch, int count) {
    printf("\nStudent    Grade\n");
    for (int i = 0; i < count; ++i) {
        printf("%-10d", i + 1);
        if (batch->grades[i] == GRADE_NOT_SET) {
            printf("N/A\n");
        } else {
            printf("%d\n", batch->grades[i]);
        }
    }
}

// The glorious (and slightly tragic) entry point
void run_exercise_3(void) {
    int how_many = summon_student_count();

    StudentBatch batch;
    batch.count = how_many;
    batch.grades = malloc(sizeof(int) * how_many);

    if (batch.grades == NULL) {
        printf("Allocation failed. The universe says no.\n");
        return;
    }

    initialize_grades(&batch, how_many);
    gather_academic_suffering(&batch, how_many);
    display_grades(&batch, how_many);

    free(batch.grades);  // Clean up your mess, even emotional ones
}
