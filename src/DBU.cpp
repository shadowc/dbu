// DBU.cpp : Defines the entry point for the application.
//

#include "DBU.h"
#include "event/EventQueue.h"
#include "event/EventDef.h"
#include "event/KeyCodes.h"
#include "console/Console.h"
#include "console/ConsoleTools.h"
#include "console/Color.h"
#include "console/ColorScheme.h"
#include "console/ForegroundColors.h"
#include "console/BackgroundColors.h"
#include "console/Attributes.h"
#include "widget/Screen.h"
#include "widget/Dialog.h"
#include "widget/Menu.h"
#include "widget/MenuItem.h"
#include <thread>
#include <chrono>

using namespace Console;
using namespace std;

Dialog* BuildUI(Screen* screen);

int main()
{
    ConsoleTty* console = ConsoleTty::getTty();
    EventQueue* eventQueue = EventQueue::GetInstance();
    ColorScheme scheme = console->getColorScheme();

    console->clearScreen();
    console->hideCursor();

    // Create screen UI
    Screen* screen = new Screen();
    Dialog* dialog = BuildUI(screen);

    screen->Invalidate();
    screen->Draw();

    // Event loop
    bool exiting = false;
    while (!exiting) {
        // We need to pass screen here to perform the first draw because ncurses clears the
        // screen the first time we poll for input
        eventQueue->Loop(screen);

        while (eventQueue->UnprocessedEvents()) {
            Event event = eventQueue->GetNextUnprocessedEvent();

            switch (event.Type) {
                case (EventType::Keyboard):
                    switch (event.KeyCode) {
                        case (KEY_ESC):
                            exiting = true;
                            break;
                        case (KEY_UP):
                            dialog->SetVisible(true);
                            break;
                        case (KEY_DOWN):
                            dialog->SetVisible(false);
                            break;    
                    }

                    screen->SetLastCharPressed(event.KeyCode);

                    break;

                case (EventType::WindowResize):
                    this_thread::sleep_for(chrono::milliseconds(5));
                    screen->OnResize();

                    break;
            }
        }

        if (!exiting) {
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

Dialog* BuildUI(Screen* screen)
{
    Dialog* connectionDialog = new Dialog();
    connectionDialog->SetTitle(" MySQL Connection ");
    connectionDialog->SetVisible(true);

    screen->AddChild(connectionDialog);

    Menu* mainMenu = new Menu();

    MenuItem* connectionMenuItem = new MenuItem();
    connectionMenuItem->SetLabel(" Connections ");
    mainMenu->AddChild(connectionMenuItem);

    MenuItem* exitMenuItem = new MenuItem();
    exitMenuItem->SetLabel(" Exit ");
    mainMenu->AddChild(exitMenuItem);

    screen->AddChild(mainMenu);

    return connectionDialog;
}
