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

		void clearScreen();
		void clearScreen(ColorStyle colorStyle);
		void setPos(int col, int row);
		Size getConsoleSize();

	private:
		static ConsoleTty* instance;
		Size cacheConsoleSize;
		bool cursorVisible;
	};
}
