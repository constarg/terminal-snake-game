#include <stdlib.h>
#include <time.h>

#include <draw_to_screen.h>
#include <terminal/terminal.h>
#include <terminal/keystrokes_codes.h>
#include <snake/snake.h>

int main() {
    srand(time(NULL));
    start_non_blocking_mode();

    int code = get_pressed_key();
    draw_start_screen();
    while (code != ENTER) {
        code = get_pressed_key();
    }

    // start the game.




    stop_non_blocking_mode();
    return 0;
}
