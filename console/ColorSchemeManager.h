#pragma once
#include "ColorScheme.h"
#include "ColorStyle.h"
#include <map>
#include <string>

using namespace std;

namespace Console {
    class ColorSchemeManager {
    public:
        ColorSchemeManager();

        void addColorScheme(string name, ColorScheme colorScheme);
        void setColorScheme(string name);
        ColorScheme getColorScheme();

    private:
        ColorScheme SelectedScheme;
        map<string, ColorScheme> ColorSchemes;
    };
}
