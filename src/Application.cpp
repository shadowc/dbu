#include "Application.h"
#include "event/EventQueue.h"
#include "console/Console.h"
#include "widget/Screen.h"
#include "menu-config/MenuConfig.h"
#include "config/Config.h"
#include <vector>
#include <thread>
#include <chrono>

using namespace Console;

EventQueue* Application::eventQueue = nullptr;
ConsoleTty* Application::console = nullptr;
Screen* Application::screen = nullptr;
MenuConfig* Application::menuConfig = nullptr;
Config* Application::config = nullptr;

void Application::Initialize()
{
    if (eventQueue == nullptr) {
        eventQueue = new EventQueue();
    }

    if (console == nullptr) {
        console = new ConsoleTty();
    }

    if (screen == nullptr) {
        screen = new Screen();
    }

    if (menuConfig == nullptr) {
        menuConfig = new MenuConfig();
    }

    if (config == nullptr) {
        config = new Config();
    }

    console->clearScreen();
    console->hideCursor();

    menuConfig->RenderMenu();
    screen->Invalidate();
    screen->Draw();
}

void Application::Run()
{
    // Event loop
    while (!eventQueue->IsExiting()) {
        // We need to pass screen here to perform the first draw because ncurses clears the
        // screen the first time we poll for input
        eventQueue->Loop();

        while (eventQueue->UnprocessedEvents()) {
            eventQueue->ProcessNextEvent();
        }

        if (!eventQueue->IsExiting()) {
            screen->Draw();
        
            // Loop at 60 fps (probably overkill)
            this_thread::sleep_for(chrono::milliseconds(16));
        }
    }
}

void Application::Shutdown()
{
    console->showCursor();
    console->resetColor();
    console->clearScreen();

    if (screen != nullptr) {
        delete screen;
        screen = nullptr;
    }

    if (console != nullptr) {
        delete console;
        console = nullptr;
    }

    if (eventQueue != nullptr) {
        delete eventQueue;
        eventQueue = nullptr;
    }

    if (menuConfig != nullptr) {
        delete menuConfig;
        menuConfig = nullptr;
    }

    if (config != nullptr) {
        config->Save();
        delete config;
        config = nullptr;
    }
}

EventQueue* Application::GetEventQueue()
{
    return eventQueue;
}

ConsoleTty* Application::GetConsole()
{
    return console;
}

Screen* Application::GetScreen()
{
    return screen;
}

MenuConfig* Application::GetMenuConfig()
{
    return menuConfig;
}

vector<ConfigServerEntry> Application::GetConfigServers()
{
    if (config == nullptr) {
        return vector<ConfigServerEntry>();
    }

    return config->GetServers();
}
