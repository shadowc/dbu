#pragma once
#include "BackgroundColors.h"
#include "ForegroundColors.h"
#include "Attributes.h"
#include "Color.h"

namespace Console {
    struct ColorStyle {
        ColorStyle() {
            fgColor = ForegroundColors::WHITE;
            bgColor = BackgroundColors::BLACK;
            Attribute = Attributes::NORMAL;
        }

        ColorStyle(Color fg) {
            fgColor = fg;
            bgColor = BackgroundColors::BLACK;
            Attribute = Attributes::NORMAL;
        }

        ColorStyle(Color fg, Color bk) {
            fgColor = fg;
            bgColor = bk;
            Attribute = Attributes::NORMAL;
        }

        ColorStyle(Color fg, Color bk, Color attr) {
            fgColor = fg;
            bgColor = bk;
            Attribute = attr;
        }

        Color fgColor;
        Color bgColor;
        Color Attribute;
    };
}