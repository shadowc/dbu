#include "Application.h"
#include "event/EventQueue.h"
#include "console/Console.h"
#include "widget/Screen.h"
#include "menu-manager/MenuManager.h"
#include "dialog-manager/DialogManager.h"
#include "config/Config.h"
#include <vector>
#include <thread>
#include <chrono>

using namespace Console;

EventQueue* Application::eventQueue = nullptr;
ConsoleTty* Application::console = nullptr;
Screen* Application::screen = nullptr;
MenuManager* Application::menuManager = nullptr;
Config* Application::config = nullptr;
DialogManager* Application::dialogManager = nullptr;

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

    if (menuManager == nullptr) {
        menuManager = new MenuManager();
    }

    if (config == nullptr) {
        config = new Config();
    }

    if (dialogManager == nullptr) {
        dialogManager = new DialogManager();
    }

    console->clearScreen();
    console->hideCursor();

    menuManager->RenderMenu();
    dialogManager->AttachDialogsToScreen();
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

    if (menuManager != nullptr) {
        delete menuManager;
        menuManager = nullptr;
    }

    if (dialogManager != nullptr) {
        delete dialogManager;
        dialogManager = nullptr;
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

MenuManager* Application::GetMenuManager()
{
    return menuManager;
}

vector<ConfigServerEntry> Application::GetConfigServers()
{
    return config->GetServers();
}

DialogManager* Application::GetDialogManager()
{
    return dialogManager;
}
