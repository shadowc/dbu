#pragma once
#include <platform.h>

namespace Console {
    struct Coords {
        Coords() {
            X = 0;
            Y = 0;
        }

        Coords(int x, int y) {
            X = x;
            Y = y;
        }

        int X;
        int Y;
    };

    struct Size {
        Size() {
            Width = 0;
            Height = 0;
        }

        Size(int w, int h) {
            Width = w;
            Height = h;
        }

        int Width;
        int Height;
    };

    #ifdef __WIN32
        #define _getConsoleSize __getConsoleSize_W
        #define _initConsoleInputMode __initConsoleInputMode_W
        #define _cleanupConsoleInputMode __cleanupConsoleInputMode_W

        Size __getConsoleSize_W();
        void __initConsoleInputMode_W();
        void __cleanupConsoleInputMode_W();
    #else 
        #define _getConsoleSize __getConsoleSize_L
        #define _initConsoleInputMode __initConsoleInputMode_L
        #define _cleanupConsoleInputMode __cleanupConsoleInputMode_L

        Size __getConsoleSize_L();
        void __initConsoleInputMode_L();
        void __cleanupConsoleInputMode_L();
    #endif
}
