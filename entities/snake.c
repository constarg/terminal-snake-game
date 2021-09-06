#include <string.h>

#include <snake/snake.h>
#include <refresh.h>
#include <equations.h>
#include <terminal/keystrokes_codes.h>
#include <mem.h>

static int dx = 5;
static int dy = 5;

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

    // Set the new piece into the array.
    snake_pieces[snake_size - 1] = new_piece;

}

void move_snake(g_snake_piece **snake_pieces, size_t *snake_size, s_food *food, int direction) {
    if ( (direction == UPP_ARROW && dy > 0) || (direction == DOWN_ARROW && dy < 0)) dy = -dy;
    else if ( (direction == RIGHT_ARROW && dx < 0) || (direction == LEFT_ARROW && dx > 0)) dx = -dx;

    move_pieces(snake_pieces, snake_size);

    if (is_food_eaten(snake_pieces, food)) {
        change_position_of(food);
        snake_size += 1;
        increase_snake_size(snake_pieces, snake_size);
    }


    refresh_game(snake_pieces, food);
}
