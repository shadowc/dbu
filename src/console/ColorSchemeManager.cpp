#include "console/ColorSchemeManager.h"
#include "console/ColorScheme.h"
#include "console/ColorStyle.h"
#include "console/ForegroundColors.h"
#include "console/BackgroundColors.h"
#include <string>
#include <map>

using namespace std;

namespace Console {
    ColorSchemeManager::ColorSchemeManager()
    {
        ColorScheme defaultScheme = ColorScheme(
            ColorStyle(ForegroundColors::WHITE, BackgroundColors::BLUE), // paragraph
            ColorStyle(ForegroundColors::YELLOW, BackgroundColors::BLUE), // Highlight
            ColorStyle(ForegroundColors::CYAN, BackgroundColors::BLUE), // Heading
            ColorStyle(ForegroundColors::BLACK, BackgroundColors::WHITE), // Title bar
            ForegroundColors::CYAN, // Title highlight
            ColorStyle(ForegroundColors::BRIGHT_WHITE, BackgroundColors::CYAN), // Button Primary
            ColorStyle(ForegroundColors::BRIGHT_WHITE, BackgroundColors::GREY), // Button Secondary
            ColorStyle(ForegroundColors::BRIGHT_WHITE, BackgroundColors::RED), // Button Danger
            ColorStyle(ForegroundColors::WHITE, BackgroundColors::GREY), // Menu
            ColorStyle(ForegroundColors::WHITE, BackgroundColors::CYAN), // Menu Selected
            ColorStyle(ForegroundColors::BLACK, BackgroundColors::GREY), // Menu Disabled
            ColorStyle(ForegroundColors::GREY, BackgroundColors::CYAN) // Menu Selected
        );
        
        ColorSchemes = map<string, ColorScheme>();
        SelectedScheme = defaultScheme;

        ColorScheme dialog = ColorScheme(
            ColorStyle(ForegroundColors::BLACK, BackgroundColors::WHITE), // paragraph
            ColorStyle(ForegroundColors::BLUE, BackgroundColors::WHITE), // Highlight
            ColorStyle(ForegroundColors::MAGENTA, BackgroundColors::WHITE), // Heading
            ColorStyle(ForegroundColors::BLACK, BackgroundColors::CYAN), // Title bar
            ForegroundColors::CYAN, // Title highlight
            ColorStyle(ForegroundColors::BRIGHT_WHITE, BackgroundColors::BLUE), // Button Primary
            ColorStyle(ForegroundColors::BRIGHT_WHITE, BackgroundColors::GREY), // Button Secondary
            ColorStyle(ForegroundColors::BRIGHT_WHITE, BackgroundColors::RED), // Button Danger
            ColorStyle(ForegroundColors::WHITE, BackgroundColors::GREY), // Menu
            ColorStyle(ForegroundColors::WHITE, BackgroundColors::CYAN), // Menu Selected
            ColorStyle(ForegroundColors::BLACK, BackgroundColors::GREY), // Menu Disabled
            ColorStyle(ForegroundColors::GREY, BackgroundColors::CYAN) // Menu Selected
        );

        addColorScheme(string("dialog"), dialog);
        addColorScheme(string("default"), defaultScheme);
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
