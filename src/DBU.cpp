// DBU.cpp : Defines the entry point for the application.
//

#include "DBU.h"
#include "event/EventQueue.h"
#include "console/Console.h"
#include "widget/Screen.h"
#include "widget/Dialog.h"
#include "widget/Menu.h"
#include "widget/MenuItem.h"
#include <thread>
#include <chrono>

using namespace Console;
using namespace std;

void BuildUI(Screen* screen);

int main()
{
    ConsoleTty* console = ConsoleTty::getTty();
    EventQueue* eventQueue = EventQueue::GetInstance();

    console->clearScreen();
    console->hideCursor();

    // Create screen UI
    Screen* screen = new Screen();
    BuildUI(screen);

    screen->Invalidate();
    screen->Draw();

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

    delete screen;
    console->showCursor();
    console->resetColor();
    console->clearScreen();
    console->shutdown();
    eventQueue->Shutdown();

    return 0;
}

void BuildUI(Screen* screen)
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
    connectionMenuItem->SetAction([screen, connectionsMenu]() {
        screen->AddChild(connectionsMenu);
    });

    mainMenu->AddChild(connectionMenuItem);

    MenuItem* exitMenuItem = new MenuItem();
    exitMenuItem->SetLabel(" Exit ");
    exitMenuItem->SetAction([]() {
        EventQueue::GetInstance()->Exit();
    });

    mainMenu->AddChild(exitMenuItem);

    screen->AddChild(mainMenu);
}
