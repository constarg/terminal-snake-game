#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <draw_to_screen.h>
#include <terminal/terminal.h>
#include <terminal/keystrokes_codes.h>
#include <snake/snake.h>
#include <mem.h>
#include <unistd.h>


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
    struct winsize terminal_dimensions = get_terminal_dimensions();
    // Make the entities.
    size_t          snake_size = 1;
    g_snake_piece **snake_pieces = NULL;
    s_food         *snake_food   = NULL;

    // Allocate space for each entity.
    ALLOCATE_MEM(snake_pieces, 1, sizeof(g_snake_piece *));
    ALLOCATE_MEM(snake_food, 1, sizeof(s_food));

    // Initial values.
    // snake head
    ALLOCATE_MEM(snake_pieces[0], 1, sizeof(g_snake_piece));
    ALLOCATE_MEM(snake_pieces[0]->s_symbol, 1, sizeof(char));
    strcpy(snake_pieces[0]->s_symbol, SNAKE_HEAD) ;

    // Centralize the snake.
    snake_pieces[0]->s_x = (terminal_dimensions.ws_col - strlen(SNAKE_HEAD))/2;
    snake_pieces[0]->s_y = terminal_dimensions.ws_row / 2;

    // Food.
    ALLOCATE_MEM(snake_food->f_symbol, 1, sizeof(char));
    strcpy(snake_food->f_symbol, FOOD_SYMBOL);
    change_position_of(snake_food);

    // start the game.
    key_stroke_code = 0;
    while (move_snake(snake_pieces, &snake_size, snake_food, key_stroke_code) != 0) {
        key_stroke_code = get_pressed_key();
        usleep(55000);

        if (key_stroke_code == ENTER) {
            break;
        }
    }


    stop_non_blocking_mode();
    return 0;
}
