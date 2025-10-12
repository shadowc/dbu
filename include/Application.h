#pragma once
#include "console/Console.h"

using namespace Console;

class EventQueue;
class Screen;

class Application
{
public:
    static void Initialize();
    static void Run();
    static void Shutdown();

    static EventQueue* GetEventQueue();
    static ConsoleTty* GetConsole();
    static Screen* GetScreen();

private:
    static EventQueue* eventQueue;
    static ConsoleTty* console;
    static Screen* screen;

    static void BuildUI();
};
