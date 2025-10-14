#pragma once
#include <platform.h>
#include <string>

#ifdef __WIN32
#include "shlobj.h"
#endif

using namespace std;

#ifdef __WIN32
    #define _getUserFolder  __getUserFolder_W

    string __getUserFolder_W();
#else
    #define _getUserFolder  __getUserFolder_L

    string __getUserFolder_L();
#endif
