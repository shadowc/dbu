#include "ForegroundColors.h"
#include "Color.h"

namespace Console {
	Color ForegroundColors::BLACK = Color(30, "30");
	Color ForegroundColors::RED = Color(31, "31");
	Color ForegroundColors::GREEN = Color(32, "32");
	Color ForegroundColors::YELLOW = Color(33, "33");
	Color ForegroundColors::BLUE = Color(34, "34");
	Color ForegroundColors::MAGENTA = Color(35, "35");
	Color ForegroundColors::CYAN = Color(36, "36");
	Color ForegroundColors::WHITE = Color(37, "37");
	Color ForegroundColors::GREY = Color(90, "90");
	Color ForegroundColors::BRIGHT_RED = Color(91, "91");
	Color ForegroundColors::BRIGHT_GREEN = Color(92, "92");
	Color ForegroundColors::BRIGHT_YELLOW = Color(93, "93");
	Color ForegroundColors::BRIGHT_BLUE = Color(94, "94");
	Color ForegroundColors::BRIGHT_MAGENTA = Color(95, "95");
	Color ForegroundColors::BRIGHT_CYAN = Color(96, "96");
	Color ForegroundColors::BRIGHT_WHITE = Color(97, "97");

	Color ForegroundColors::ByIndex[16] = {
		ForegroundColors::BLACK,
		ForegroundColors::RED,
		ForegroundColors::GREEN,
		ForegroundColors::YELLOW,
		ForegroundColors::BLUE,
		ForegroundColors::MAGENTA,
		ForegroundColors::CYAN,
		ForegroundColors::WHITE,
		ForegroundColors::GREY,
		ForegroundColors::BRIGHT_RED,
		ForegroundColors::BRIGHT_GREEN,
		ForegroundColors::BRIGHT_YELLOW,
		ForegroundColors::BRIGHT_BLUE,
		ForegroundColors::BRIGHT_MAGENTA,
		ForegroundColors::BRIGHT_CYAN,
		ForegroundColors::BRIGHT_WHITE
	};
}
