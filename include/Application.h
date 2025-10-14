#pragma once
#include "console/Console.h"
#include "config/Config.h"
#include "config/ConfigServerEntry.h"
#include <vector>

using namespace Console;

class EventQueue;
class Screen;
class MenuManager;
class DialogManager;

class Application
{
public:
    static void Initialize();
    static void Run();
    static void Shutdown();

    static EventQueue* GetEventQueue();
    static ConsoleTty* GetConsole();
    static Screen* GetScreen();
    static MenuManager* GetMenuManager();
    static vector<ConfigServerEntry> GetConfigServers();
    static DialogManager* GetDialogManager();

private:
    static EventQueue* eventQueue;
    static ConsoleTty* console;
    static Screen* screen;
    static MenuManager* menuManager;
    static Config* config;
    static DialogManager* dialogManager;
};
