#ifndef TERMINAL_SNAKE_GAME_SNAKE_H
#define TERMINAL_SNAKE_GAME_SNAKE_H 1

#include <food/food.h>
#include <stdlib.h>

#define SNAKE_HEAD_UP       '^'
#define SNAKE_HEAD_DOWN     'v'
#define SNAKE_HEAD_RIGHT    '>'
#define SNAKE_HEAD_LEFT     '<'
#define SNAKE_TAIL          '+'

typedef struct g_snake_piece {
    int   s_x;
    int   s_y;
    char  s_symbol;

} g_snake_piece;

extern int move_snake(int direction);

extern void initialize();

extern void destruct();

#endif
