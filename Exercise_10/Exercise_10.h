//
// Created by Sona on 10/2/2026 AD.
//

#ifndef IOT_LAITTEIDEN_C_OHJELMOINTI_EXERCISE_10_H
#define IOT_LAITTEIDEN_C_OHJELMOINTI_EXERCISE_10_H

#define INPUT_LIMIT 100         //Because apparently nobody ever types more than 100 chars. Sure.
#include <stdio.h>

typedef struct {
    char buffer[INPUT_LIMIT];   //Store the user's "thoughts" here (or lack thereof)
    size_t length;              // How long the suffering is
    int is_stop_signal;         // Did they finally say "stop"? Please, say yes!
}UserInput;


void run_exercise_10();         // Entry point to the abyss

#endif //IOT_LAITTEIDEN_C_OHJELMOINTI_EXERCISE_10_H