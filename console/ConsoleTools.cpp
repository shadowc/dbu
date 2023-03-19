#include <platform.h>
#include "ConsoleTools.h"
#include <stdio.h>

#ifdef __WIN32
#include <Windows.h>
#else
#include <sys/ioctl.h>
#endif

namespace Console {
    #ifdef __WIN32

    Size __getConsoleSize_W()
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int columns, rows;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        return Size(columns, rows);
    }

    void __initConsoleInputMode_W()
    {
        HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

        DWORD dwOriginalInMode = 0;
        GetConsoleMode(hIn, &dwOriginalInMode);

        DWORD dwRequestedInModes = ENABLE_VIRTUAL_TERMINAL_INPUT;
        DWORD dwInMode = dwOriginalInMode | dwRequestedInModes;
        SetConsoleMode(hIn, dwInMode);
    }

    #else

    Size __getConsoleSize_L()
    {
        struct winsize max;
        ioctl(0, TIOCGWINSZ, &max);

        return Size(max.ws_col, max.ws_row);
    }

    void __initConsoleInputMode_L()
    {
    }

    #endif
}