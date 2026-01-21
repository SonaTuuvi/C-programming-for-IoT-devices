#ifndef EXERCISE_1_H
#define EXERCISE_1_H

typedef struct
{
    unsigned short bus_ticket_price;
    unsigned short taxi_ticket_price;
} Transport;

typedef struct
{
    unsigned short money;
} Person;

// Transport-related functions
void input_prices(Transport* t);
void show_menu(const Transport* t);

// Person-related functions
void input_money(Person* p);
float get_money(const Person* p);
void attempt_ride(Person* p, const Transport* t, int choice);
int can_afford_any(const Person* p, const Transport* t);

// Main logic starts here
void run_program();

#endif //IOT_LAITTEIDEN_C_OHJELMOINTI_Р_H
