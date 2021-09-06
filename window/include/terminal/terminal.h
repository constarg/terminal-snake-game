#ifndef TERMINAL_SNAKE_GAME_TERMINAL_H
#define TERMINAL_SNAKE_GAME_TERMINAL_H 1

#include <sys/ioctl.h>
#include <stdio.h>

#define CLEAR_SCREEN() printf("\033[2J");
#define GO_TO(X,Y) printf("\033[%d;%dH", (Y), (X));

extern struct winsize get_terminal_dimensions();

extern int start_non_blocking_mode();

extern int stop_non_blocking_mode();

extern int get_pressed_key();

#endif
