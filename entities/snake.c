#include <string.h>

#include <snake/snake.h>
#include <refresh.h>
#include <equations.h>
#include <terminal/keystrokes_codes.h>
#include <terminal/terminal.h>
#include <mem.h>

static int dx = 1;
static int dy = 0;

static inline int is_food_eaten(g_snake_piece **snake_pieces, s_food *food) {
    int distance = calculate_distance(snake_pieces[0]->s_x, snake_pieces[0]->s_y,
                                          food->f_x, food->f_y);

    if (distance < 5)
        return 1;
    else
        return 0;
}

static void move_pieces(g_snake_piece **snake_pieces, size_t *snake_size) {
    // Save the position that the next piece should be.
    int x_for_next;
    int y_for_next;
    int x_tmp;
    int y_tmp;

    for (size_t curr_piece = 0; curr_piece < *snake_size; curr_piece++) {
        if (curr_piece + 1 == *snake_size) {
            GO_TO(snake_pieces[curr_piece]->s_x, snake_pieces[curr_piece]->s_y);
            printf(" ");
        }

        if (curr_piece > 0) {
            x_tmp = snake_pieces[curr_piece]->s_x;
            y_tmp = snake_pieces[curr_piece]->s_y;
            snake_pieces[curr_piece]->s_x = x_for_next;
            snake_pieces[curr_piece]->s_y = y_for_next;
            x_for_next = x_tmp;
            y_for_next = y_tmp;
            continue;
        }

        // If the current piece is head.
        if (curr_piece == 0) {
            x_for_next = snake_pieces[curr_piece]->s_x;
            y_for_next = snake_pieces[curr_piece]->s_y;
            snake_pieces[curr_piece]->s_x += dx;
            snake_pieces[curr_piece]->s_y += dy;
            continue;
        }

    }
}

static inline void increase_snake_size(g_snake_piece **snake_pieces, size_t *snake_size) {

    // increase the array.
    REALLOCATE_MEM(snake_pieces, sizeof(g_snake_piece *) * *snake_size);

    // configure the new piece.
    g_snake_piece *new_piece = NULL;
    ALLOCATE_MEM(new_piece, 1, sizeof(g_snake_piece));
    ALLOCATE_MEM(new_piece->s_symbol, 1, sizeof(char));

    new_piece->s_symbol = SNAKE_TAIL;

    // Set the new piece into the array.
    snake_pieces[*snake_size - 1] = new_piece;

}

static int is_snake_killed(g_snake_piece **snake_pieces) {

    struct winsize terminal_dimension = get_terminal_dimensions();

    int snake_current_x = snake_pieces[0]->s_x;
    int snake_current_y = snake_pieces[0]->s_y;

    int distance_from_wall = calculate_distance(snake_current_x, snake_current_y,
                                                terminal_dimension.ws_col, terminal_dimension.ws_row);


    if (distance_from_wall < 5)
        return 1;
    else
        return 0;

}

int move_snake(g_snake_piece **snake_pieces, size_t *snake_size, s_food *food, int direction) {
    if      (direction == UPP_ARROW)    dy = -1, dx =  0;
    else if (direction == DOWN_ARROW)   dy =  1, dx =  0;
    else if (direction == RIGHT_ARROW)  dy =  0, dx =  1;
    else if (direction == LEFT_ARROW)   dy =  0, dx = -1;

    move_pieces(snake_pieces, snake_size);

    if (is_snake_killed(snake_pieces)) return 0;

    if (is_food_eaten(snake_pieces, food)) {
        change_position_of(food);
        *snake_size = *snake_size + 1;
        increase_snake_size(snake_pieces, snake_size);
    }


    refresh_game(snake_pieces, snake_size, food);

    return 1;
}