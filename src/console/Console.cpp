#include "console/Console.h"
#include "console/ConsoleTools.h"
#include "console/Color.h"
#include "console/ColorSchemeManager.h"
#include "console/ColorScheme.h"
#include "console/ColorStyle.h"
#include <iostream>
#include <cmath>

using namespace std;

namespace Console {
    ConsoleTty* ConsoleTty::instance = nullptr;

    ConsoleTty::ConsoleTty()
    {
        colorSchemeManager = new ColorSchemeManager();

        _initConsoleInputMode();
        // Start with cursorVisible=false and ensure we have a cursor
        cursorVisible = false;
        showCursor();
    }

    void ConsoleTty::shutdown()
    {
        _cleanupConsoleInputMode();
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

    void ConsoleTty::hideCursor()
    {
        if (cursorVisible) {
            cout << "\033[?25l";
            cursorVisible = false;
        }
    }

    void ConsoleTty::showCursor()
    {
        if (!cursorVisible) {
            cout << "\033[?25h";
            cursorVisible = true;
        }
    }

    bool ConsoleTty::isCursorVisible()
    {
        return cursorVisible;
    }

    void ConsoleTty::FillLine(int y, int from, int to, char c)
    {
        setPos(from, y);
        for (int i = from; i <= to; i++) {
            cout << c;
        }
    }

    void ConsoleTty::CenterString(int y, int from, int to, string str)
    {
        int width = to - from;
    
        setPos(from + (int)(floor((float)width / 2.0f) - floor((float)str.length() / 2)), y);
        cout << str;
    }

    void ConsoleTty::clearScreen()
    {
        cout << "\033c";
    }

    void ConsoleTty::clearScreen(ColorStyle colorStyle)
    {
        setColor(colorStyle);
        cout << "\033[2J";
    }

    void ConsoleTty::setPos(int col, int row)
    {
        cout << "\033[" << row << ";" << col << "f";
    }

    Size ConsoleTty::getConsoleSize()
    {
        return _getConsoleSize();
    }
}
