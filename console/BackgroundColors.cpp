#include "BackgroundColors.h"
#include "Color.h"

namespace Console {
	Color BackgroundColors::BLACK = Color(40, "40");
	Color BackgroundColors::RED = Color(41, "41");
	Color BackgroundColors::GREEN = Color(42, "42");
	Color BackgroundColors::YELLOW = Color(43, "43");
	Color BackgroundColors::BLUE = Color(44, "44");
	Color BackgroundColors::MAGENTA = Color(45, "45");
	Color BackgroundColors::CYAN = Color(46, "46");
	Color BackgroundColors::WHITE = Color(47, "47");
	Color BackgroundColors::GREY = Color(100, "100");
	Color BackgroundColors::BRIGHT_RED = Color(101, "101");
	Color BackgroundColors::BRIGHT_GREEN = Color(102, "102");
	Color BackgroundColors::BRIGHT_YELLOW = Color(103, "103");
	Color BackgroundColors::BRIGHT_BLUE = Color(104, "104");
	Color BackgroundColors::BRIGHT_MAGENTA = Color(105, "105");
	Color BackgroundColors::BRIGHT_CYAN = Color(106, "106");
	Color BackgroundColors::BRIGHT_WHITE = Color(107, "107");

	Color BackgroundColors::ByIndex[16] = {
		BackgroundColors::BLACK,
		BackgroundColors::RED,
		BackgroundColors::GREEN,
		BackgroundColors::YELLOW,
		BackgroundColors::BLUE,
		BackgroundColors::MAGENTA,
		BackgroundColors::CYAN,
		BackgroundColors::WHITE,
		BackgroundColors::GREY,
		BackgroundColors::BRIGHT_RED,
		BackgroundColors::BRIGHT_GREEN,
		BackgroundColors::BRIGHT_YELLOW,
		BackgroundColors::BRIGHT_BLUE,
		BackgroundColors::BRIGHT_MAGENTA,
		BackgroundColors::BRIGHT_CYAN,
		BackgroundColors::BRIGHT_WHITE
	};
}
