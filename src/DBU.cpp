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
#include <thread>
#include <chrono>

using namespace Console;
using namespace std;

int main()
{
    ConsoleTty* console = ConsoleTty::getTty();
    EventQueue* eventQueue = EventQueue::GetInstance();
    ColorScheme scheme = console->getColorScheme();

    console->clearScreen(scheme.Paragraph);
    console->hideCursor();

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
                    if (event.KeyCode == 27) {
                        exiting = true;
                    }

                    screen->SetLastCharPressed(event.KeyCode);

                    break;

                case (EventType::WindowResize):
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
