#include "widget/Dialog.h"
#include "widget/AbstractWidget.h"
#include "console/ConsoleTools.h"
#include "console/Console.h"

#include <iostream>

using namespace Console;

Dialog::Dialog()
{
    title = "Dialog";
    visible = false;
    size.Width = 60;
    size.Height = 15;
}

void Dialog::SetVisible(bool newVisible)
{
    if (newVisible != visible) {
        visible = newVisible;
        Invalidate();
    }
}

void Dialog::SetTitle(string newTitle)
{
    title = newTitle;
    Invalidate();
}

void Dialog::RenderWidget()
{
    AbstractWidget* screen = parent;

    if (parent == nullptr) {
        return;
    }

    ConsoleTty* console = ConsoleTty::getTty();
    ColorScheme scheme = console->getColorScheme();

    // center dialog on parent screenspace
    Coords parentCoords = parent->GetPosition();
    Size parentSize = parent->GetSize();

    coords.X = floor(float((parentSize.Width - parentCoords.X - 1) / 2.0f)) - floor(float(size.Width / 2.0f));
    coords.Y = floor(float((parentSize.Height - parentCoords.Y - 1) / 2.0f)) - floor(float(size.Height / 2.0f));

    // paint background
    console->setColor(scheme.TitleBar);

    // Build top
    console->setPos(coords.X, coords.Y);
    printf("\u00DA");
    console->FillLine(coords.Y, coords.X + 1, size.Width - 1, '\u00C4');
    printf("\u00BF");

    // Center title
    console->CenterString(coords.Y, coords.X, size.Width, title);

    // fill dialog
    for (int i = coords.Y + 1; i < coords.Y + size.Height; i++) {
        console->setPos(coords.X, i);
        printf("\u00B3");
        console->FillLine(i, coords.X + 1, size.Width - 1, ' ');
        printf("\u00B3");
    }

    // Build bottom
    console->setPos(coords.X, coords.Y + size.Height);
    printf("\u00C0");
    console->FillLine(coords.Y + size.Height, coords.X + 1, size.Width - 1, '\u00C4');
    printf("\u00D9");
}
