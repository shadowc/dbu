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
            MenuSelected = ColorStyle();
            MenuDisabled = ColorStyle();
            MenuSelectedDisabled = ColorStyle();
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
            ColorStyle mD,
            ColorStyle mS,
            ColorStyle mSD
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
            MenuSelected = mS;
            MenuDisabled = mD;
            MenuSelectedDisabled = mSD;
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
        ColorStyle MenuDisabled;
        ColorStyle MenuSelected;
        ColorStyle MenuSelectedDisabled;
    };
}
