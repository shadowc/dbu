#pragma once
#include <platform.h>

#ifdef __WIN32
    #define PATH_SEPARATOR "\\"
    #define USER_DIR "%localappdata%"
    #define CONFIG_DIR "Dbu"
    #define CONFIG_ENDL "\r\n"
#else
    #define PATH_SEPARATOR "/"
    #define USER_DIR getenv("HOME")
    #define CONFIG_DIR ".dbu"
    #define CONFIG_ENDL "\n"
#endif

#define CONFIG_FILE_NAME "config.txt"
