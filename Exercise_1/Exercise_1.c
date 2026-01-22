#include <stdio.h>
#include "Exercise_1.h"

/*
 * ----------------------------------------------------------------------------------
 *  Author: The Legend... named Sona
 *  Date:   21.01.2026
 *  Project: Transport Payment Simulation
 * -----------------------------------------------------------------------------------
*
 *  Description:
 *      Ever dreamed of taking a taxi but life hits you with €4.30?
 *      This program simulates your daily struggle:
 *        - Choose between bus and taxi
 *        - Cry when you can't afford either
 *        - Eventually walk home with dignity (or not)
 *
 *  Notes:
 *      - Runs on 100% pure C and caffeine.
 *      - Guaranteed to make your wallet feel seen.
 *      - Can be upgraded to include emotional damage simulation in version 2.0.
 *
 *  Usage:
 *      Compile, run, question your life choices.
 *
 *  Todo:
 *      - Add Uber and flying unicorn as transport options
 */

// Ask the user write ticket prices and converts them to cents (unsigned short)
void input_prices(Transport* transport)
{
    float temp;

    printf("Enter price of bus ticket: ");
    scanf("%f", &temp);
    transport->bus_ticket_price = (unsigned short)(temp * 100); // Convert to cents

    printf("Enter price of taxi: ");
    scanf("%f", &temp);
    transport->taxi_ticket_price = (unsigned short)(temp * 100); // Convert to cents
}

// Show transport options with their prices (converted back to euros)
void show_menu(const Transport* transport)
{
    printf("Do you want to take\n");
    printf("\t1) bus (%.2f euros)\n", transport->bus_ticket_price / 100.0);
    printf("\t2) taxi (%.2f euros)\n", transport->taxi_ticket_price / 100.0);
    printf("Enter your selection: ");
}

// Ask the user how much money they have and converts it to cents
void input_money(Person* person)
{
    float temp;

    printf("How much money you have: ");
    scanf("%f", &temp);
    person->money = (unsigned short)(temp * 100);
}

float get_money(const Person* person)
{
    return person->money/ 100.0f;
}

int can_afford_any(const Person* person, const Transport* transport)
{
    return (person->money >= transport->bus_ticket_price || person->money >= transport->taxi_ticket_price);
}

// Check if user's put correct number of choosing menu and also check money if they can afford it
void attempt_ride(Person* person, const Transport* transport, int choice)
{
    if (choice == 1) {
        printf("You chose bus.\n");
        if (person->money >= transport->bus_ticket_price) {
            person->money -= transport->bus_ticket_price;
            printf("You have %.2f euros left.\n", person->money);
        } else {
            printf("You don’t have enough money for bus.\n");
        }
    } else if (choice == 2) {
        printf("You chose taxi.\n");
        if (person->money >= transport->taxi_ticket_price) {
            person->money -= transport->taxi_ticket_price;
            printf("You have %.2f euros left.\n", person->money);
        } else {
            printf("You don’t have enough money for taxi.\n");
        }
    } else {
        printf("Invalid selection. Please enter 1 or 2.\n");
    }
}

// Main program logic: keeps asking until you're broke
void run_exercise_1()
{
    Transport transport;
    Person person;

    input_prices(&transport);   // Step 1: Get prices
    input_money(&person);       // Step 2: See how broke we are

    // Keep offering rides as long as the user can afford something
    while (can_afford_any(&person, &transport)) {
        printf("You have %.2f euros left.\n", get_money(&person));
        show_menu(&transport);

        int choice;
        scanf("%d", &choice);

        attempt_ride(&person, &transport, choice);
    }

    // If you're here, you're walking.
    printf("You need to walk. Bye\n");
}
