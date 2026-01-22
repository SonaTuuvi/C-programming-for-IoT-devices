#ifndef EXERCISE_2_H
#define EXERCISE_2_H

// We're suffering for 12 months, not one less
#define MONTHS 12


// Struct of your financial fate
// YES, i am using arrays — just wrapped in a struct for sanity.
// Cleaner, safer, still 100% legal.
typedef struct {
    float salaries[MONTHS];   // Monthly happiness injection (Array of monthly incomes (€))
    float taxes[MONTHS];      // Monthly depression extraction (Array of monthly tax deductions (€))
} YearlyFinance;


// Function declarations

void input_tax_information(float* base_tax, float* limit, float* over_limit_tax);
void input_salaries(float* salaries);
void calculate_taxes(YearlyFinance* f, float base_tax, float limit, float over_limit_tax);
void print_report(const YearlyFinance* f);

// Runs the whole circus
void run_exercise_2(void);

#endif // EXERCISE_2_H
