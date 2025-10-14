#pragma once
#include <string>

using namespace std;

struct ConfigServerEntry
{
    string host;
    string username;
    string password;
    string db;
    unsigned int port;
};
