#ifndef TERMINAL_SNAKE_GAME_TERMINAL_H
#define TERMINAL_SNAKE_GAME_TERMINAL_H 1

#include <sys/ioctl.h>

#define CLEAR_SCREEN(SCREEN_HEIGHT) printf("\033[2J");
#define GO_TO(X,Y) printf("\033[%d;%dH", (X), (Y));

extern struct winsize get_terminal_dimensions();

extern int start_non_blocking_mode();

extern int stop_non_blocking_mode();

#endif
