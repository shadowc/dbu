#include "event/KeyboardTools.h"

#ifdef __WIN32
#include <conio.h>
#else
#include <ncurses.h>
#endif

#ifdef __WIN32

int _getKeyboardInput()
{
    int lastChar = 0;
    while (_kbhit()) {
        lastChar = _getch();
    }
    return lastChar;
}

#else

int __getKeyboardInput_L()
{
    // TODO: Implement using ncurses
    return 0;
}

#endif