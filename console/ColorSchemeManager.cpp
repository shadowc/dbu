#include "ColorSchemeManager.h"
#include "ColorScheme.h"
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
            ColorStyle(ForegroundColors::BRIGHT_WHITE, BackgroundColors::CYAN), // Button Primary
            ColorStyle(ForegroundColors::BRIGHT_WHITE, BackgroundColors::GREY), // Button Secondary
            ColorStyle(ForegroundColors::BRIGHT_WHITE, BackgroundColors::RED) // Button Danger
        );
        
        ColorSchemes = map<string, ColorScheme>();
        SelectedScheme = scheme;

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