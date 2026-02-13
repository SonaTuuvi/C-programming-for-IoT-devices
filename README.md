# C-programming-for-IoT-devices
**C for IoT devices – low-level bugs, high-level ambitions.**  
(Proudly segfaulting smart devices since 2026.)

But here we are — because C doesn’t believe in making life easy,
and I don’t believe in writing boring code.

Also, I’m convinced this exercise was designed specifically
to make experienced developers feel like interns again.
Is it legal to waste this much brainpower on string length?

Anyway, it compiles. You're welcome.

---

## How to Run the Exercises Now

Good news: we've evolved.

No more manually commenting/uncommenting `run_exercise_X()` lines like it’s 1999.  
We now have a **menu**. Yes. An actual user-facing menu. Welcome to civilization.

### Steps:

1. Clone or download this glorious chaos.
2. Open the project in your IDE of choice. Or don’t. GCC is fine. Hope is optional.
3. Build the project.
4. Run it.
5. You’ll be greeted by:

- Welcome to the Exercise Chooser 3000
- Pick your flavor of pain today:
- 1 - Exercise 1
- 2 - Exercise 2
- ...
- 12 - Exercise 12
- 0 - Exit, because sanity matters



6. Pick a number. Press Enter.
7. Watch your chosen exercise either run flawlessly or drag you into C-induced madness.

---

## Project Structure (a.k.a. Organized Madness™)

Each exercise lives in its own directory:
- `Exercise_1/` to `Exercise_9/`
- Each has its own `.c` and `.h` file (because even chaos needs structure)
- Exercises are summoned through the great summoner: `menu.c`

All starts from:
- `main.c` → calls `show_exercise_menu()` → you choose your fate → something happens

---

## Example: Running Exercise 6

Choose `6` from the menu. You’ll experience:

- A polite dice-rolling menu (D6? D10? Want to quit?)
- Legit input validation
- A loop that only ends when you do

Because yes, **structure is love**.  
And also: _“just one file”_ is a myth whispered by the lazy.

---

## Philosophy

- **No copy-paste loops.** We write functions like adults.
- **No single-file hell.** Modular, because duct tape can only do so much.
- **Pointers? Sure. Sanity? Unclear.**
- **Comments have personality.** You’ll know exactly how the dev was feeling at 2:13am.

---

##  Notes

- If you get linker errors, it’s because two files are screaming for attention.
- If you get a segfault, well — welcome to C.
- If everything works the first time, you're hallucinating.

---

> _Commented with intention, formatted with pride, executed with random._  
> _Written by someone who’s been deep in the stack and came back with opinions._
