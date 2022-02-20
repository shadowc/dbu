#include "Console.h"
#include "ConsoleTools.h"
#include "Color.h"
#include "ColorSchemeManager.h"
#include "ColorScheme.h"
#include "ColorStyle.h"
#include <iostream>

using namespace std;

namespace Console {
	ConsoleTty* ConsoleTty::instance = nullptr;

	ConsoleTty::ConsoleTty()
	{
		colorSchemeManager = new ColorSchemeManager();
		cacheConsoleSize = Size();
	}

	ConsoleTty* ConsoleTty::getTty()
	{
		if (ConsoleTty::instance == nullptr) {
			ConsoleTty::instance = new ConsoleTty();
		}

		return ConsoleTty::instance;
	}

	ColorScheme ConsoleTty::getColorScheme()
	{
		return colorSchemeManager->getColorScheme();
	}

	void ConsoleTty::setColor(Color fg_color) 
	{
		cout << "\033[" << fg_color.getColorString() << "m";
	}

	void ConsoleTty::setColor(Color fg_color, Color bg_color)
	{
		cout << "\033[1;" << bg_color.getColorString() << ";" << fg_color.getColorString() << "m";
	}

	void ConsoleTty::setColor(Color fg_color, Color bg_color, Color attribute)
	{
		cout << "\033[" << attribute.getColorString() << ";" << bg_color.getColorString() << ";" << fg_color.getColorString() << "m";
	}

	void ConsoleTty::setColor(ColorStyle colorStyle)
	{
		setColor(colorStyle.fgColor, colorStyle.bgColor, colorStyle.Attribute);
	}

	void ConsoleTty::resetColor()
	{
		cout << "\033[0m";
	}

	void ConsoleTty::clearScreen()
	{
		cout << "\033[2J";
	}

	void ConsoleTty::clearScreen(ColorStyle colorStyle)
	{
		setColor(colorStyle);
		clearScreen();
	}

	void ConsoleTty::setPos(int col, int row)
	{
		cout << "\033[" << row << ";" << col << "f";
	}

	Size ConsoleTty::getConsoleSize()
	{
		if (cacheConsoleSize.Width == 0 && cacheConsoleSize.Height == 0) {
			cacheConsoleSize = _getConsoleSize();
		}

		return cacheConsoleSize;
	}
}
