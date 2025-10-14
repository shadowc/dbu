#include "config/Config.h"
#include "config/ConfigDef.h"
#include "config/ConfigTools.h"
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <filesystem>
#include <fstream>

using namespace std;

Config::Config()
{
    servers = vector<ConfigServerEntry>();
}

void Config::Load()
{
    // check if the config directory exists
    string configPath = _getUserFolder() + PATH_SEPARATOR + CONFIG_DIR;
    if (!std::filesystem::exists(configPath)) {
        return;
    }

    string filePath = configPath + PATH_SEPARATOR + CONFIG_FILE_NAME;
    if (!std::filesystem::exists(filePath)) {
        return;
    }

    // Load the config file
    ifstream configFile(filePath);
    stringstream buffer;
    buffer << configFile.rdbuf();
    Parse(buffer.str());
}

void Config::Save()
{
    // check if the config directory exists
    string configPath = _getUserFolder() + PATH_SEPARATOR + CONFIG_DIR;
    if (!filesystem::exists(configPath)) {
        filesystem::create_directory(configPath);
    }

    string filePath = configPath + PATH_SEPARATOR + CONFIG_FILE_NAME;
    
    // write the config file
    ofstream configFile = ofstream(filePath);
    configFile << Serialize();
    configFile.close();
}

string Config::Serialize()
{
    string result = "";

    for (const ConfigServerEntry& server : servers) {
        result += server.host + "," + server.username + "," + server.password + "," + server.db + "," + to_string(server.port) + CONFIG_ENDL;
    }

    return result;
}

void Config::Parse(string data)
{
    servers.clear();

    // Split by lines
    vector<string> lines;


    size_t pos = 0;
    while ((pos = data.find(CONFIG_ENDL)) != string::npos) {
        lines.push_back(data.substr(0, pos));
        data.erase(0, pos + strlen(CONFIG_ENDL));
    }

    for (const string& line : lines) {
        size_t start = 0;
        size_t end = line.find(',');
        vector<string> parts;

        while (end != string::npos) {
            parts.push_back(line.substr(start, end - start));
            start = end + 1;
            end = line.find(',', start);
        }

        parts.push_back(line.substr(start));

        if (parts.size() == 5) {
            ConfigServerEntry entry;
            entry.host = parts[0];
            entry.username = parts[1];
            entry.password = parts[2];
            entry.db = parts[3];
            entry.port = stoi(parts[4]);

            servers.push_back(entry);
        }
    }
}

vector<ConfigServerEntry> Config::GetServers()
{
    return servers;
}
