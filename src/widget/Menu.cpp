#include "widget/Menu.h"
#include "console/Console.h"
#include <cmath>

void Menu::SetHorizontal()
{
    if (!horizontal) {
        horizontal = true;
        Invalidate();
    }
}   

void Menu::SetVertical()
{
    if (horizontal) {
        horizontal = false;
        Invalidate();
    }
}

bool Menu::IsHorizontal() const
{
    return horizontal;
}

bool Menu::IsVertical() const
{
    return !horizontal;
}

void Menu::SetTopPadding(int padding)
{
    if (padding != topPadding) {
        topPadding = padding;
        Invalidate();
    }
}

void Menu::SetSidePadding(int padding)
{
    if (padding != sidePadding) {
        sidePadding = padding;
        Invalidate();
    }
}

void Menu::Invalidate()
{
    AbstractWidget::Invalidate();

    if (parent != nullptr && horizontal) {
       // center dialog on parent screenspace
        Coords parentCoords = parent->GetPosition();
        Size parentSize = parent->GetSize();

        coords.X = max(0, parentCoords.X + sidePadding);
        coords.Y = max(0, parentCoords.Y + topPadding);

        size.Width = max(0, parentSize.Width - (sidePadding * 2)); 
        size.Height = 1; // fixed height for horizontal menu 
    }
}

void Menu::RenderWidget()
{
    ConsoleTty* console = ConsoleTty::getTty();
    ColorScheme scheme = console->getColorScheme();

    console->setColor(scheme.Menu);

    for (int y = coords.Y; y < coords.Y + size.Height; y++) {
        console->FillLine(y, coords.X, coords.X + size.Width, ' ');
    }
}
