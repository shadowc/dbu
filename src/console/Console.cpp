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

    void ConsoleTty::FillLine(int y, int from, int to, const char* c)
    {
        setPos(from, y);
        for (int i = from; i <= to; i++) {
            printf("%s", c);
        }
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

    void ConsoleTty::DrawBox(int x, int y, int width, int height)
    {
        // Build top
        setPos(x, y);
        printf("┌");
        FillLine(y, x + 1, x + width - 1, "─");
        printf("┐");

        // fill dialog
        for (int i = y + 1; i < y + height; i++) {
            setPos(x, i);
            printf("│");
            FillLine(i, x + 1, x + width - 1, ' ');
            printf("│");
        }

        // Build bottom
        setPos(x, y + height);
        printf("└");
        FillLine(y + height, x + 1, x + width - 1, "─");
        printf("┘");
    }

    void ConsoleTty::clearScreen()
    {
        cout << "\033c" << std::flush;
    }

    void ConsoleTty::setPos(int col, int row)
    {
        cout << "\033[" << row << ";" << col << "f";
    }

    Size ConsoleTty::getConsoleSize()
    {
        return _getConsoleSize();
    }

    void ConsoleTty::Flush()
    {
        cout << std::flush;
    }
}
