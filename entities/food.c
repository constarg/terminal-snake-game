#include <stdlib.h>
#include <sys/ioctl.h>

#include <food/food.h>
#include <terminal/terminal.h>


void change_position_of(s_food *food) {
    struct winsize terminal_dimension = get_terminal_dimensions();
    int new_x = rand() % (terminal_dimension.ws_col + 1);
    int new_y = rand() % (terminal_dimension.ws_row + 1);

    GO_TO(food->f_x, food->f_y);
    printf(" ");
    fflush(stdout);

    food->f_x = new_x;
    food->f_y = new_y;
}