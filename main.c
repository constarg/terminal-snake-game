#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <draw_to_screen.h>
#include <terminal/terminal.h>
#include <terminal/keystrokes_codes.h>
#include <snake/snake.h>
#include <mem.h>
#include <unistd.h>

#include <refresh.h>


int main() {
    srand(time(NULL));
    start_non_blocking_mode();

    int key_stroke_code = get_pressed_key();
    draw_start_screen();
    while (key_stroke_code != ENTER) {
        key_stroke_code = get_pressed_key();
        usleep(5000);
    }
    CLEAR_SCREEN();

    initialize();
    // start the game.
    key_stroke_code = 0;
    while (move_snake(key_stroke_code) != 0) {
        key_stroke_code = get_pressed_key();
        usleep(55000);

        if (key_stroke_code == ENTER) {
            break;
        }
    }
    
    draw_game_over_screen();
    while (key_stroke_code != ENTER) {
        key_stroke_code = get_pressed_key();
        usleep(5000);
    }

    destruct();
    stop_non_blocking_mode();
    return 0;
}
