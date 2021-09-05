#include <terminal/terminal.h>
#include <termios.h>
#include <unistd.h>
#include <memory.h>

#include <mem.h>
#include <terminal/keystrokes_codes.h>

#define FALSE 0
#define TRUE  1


static struct termios *old_terminal;
static int non_blocking_enabled = FALSE;

struct winsize get_terminal_dimensions() {
    struct winsize terminal_size;

    // get the width and height of the terminal.
    ioctl(0, TIOCGWINSZ, &terminal_size);

    return terminal_size;
}

int start_non_blocking_mode() {
    struct termios new_terminal;

    ALLOCATE_MEM(old_terminal, 1, sizeof(struct termios));
    // backup current terminal.
    if (tcgetattr(STDIN_FILENO, old_terminal) == -1) return -1;
    // Change a few options.
    new_terminal.c_cc[VTIME] = 0;
    new_terminal.c_cc[VMIN] = 0;
    new_terminal.c_lflag &= ~(ICANON);
    new_terminal.c_lflag &= ~(ECHO);
    // Set the new terminal.
    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_terminal) == -1) return -1;

    non_blocking_enabled = TRUE;
    return 0;
}

int stop_non_blocking_mode() {
    if (old_terminal == NULL) return -1;

    tcsetattr(STDIN_FILENO, TCSANOW, old_terminal);

    free(old_terminal);
    non_blocking_enabled = FALSE;
    return 0;
}


int get_pressed_kay() {
    char buffer[3];
    ssize_t len;

    if (!non_blocking_enabled) return -1;

    len = read(STDIN_FILENO, &buffer, sizeof(buffer));

    if (len > 0) {
        int code_1 = (int) buffer[0], code_2 = (int) buffer[1], code_3 = (int) buffer[2];
        // check the codes.
        if (code_1 == 0x1b && code_2 == 0x5b && code_3 == UPP_ARROW) return UPP_ARROW;
        else if (code_1 == 0x1b && code_2 == 0x5b && code_3 == DOWN_ARROW) return DOWN_ARROW;
        else if (code_1 == 0x1b && code_2 == 0x5b && code_3 == RIGHT_ARROW) return RIGHT_ARROW;
        else if (code_1 == 0x1b && code_2 == 0x5b && code_3 == LEFT_ARROW) return LEFT_ARROW;
        else if (code_1 == 0xd && code_2 == 0x0 && code_3 == ENTER) return ENTER;
    }

    return -1;
}