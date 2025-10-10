#include "console/ColorSchemeManager.h"
#include "console/ColorScheme.h"
#include <string>
#include <map>

using namespace std;

namespace Console {
    ColorSchemeManager::ColorSchemeManager()
    {
        ColorScheme scheme = ColorScheme(
            ColorStyle(ForegroundColors::WHITE, BackgroundColors::BLUE), // paragraph
            ColorStyle(ForegroundColors::YELLOW, BackgroundColors::BLUE), // Highlight
            ColorStyle(ForegroundColors::CYAN, BackgroundColors::BLUE), // Heading
            ColorStyle(ForegroundColors::BLACK, BackgroundColors::WHITE), // Title bar
            ColorStyle(ForegroundColors::BRIGHT_WHITE, BackgroundColors::CYAN), // Button Primary
            ColorStyle(ForegroundColors::BRIGHT_WHITE, BackgroundColors::GREY), // Button Secondary
            ColorStyle(ForegroundColors::BRIGHT_WHITE, BackgroundColors::RED), // Button Danger
            ColorStyle(ForegroundColors::WHITE, BackgroundColors::GREY), // Menu
            ColorStyle(ForegroundColors::BRIGHT_WHITE, BackgroundColors::BLUE) // Menu Selected
        );
        
        ColorSchemes = map<string, ColorScheme>();
        SelectedScheme = scheme;

        ColorScheme dialog = ColorScheme(
            ColorStyle(ForegroundColors::BLACK, BackgroundColors::WHITE), // paragraph
            ColorStyle(ForegroundColors::BLUE, BackgroundColors::WHITE), // Highlight
            ColorStyle(ForegroundColors::MAGENTA, BackgroundColors::WHITE), // Heading
            ColorStyle(ForegroundColors::BLACK, BackgroundColors::CYAN), // Title bar
            ColorStyle(ForegroundColors::BRIGHT_WHITE, BackgroundColors::BLUE), // Button Primary
            ColorStyle(ForegroundColors::BRIGHT_WHITE, BackgroundColors::GREY), // Button Secondary
            ColorStyle(ForegroundColors::BRIGHT_WHITE, BackgroundColors::RED), // Button Danger
            ColorStyle(ForegroundColors::WHITE, BackgroundColors::GREY), // Menu
            ColorStyle(ForegroundColors::BRIGHT_WHITE, BackgroundColors::BLUE) // Menu Selected
        );

        addColorScheme(string("dialog"), dialog);
        addColorScheme(string("default"), scheme);
    }

    void ColorSchemeManager::addColorScheme(string name, ColorScheme colorScheme)
    {
        ColorSchemes.insert(pair<string, ColorScheme>(name, colorScheme));
    }

    void ColorSchemeManager::setColorScheme(string name)
    {
        SelectedScheme = ColorSchemes.at(name);
    }

    ColorScheme ColorSchemeManager::getColorScheme()
    {
        return SelectedScheme;
    }
}