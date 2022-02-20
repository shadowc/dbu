// DBU.cpp : Defines the entry point for the application.
//

#include "DBU.h"
#include "console/Console.h"
#include "console/ConsoleTools.h"
#include "console/Color.h"
#include "console/ColorScheme.h"
#include "console/ForegroundColors.h"
#include "console/BackgroundColors.h"
#include "console/Attributes.h"
#include <iostream>

using namespace Console;
using namespace std;

int main()
{
	ConsoleTty* console = ConsoleTty::getTty();
	ColorScheme scheme = console->getColorScheme();
	Size cSize = console->getConsoleSize();

	console->clearScreen(scheme.Paragraph);

	console->setPos(1, cSize.Height);
	console->setColor(scheme.Paragraph);
	cout << "Console size: " << cSize.Width << ", " << cSize.Height;

	getchar();

	console->resetColor();
	console->clearScreen();
	return 0;
}
