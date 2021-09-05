#ifndef TERMINAL_SNAKE_GAME_SNAKE_H
#define TERMINAL_SNAKE_GAME_SNAKE_H 1

typedef struct g_snake {
    short int s_x;
    short int s_y;
    short int s_width;

} g_snake;

extern int move_snake(g_snake snake, short int x, short int y, int direction);

#endif
