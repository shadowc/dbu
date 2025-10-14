#pragma once
#include "ColorStyle.h"
#include "ForegroundColors.h"
#include "BackgroundColors.h"
#include "Color.h"

namespace Console { 
    struct ColorScheme {
        ColorScheme() {
            Paragraph = ColorStyle();
            Highlight = ColorStyle();
            Heading = ColorStyle();
            TitleBar = ColorStyle();
            TitleHighlight = ForegroundColors::CYAN;
            ButtonPrimary = ColorStyle();
            ButtonSecondary = ColorStyle();
            ButtonDanger = ColorStyle();
            Menu = ColorStyle();
            MenuHighlight = ForegroundColors::CYAN;
            MenuDisabled = ForegroundColors::GREY;
            MenuSelected = BackgroundColors::BLUE;
        }

        ColorScheme(
            ColorStyle p,
            ColorStyle hi,
            ColorStyle h,
            ColorStyle t,
            Color tH,
            ColorStyle btnP,
            ColorStyle btnS,
            ColorStyle btnD,
            ColorStyle m,
            Color mH,
            Color mD,
            Color mS
        ) {
            Paragraph = p;
            Highlight = hi;
            Heading = h;
            TitleBar = t;
            TitleHighlight = tH;
            ButtonPrimary = btnP;
            ButtonSecondary = btnS;
            ButtonDanger = btnD;
            Menu = m;
            MenuHighlight = mH;
            MenuDisabled = mD;
            MenuSelected = mS;
        }

        ColorStyle Paragraph;
        ColorStyle Highlight;
        ColorStyle Heading;
        ColorStyle TitleBar;
        Color TitleHighlight;
        ColorStyle ButtonPrimary;
        ColorStyle ButtonSecondary;
        ColorStyle ButtonDanger;
        ColorStyle Menu;
        Color MenuHighlight;
        Color MenuDisabled;
        Color MenuSelected;
    };
}
