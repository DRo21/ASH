#include "core/terminal.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>

int get_terminal_height() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return 25; // Fallback
}

char get_key() {
    return _getch();
}

#else
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <stdio.h>

int get_terminal_height() {
    struct winsize w {};
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0)
        return w.ws_row;
    return 25;
}

char get_key() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif
