#include <stdlib.h>
#include <sys/ioctl.h>

#include <food/food.h>
#include <terminal/terminal.h>


void change_position_of(s_food *food) {
    struct winsize terminal_dimensions = get_terminal_dimensions();
    int new_x = rand() % (terminal_dimensions.ws_col + 1);
    int new_y = rand() % (terminal_dimensions.ws_row + 1);

    food->f_x = new_x;
    food->f_y = new_y;
}