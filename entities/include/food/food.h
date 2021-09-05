#ifndef TERMINAL_SNAKE_GAME_FOOD_H
#define TERMINAL_SNAKE_GAME_FOOD_H 1

#define POINT_PER_CATCH 1;


typedef struct s_food {
    short int f_x;
    short int f_y;
} s_food;

extern void change_position_of(s_food food, short int x, short int y);


#endif
