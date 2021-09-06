#include <unistd.h>

#include <draw_to_screen.h>
#include <terminal/terminal.h>
#include <mem.h>
#include <string.h>

#define START_MSG   "Start Game"
#define ENTER_MSG   "Press Enter"


void draw_start_screen() {
    CLEAR_SCREEN();
    fflush(stdin);

    struct winsize terminal_dimensions = get_terminal_dimensions();

    unsigned short text_location_x = terminal_dimensions.ws_col/2;
    unsigned short text_location_y = terminal_dimensions.ws_row/2;
    text_location_x -= 2;
    text_location_y -= 3;

    GO_TO(text_location_x - 4, text_location_y);
    printf("%s\n", START_MSG);

    char *enter_msg = NULL;
    ALLOCATE_MEM(enter_msg, strlen(ENTER_MSG) + strlen("|   ") + 5, sizeof(char));
    strcpy(enter_msg, "|   ");
    strcat(enter_msg, ENTER_MSG);
    strcat(enter_msg, "   ");
    strcat(enter_msg, "|");

    char *to_draw[3] = {
            "+-----------------+\n",
            enter_msg,
            "+-----------------+\n"
    };

    for (int draw = 0; draw < 3; draw++) {
        GO_TO(text_location_x - 8, text_location_y + draw + 1);
        printf("%s", to_draw[draw]);
    }

    free(enter_msg);
}