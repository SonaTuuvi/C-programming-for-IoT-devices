#include <stdio.h>
#include "Exercise_2.h"

/*
 * ----------------------------------------------------------------------------------
 *  Author: The Legend... named Sona
 *  Date:   22.01.2026
 *  Project: Tax Simulator 2026 – The Deduction Saga
 * ----------------------------------------------------------------------------------
 *
 *  Description:
 *      Simulates 12 months of salary and calculates tax.
 *      Base rate until you're broke. Then we double it.
 *
 *  Notes:
 *      - Uses progressive tax rate system
 *      - Clean decimal-aligned output that even your boss would approve
 *
 *  WARNING:
 *      Floating point math is NOT perfectly precise.
 *      Minor rounding demons may appear at runtime.
 *
 *  Future Upgrade (a.k.a. Ultimate Pain Mode):
 *      - Replace all float usage with unsigned int (storing cents)
 *      - Perform all calculations using integer math
 *      - Round properly, compare precisely
 *      - Eliminate rounding chaos forever
 *      - Achieve tax enlightenment
 *
 *  Usage:
 *      Compile, run, accept your fiscal destiny
 *
 *  Todo:
 *      - Cry in accountant
 *      - Add emotional damage statistics
 *      - Add yearly total tax
 *      - Add evil laugh sound effect (optional)
 * ----------------------------------------------------------------------------------
 */


// Reads basic tax configuration from the user:
// - base tax rate (applied until the income limit is reached)
// - yearly income limit
// - higher tax rate for income exceeding the limit
void input_tax_information(float* base_tax, float* limit, float* over_limit)
{
    printf("Enter tax rate: ");
    scanf("%f", base_tax);

    printf("Enter income limit: ");
    scanf("%f", limit);

    printf("Enter tax rate for income over the limit: ");
    scanf("%f", over_limit);
}

// Prompts the user to input monthly income for 12 months.
// Values are stored in the salaries array.
void input_salaries(float* salaries)
{
    for (int i = 0; i < MONTHS; ++i) {
        printf("Enter income for month %d: ", i + 1);
        scanf("%f", &salaries[i]);
    }
}

// Calculates monthly taxes using progressive tax logic:
// - Until the income limit is reached, apply the base rate
// - In the month, where the limit is exceeded, split the income:
//     part is taxed at base rate, the rest at the higher rate
// - After the limit is fully exceeded, apply higher rate to all income
void calculate_taxes(YearlyFinance* f,
                     float base_rate,
                     float threshold,
                     float doom_rate)
{
    float accumulated = 0.0f; // Running total of income across the year

    for (int month = 0; month < MONTHS; ++month)
    {
        float pay = f->salaries[month]; // Income for current month
        float slice = 0.0f;             // Calculated tax for current month

        if (accumulated >= threshold)
        {
            // Already over the limit — entire income is taxed at higher rate
            slice = pay * doom_rate / 100.0f;
        }
        else if ((accumulated + pay) <= threshold)
        {
            // Still below the limit — tax the full amount at base rate
            slice = pay * base_rate / 100.0f;
        }
        else
        {
            // This is the month where the limit is crossed
            float still_safe = threshold - accumulated;
            float now_doomed = pay - still_safe;

            slice = still_safe * base_rate / 100.0f +
                    now_doomed * doom_rate / 100.0f;
        }

        f->taxes[month] = slice;
        accumulated += pay;
    }
}

// Prints the final report:
// - month number (right-aligned, 5 characters)
// - income and tax with 2 decimal places and column alignment
void print_report(const YearlyFinance* f)
{
    printf("%-5s %10s %10s\n", "month", "income", "tax");

    for (int i = 0; i < MONTHS; ++i) {
        printf("%5d %10.2f %10.2f\n", i + 1, f->salaries[i], f->taxes[i]);
    }
}

// Really important function that runs the entire simulation:
// - Gets input
// - Calculates taxes
// - Prints the formatted tax table
void run_exercise_2(void)
{
    YearlyFinance finance;
    float base_tax, over_limit, limit;

    input_tax_information(&base_tax, &limit, &over_limit);
    input_salaries(finance.salaries);

    calculate_taxes(&finance, base_tax, limit, over_limit);

    print_report(&finance);
}
