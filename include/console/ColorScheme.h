#pragma once
#include "ColorStyle.h"

namespace Console { 
    struct ColorScheme {
        ColorScheme() {
            Paragraph = ColorStyle();
            Highlight = ColorStyle();
            Heading = ColorStyle();
            TitleBar = ColorStyle();
            ButtonPrimary = ColorStyle();
            ButtonSecondary = ColorStyle();
            ButtonDanger = ColorStyle();
            Menu = ColorStyle();
            MenuSelected = ColorStyle();
        }

        ColorScheme(
            ColorStyle p,
            ColorStyle hi,
            ColorStyle h,
            ColorStyle t,
            ColorStyle btnP,
            ColorStyle btnS,
            ColorStyle btnD,
            ColorStyle m,
            ColorStyle mS
        ) {
            Paragraph = p;
            Highlight = hi;
            Heading = h;
            TitleBar = t;
            ButtonPrimary = btnP;
            ButtonSecondary = btnS;
            ButtonDanger = btnD;
            Menu = m;
            MenuSelected = mS;
        }

        ColorStyle Paragraph;
        ColorStyle Highlight;
        ColorStyle Heading;
        ColorStyle TitleBar;
        ColorStyle ButtonPrimary;
        ColorStyle ButtonSecondary;
        ColorStyle ButtonDanger;
        ColorStyle Menu;
        ColorStyle MenuSelected;
    };
}
