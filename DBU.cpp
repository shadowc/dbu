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

void Paint(ConsoleTty* console, bool force);

Size cacheSize;
int lastChar;
bool charChanged;

int main()
{
	ConsoleTty* console = ConsoleTty::getTty();
	EventQueue* eventQueue = EventQueue::GetInstance();
	cacheSize = console->getConsoleSize();
	lastChar = 0;

	console->hideCursor();
	Paint(console, true);

	// Event loop
	bool exiting = false;
	while (!exiting) {
		Paint(console, false);

		eventQueue->Loop();

		while (eventQueue->UnprocessedEvents()) {
			Event event = eventQueue->GetNextUnprocessedEvent();

			switch (event.Type) {
				case (EventType::Keyboard):
					lastChar = event.KeyCode;
					charChanged = true;
					if (lastChar == 27) {
						exiting = true;
					}
					
					break;
			}
		}

		this_thread::sleep_for(chrono::milliseconds(16));
	}

	console->showCursor();
	console->resetColor();
	console->clearScreen();
	eventQueue->Shutdown();

	return 0;
}

void Paint(ConsoleTty* console, bool force) {
	ColorScheme scheme = console->getColorScheme();
	Size cSize = console->getConsoleSize();

	if (cSize.Width != cacheSize.Width || cSize.Height != cacheSize.Height || force || charChanged) {
		cacheSize.Width = cSize.Width;
		cacheSize.Height = cSize.Height;

		console->clearScreen(scheme.Paragraph);

		console->setPos(1, cSize.Height);
		console->setColor(scheme.Paragraph);
		cout << "Console size: " << cSize.Width << ", " << cSize.Height;

		if (charChanged) {
			cout << " Last char: " << lastChar;
			charChanged = false;
		}
	}
}
