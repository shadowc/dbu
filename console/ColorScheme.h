#pragma once
#include "ColorStyle.h"

namespace Console { 
    struct ColorScheme {
        ColorScheme() {
            Paragraph = ColorStyle();
            Highlight = ColorStyle();
            Heading = ColorStyle();
            ButtonPrimary = ColorStyle();
            ButtonSecondary = ColorStyle();
            ButtonDanger = ColorStyle();
        }

        ColorScheme(ColorStyle p, ColorStyle hi, ColorStyle h, ColorStyle btnP, ColorStyle btnS, ColorStyle btnD) {
            Paragraph = p;
            Highlight = hi;
            Heading = h;
            ButtonPrimary = btnP;
            ButtonSecondary = btnS;
            ButtonDanger = btnD;
        }

        ColorStyle Paragraph;
        ColorStyle Highlight;
        ColorStyle Heading;
        ColorStyle ButtonPrimary;
        ColorStyle ButtonSecondary;
        ColorStyle ButtonDanger;
    };
}
