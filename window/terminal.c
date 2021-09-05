#include <terminal/terminal.h>
#include <termios.h>
#include <unistd.h>

static struct termios *old_terminal;

struct winsize get_terminal_dimensions() {
    struct winsize terminal_size;

    // get the width and height of the terminal.
    ioctl(0, TIOCGWINSZ, &terminal_size);

    return terminal_size;
}

int start_non_blocking_mode() {
    struct termios new_terminal;

    // backup current terminal.
    if (tcgetattr(STDIN_FILENO, old_terminal) == -1) return -1;
    // Change a few options.
    new_terminal.c_cc[VTIME] = 0;
    new_terminal.c_cc[VMIN] = 0;
    new_terminal.c_lflag &= ~(ICANON);
    new_terminal.c_lflag &= ~(ECHO);
    // Set the new terminal.
    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_terminal) == -1) return -1;

    return 0;
}

int stop_non_blocking_mode() {
    if (old_terminal == NULL) return -1;

    tcsetattr(STDIN_FILENO, TCSANOW, old_terminal);

    return 0;
}