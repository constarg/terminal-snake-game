#ifndef TERMINAL_SNAKE_GAME_SNAKE_H
#define TERMINAL_SNAKE_GAME_SNAKE_H 1

#include <food/food.h>
#include <stdlib.h>

#define SNAKE_HEAD   "■"
#define SNAKE_TAIL   "■"

typedef struct g_snake_piece {
    int   s_x;
    int   s_y;
    char *s_symbol;

} g_snake_piece;

extern int move_snake(g_snake_piece **snake_pieces, size_t *snake_size, s_food *food, int direction);

#endif
