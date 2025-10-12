#include "Application.h"
#include "event/EventQueue.h"
#include "console/Console.h"
#include "widget/Screen.h"
#include "widget/Menu.h"
#include "widget/MenuItem.h"
#include <thread>
#include <chrono>

using namespace Console;

EventQueue* Application::eventQueue = nullptr;
ConsoleTty* Application::console = nullptr;
Screen* Application::screen = nullptr;

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

    console->clearScreen();
    console->hideCursor();

    BuildUI();

    screen->Invalidate();
    screen->Draw();
}

void Application::Run()
{
    // Event loop
    while (!eventQueue->IsExiting()) {
        // We need to pass screen here to perform the first draw because ncurses clears the
        // screen the first time we poll for input
        eventQueue->Loop(screen);

        while (eventQueue->UnprocessedEvents()) {
            eventQueue->ProcessNextEvent(screen);
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

void Application::BuildUI()
{
    Menu* connectionsMenu = new Menu();
    connectionsMenu->SetVertical();

    MenuItem* connectMenuItem = new MenuItem();
    connectMenuItem->SetLabel(" Connect to server... ");
    connectionsMenu->AddChild(connectMenuItem);

    MenuItem* manageConnectionsMenuItem = new MenuItem();
    manageConnectionsMenuItem->SetLabel(" Manage connections... ");
    connectionsMenu->AddChild(manageConnectionsMenuItem);

    Menu* mainMenu = new Menu();

    MenuItem* connectionMenuItem = new MenuItem();
    connectionMenuItem->SetLabel(" Connections ");
    connectionMenuItem->SetAction([connectionsMenu]() {
        Application::GetScreen()->AddChild(connectionsMenu);
    });

    mainMenu->AddChild(connectionMenuItem);

    MenuItem* exitMenuItem = new MenuItem();
    exitMenuItem->SetLabel(" Exit ");
    exitMenuItem->SetAction([]() {
        Application::GetEventQueue()->Exit();
    });

    mainMenu->AddChild(exitMenuItem);

    screen->AddChild(mainMenu);
}
