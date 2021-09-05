#ifndef TERMINAL_SNAKE_GAME_TERMINAL_H
#define TERMINAL_SNAKE_GAME_TERMINAL_H 1

#include <sys/ioctl.h>

#define CLEAR_SCREEN(SCREEN_HEIGHT) printf("\033[2J");

extern struct winsize get_terminal_dimensions();



#endif
