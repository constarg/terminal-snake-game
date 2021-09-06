#include <draw_to_screen.h>
#include <terminal/terminal.h>
#include <terminal/keystrokes_codes.h>

int main() {
    //draw_start_screen();
    start_non_blocking_mode();

    int code = get_pressed_key();
    draw_start_screen();
    while (code != ENTER) {
        code = get_pressed_key();
    }

    stop_non_blocking_mode();
    return 0;
}
