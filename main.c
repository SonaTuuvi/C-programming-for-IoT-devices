#include <stdio.h>
#include "menu.h"

int main(void) {
    // Чтобы IDE не мешала порядок/задержку вывода
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    show_exercise_menu();
    return 0;
}