#include <terminal/terminal.h>
#include <termios.h>
#include <unistd.h>


struct winsize get_terminal_dimensions() {
    struct winsize terminal_size;

    // get the width and height of the terminal.
    ioctl(0, TIOCGWINSZ, &terminal_size);

    return terminal_size;
}
