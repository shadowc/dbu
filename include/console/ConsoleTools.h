#pragma once
#include <platform.h>
#include "console/ConsoleDef.h"

namespace Console {
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
