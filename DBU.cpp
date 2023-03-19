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
#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>

using namespace Console;
using namespace std;

void Paint();

Size cacheSize;
int lastChar;
bool charChanged;

int main()
{
    ConsoleTty* console = ConsoleTty::getTty();
    EventQueue* eventQueue = EventQueue::GetInstance();
    cacheSize = console->getConsoleSize();
    ColorScheme scheme = console->getColorScheme();
    lastChar = 0;

    console->clearScreen(scheme.Paragraph);
    console->hideCursor();
    Paint();

    // Event loop
    bool exiting = false;
    while (!exiting) {
        eventQueue->Loop();

        bool hadUnprocessedEvents = false;
        while (eventQueue->UnprocessedEvents()) {
            Event event = eventQueue->GetNextUnprocessedEvent();

            switch (event.Type) {
                case (EventType::Keyboard):
                    hadUnprocessedEvents = true;
                    lastChar = event.KeyCode;
                    charChanged = true;
                    if (lastChar == 27) {
                        exiting = true;
                    }

                    break;

                case (EventType::WindowResize):
                    hadUnprocessedEvents = true;
                    cacheSize.Width = event.NewScreenSize.Width;
                    cacheSize.Height = event.NewScreenSize.Height;

                    break;
            }
        }

        if (hadUnprocessedEvents) {
            Paint();
        }

        // Loop at 60 fps (probably overkill)
        this_thread::sleep_for(chrono::milliseconds(16));
    }

    console->showCursor();
    console->resetColor();
    console->clearScreen();
    eventQueue->Shutdown();

    return 0;
}

void Paint() {
    ConsoleTty* console = ConsoleTty::getTty();
    ColorScheme scheme = console->getColorScheme();

    console->clearScreen();

    console->setPos(1, cacheSize.Height);
    console->setColor(scheme.Paragraph);
    cout << "Console size: " << cacheSize.Width << ", " << cacheSize.Height;

    if (charChanged) {
        cout << " Last char: " << lastChar;
        charChanged = false;
    }
}
