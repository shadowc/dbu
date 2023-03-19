// DBU.cpp : Defines the entry point for the application.
//

#include "DBU.h"
#include "event/EventQueue.h"
#include "event/EventDef.h"
#include "console/Console.h"
#include "console/ConsoleTools.h"
#include "console/Color.h"
#include "console/ColorScheme.h"
#include "console/ForegroundColors.h"
#include "console/BackgroundColors.h"
#include "console/Attributes.h"
#include "widget/Screen.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>

using namespace Console;
using namespace std;

// void Paint();

// Size cacheSize;
// int lastChar;
// bool charChanged;

int main()
{
    ConsoleTty* console = ConsoleTty::getTty();
    EventQueue* eventQueue = EventQueue::GetInstance();
    // cacheSize = console->getConsoleSize();
    ColorScheme scheme = console->getColorScheme();
    // lastChar = 0;

    console->clearScreen(scheme.Paragraph);
    console->hideCursor();
    // Paint();

    // Create screen UI
    Screen* screen = new Screen();
    screen->Invalidate();
    screen->Draw();

    // Event loop
    bool exiting = false;
    while (!exiting) {
        eventQueue->Loop();

        while (eventQueue->UnprocessedEvents()) {
            Event event = eventQueue->GetNextUnprocessedEvent();

            switch (event.Type) {
                case (EventType::Keyboard):
                    // lastChar = event.KeyCode;
                    // charChanged = true;
                    if (event.KeyCode == 27) {
                        exiting = true;
                    }

                    break;

                case (EventType::WindowResize):
                    // cacheSize.Width = event.NewScreenSize.Width;
                    // cacheSize.Height = event.NewScreenSize.Height;
                    screen->OnResize();

                    break;
            }
        }

        screen->Draw();
        
        // Loop at 60 fps (probably overkill)
        this_thread::sleep_for(chrono::milliseconds(16));
    }

    delete screen;
    console->showCursor();
    console->resetColor();
    console->clearScreen();
    eventQueue->Shutdown();

    return 0;
}

// void Paint() {
//     ConsoleTty* console = ConsoleTty::getTty();
//     ColorScheme scheme = console->getColorScheme();

//     console->clearScreen();

//     console->setPos(1, cacheSize.Height);
//     console->setColor(scheme.Paragraph);
//     cout << "Console size: " << cacheSize.Width << ", " << cacheSize.Height;

//     if (charChanged) {
//         cout << " Last char: " << lastChar;
//         charChanged = false;
//     }
// }
