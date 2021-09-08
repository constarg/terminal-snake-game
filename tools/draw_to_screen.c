#include <string.h>

#include <draw_to_screen.h>
#include <terminal/terminal.h>


#define START_MSG       "Press Enter to Play"
#define GAME_OVER_MSG   "Game Over Press Enter to exit."

static void draw(char *msg) {
    CLEAR_SCREEN();

    struct winsize terminal_dimensions = get_terminal_dimensions();

    unsigned short text_location_x = (terminal_dimensions.ws_col - strlen(msg))/2;
    unsigned short text_location_y = terminal_dimensions.ws_row/2;

    GO_TO(text_location_x, text_location_y);
    printf("%s\n", msg);
}

void draw_start_screen() {
    draw(START_MSG);
}

void draw_game_over_screen() {
    draw(GAME_OVER_MSG);
}