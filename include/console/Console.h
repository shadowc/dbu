#pragma once
#include "Color.h"
#include "ColorSchemeManager.h"
#include "ColorStyle.h"
#include "ConsoleTools.h"

namespace Console {
    class ConsoleTty {
    private:
        ConsoleTty();

    public:
        static ConsoleTty* getTty();
        ColorSchemeManager* colorSchemeManager;

        ColorScheme getColorScheme();

        void setColor(Color fg_color);
        void setColor(Color fg_color, Color bg_color);
        void setColor(Color fg_color, Color bg_color, Color attribute);
        void setColor(ColorStyle colorStyle);

        void resetColor();

        void hideCursor();
        void showCursor();
        bool isCursorVisible();

        void FillLine(int y, int from, int to, char c);
        void CenterString(int y, int from, int to, string str);

        void clearScreen();
        void setPos(int col, int row);
        Size getConsoleSize();

        void shutdown();

    private:
        static ConsoleTty* instance;
        bool cursorVisible;
    };
}
