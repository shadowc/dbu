#pragma once
#include <platform.h>

#ifdef __WIN32
    #define _getKeyboardInput __getKeyboardInput_W

    int __getKeyboardInput_W();
#else 
    #define _getKeyboardInput __getKeyboardInput_L

    int kbhit();
    int __getKeyboardInput_L();
#endif
