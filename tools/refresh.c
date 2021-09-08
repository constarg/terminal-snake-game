#include <stdio.h>

#include <refresh.h>
#include <terminal/terminal.h>

static inline void print_snake_pieces(g_snake_piece **snake_pieces, size_t snake_size) {

    for (size_t piece = 0; piece < snake_size; piece++) {
        GO_TO(snake_pieces[piece]->s_x, snake_pieces[piece]->s_y);
        printf("%c", snake_pieces[piece]->s_symbol);
    }
}

static inline void print_snake_food(s_food *food) {

    GO_TO(food->f_x, food->f_y);
    printf("%c", food->f_symbol);
}

void refresh_game(g_snake_piece **snake_pieces, size_t snake_size, s_food *food) {
    print_snake_pieces(snake_pieces, snake_size);
    print_snake_food(food);
    fflush(stdout);
}