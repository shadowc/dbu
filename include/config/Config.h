#pragma once
#include <vector>
#include "config/ConfigServerEntry.h"

using namespace std;

class Config
{
public:
    Config();

    void Save();
    vector<ConfigServerEntry> GetServers();
    
protected:
    void Load();
    string Serialize();
    void Parse(string data);
    vector<ConfigServerEntry> servers;
};
