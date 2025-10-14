#include <platform.h>
#ifdef __WIN32
#include "shlobj.h"
#endif
#include <string>

using namespace std;

#ifdef __WIN32
    #define _getUserFolder  __getUserFolder_W

    string __getUserFolder_W()
    {
        char path[MAX_PATH];
        if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &path))) {
            return string(path);
        }

        return string("");
    }
#else
    #define _getUserFolder  __getUserFolder_L

    string __getUserFolder_L()
    {
        const char* homeDir = getenv("HOME");
        if (homeDir != nullptr) {
            return string(homeDir);
        }

        return string("");
    }   
#endif
