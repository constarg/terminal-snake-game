#ifndef TERMINAL_SNAKE_GAME_FOOD_H
#define TERMINAL_SNAKE_GAME_FOOD_H 1

#define FOOD_SYMBOL 'O'

typedef struct s_food {
    short int f_x;
    short int f_y;
    char      f_symbol;
} s_food;

extern void change_position_of(s_food *food);

#endif
