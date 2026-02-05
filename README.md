# C-programming-for-IoT-devices
C for IoT devices – low-level bugs, high-level ambitions. (Proudly segfaulting smart devices since 2026.)

### **How to Run the Exercises**

_Clone or download the repo. You know the drill._

_Open main.c._

### Uncomment the line for the exercise you want to run — like this:
- // run_exercise_1();
- // run_exercise_2();
- // run_exercise_3();
- run_exercise_5(); // ← this is the chosen one

Build & run the project (gcc, your IDE, or just ✨ pure hope ✨).
Enjoy the chaos (or structure, depending on the task).

Example: Running Exercise 5
A 3-round dice game where the computer always wins (except when you roll a 6 — then it's "fair").
Input is validated.
Program is mildly sarcastic.


**No structs. No pointers. No stress. Okay, maybe just a little.**


## Exercise 6 – Dice Menu (The Structured Version™)

This ain't your average single-file throwaway.  
This is a *modular*, *commented*, and *gloriously separated* dice simulator.  
Because clarity matters. And so does sarcasm.

### What it does:
- Shows a menu: D6, D10, or Quit
- Validates input like a polite bouncer
- Rolls virtual dice using `rand()` (chaos, but controlled)
- Runs until the user gives up (as they should)

### Structure:
- `run_exercise_6.c` – logic, commentary, and sass
- `run_exercise_6.h` – declarations because structure is love
- Called from `main.c` because i respect entry points

### Why it's like this:
Because "just put it in one file" is not a rule, it’s a suggestion.  
And this dev? Chooses architecture over minimalism. Every time.

---

> *Commented with intention, formatted with pride, executed with random.*
