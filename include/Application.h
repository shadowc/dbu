#pragma once
#include "console/Console.h"
#include "config/Config.h"
#include "config/ConfigServerEntry.h"
#include <vector>

using namespace Console;

class EventQueue;
class Screen;
class MenuConfig;

class Application
{
public:
    static void Initialize();
    static void Run();
    static void Shutdown();

    static EventQueue* GetEventQueue();
    static ConsoleTty* GetConsole();
    static Screen* GetScreen();
    static MenuConfig* GetMenuConfig();
    static vector<ConfigServerEntry> GetConfigServers();

private:
    static EventQueue* eventQueue;
    static ConsoleTty* console;
    static Screen* screen;
    static MenuConfig* menuConfig;
    static Config* config;
};
