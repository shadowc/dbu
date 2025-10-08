#include "event/KeyboardTools.h"

#ifdef __WIN32
#include <conio.h>
#else
#include <ncurses.h>
#endif

#ifdef __WIN32

int __getKeyboardInput_W()
{
    int lastChar = 0;
    while (_kbhit()) {
        lastChar = _getch();
    }
    return lastChar;
}

#else

int kbhit()
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

int __getKeyboardInput_L()
{
    noecho();
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);

    int lastChar = 0;

    while (kbhit()) {
        lastChar = getch();
    }

    return lastChar;
}

#endif
