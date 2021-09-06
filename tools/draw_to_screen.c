#include <string.h>

#include <draw_to_screen.h>
#include <terminal/terminal.h>


#define START_MSG   "Press Enter to Play"


void draw_start_screen() {
    CLEAR_SCREEN();
    fflush(stdin);

    struct winsize terminal_dimensions = get_terminal_dimensions();

    unsigned short text_location_x = (terminal_dimensions.ws_col - strlen(START_MSG))/2;
    unsigned short text_location_y = terminal_dimensions.ws_row/2;

    GO_TO(text_location_x, text_location_y);
    printf("%s\n", START_MSG);
}