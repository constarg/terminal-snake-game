#include <string.h>

#include <snake/snake.h>
#include <refresh.h>
#include <equations.h>
#include <terminal/keystrokes_codes.h>
#include <terminal/terminal.h>
#include <mem.h>

static int dx = 1;
static int dy = 0;
static char head = SNAKE_HEAD_RIGHT;
static g_snake_piece **snake_pieces = NULL;
static s_food         *snake_food   = NULL;
static size_t          snake_size   = 1;

static inline int is_food_eaten() {
    double distance = calculate_distance(snake_pieces[0]->s_x, snake_pieces[0]->s_y,
                                          snake_food->f_x, snake_food->f_y);

    if (distance < 5)
        return 1;
    else
        return 0;
}

static void move_pieces() {
    // Save the position that the next piece should be.
    int x_for_next;
    int y_for_next;
    int x_tmp;
    int y_tmp;

    for (size_t curr_piece = 0; curr_piece < snake_size; curr_piece++) {
        if (curr_piece + 1 == snake_size) {
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
            snake_pieces[curr_piece]->s_symbol = head;
            continue;
        }

    }
}

void increase_snake_size() {
    // increase the array.

    REALLOCATE_MEM(snake_pieces, sizeof(g_snake_piece *) * snake_size);

    // configure the new piece.
    g_snake_piece *new_piece = NULL;
    ALLOCATE_MEM(new_piece, 1, sizeof(g_snake_piece));
    new_piece->s_x = 0;
    new_piece->s_y = 0;
    new_piece->s_symbol = SNAKE_TAIL;

    // Set the new piece into the array.
    snake_pieces[snake_size - 1] = new_piece;
}

static int is_snake_hit_wall() {
    struct winsize terminal_dimension = get_terminal_dimensions();

    int snake_current_x = snake_pieces[0]->s_x;
    int snake_current_y = snake_pieces[0]->s_y;

    printf("%d", snake_current_x);

    if (snake_current_x > terminal_dimension.ws_col || snake_current_x == -1 ||
        snake_current_y > terminal_dimension.ws_row || snake_current_y == -1) {

        return 1;
    }

    else
        return 0;
}

static int is_snake_hit_himself() {
    g_snake_piece snake_head = {
            .s_x = snake_pieces[0]->s_x,
            .s_y = snake_pieces[0]->s_x,
            .s_symbol = snake_pieces[0]->s_symbol
    };

    if (snake_size <= 2) return 0;

    double distance_piece;

    for (int piece = 2; piece < snake_size; piece++) {
        distance_piece = calculate_distance(
                    snake_head.s_x,
                    snake_head.s_y,
                    snake_pieces[piece]->s_x,
                    snake_pieces[piece]->s_y
                );

        if (distance_piece == 0)
            return 1;
    }

    return 0;
}


static int is_snake_killed() {

    if (is_snake_hit_wall()) {
        printf("HIT HIMSELF");
        return 1;
    }
    if (is_snake_hit_himself()) {
        printf("HIT WALL");
        return 1;
    }


    return 0;

}

int move_snake(int direction) {
    if      (direction == UPP_ARROW)    dy = -1, dx =  0, head = SNAKE_HEAD_UP;
    else if (direction == DOWN_ARROW)   dy =  1, dx =  0, head = SNAKE_HEAD_DOWN;
    else if (direction == RIGHT_ARROW)  dy =  0, dx =  1, head = SNAKE_HEAD_RIGHT;
    else if (direction == LEFT_ARROW)   dy =  0, dx = -1, head = SNAKE_HEAD_LEFT;

    move_pieces();

    if (is_snake_killed()) return 0;
    //
    if (is_food_eaten()) {
        change_position_of(snake_food);
        snake_size = snake_size + 1;
        increase_snake_size();
        move_pieces();
    }


    refresh_game(snake_pieces, snake_size, snake_food);
    return 1;
}

void initialize() {
    struct winsize terminal_dimensions = get_terminal_dimensions();

    // Allocate space for each entity.
    ALLOCATE_MEM(snake_pieces, 1, sizeof(g_snake_piece *));
    ALLOCATE_MEM(snake_food, 1, sizeof(s_food));

    // Initial values.
    // snake head
    ALLOCATE_MEM(snake_pieces[0], 1, sizeof(g_snake_piece));
    snake_pieces[0]->s_symbol = SNAKE_HEAD_RIGHT;

    // Centralize the snake.
    snake_pieces[0]->s_x = (terminal_dimensions.ws_col - 1)/2;
    snake_pieces[0]->s_y = terminal_dimensions.ws_row / 2;

    // Food.
    snake_food->f_symbol = FOOD_SYMBOL;
    change_position_of(snake_food);
}

void destruct() {

    for (int piece = 0; piece < snake_size; piece++)
        free(snake_pieces[piece]);

    free(snake_pieces);
    free(snake_food);
}