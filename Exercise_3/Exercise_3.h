#ifndef EXERCISE_3_H
#define EXERCISE_3_H

// No matter how many students — they will all suffer the same loop
#define MAX_GRADES 1000  // Just in case someone gets ambitious
#define GRADE_NOT_SET -1


// We grade, therefore we cry
typedef struct {
    int* grades;   // Array of academic regrets (-1 means no grade yet)
    int count;     // Number of students brave enough to register
} StudentBatch;

// Summons the grading horror
void run_exercise_3(void);

// Asks how many students will disappoint us
int summon_student_count(void);

// Initializes their fates (-1 = undefined, untouched by knowledge)
void initialize_grades(StudentBatch* batch, int count);

// Enters the ritual loop: assign grades or back away slowly
void gather_academic_suffering(StudentBatch* batch, int count);

// Prints out the final scoreboard of dreams and voids
void display_grades(const StudentBatch* batch, int count);

#endif // EXERCISE_3_H
