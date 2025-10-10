#include "widget/Dialog.h"
#include "widget/AbstractWidget.h"
#include "console/ConsoleTools.h"
#include "console/Console.h"
#include <cmath>
#include <iostream>

using namespace Console;

Dialog::Dialog()
{
    title = "Dialog";
    visible = false;
    size.Width = 60;
    size.Height = 15;
    colorScheme = "dialog";
}

void Dialog::SetVisible(bool newVisible)
{
    if (newVisible != visible) {
        visible = newVisible;
        Invalidate();

        if (!visible && parent != nullptr) {
            parent->Invalidate();
        }
    }
}

void Dialog::SetTitle(string newTitle)
{
    title = newTitle;
    Invalidate();
}

void Dialog::RenderWidget()
{
    if (!visible) {
        return;
    }

    ConsoleTty* console = ConsoleTty::getTty();
    ColorScheme scheme = console->getColorScheme();

    // paint background
    console->setColor(scheme.Paragraph);

    console->DrawBox(coords.X, coords.Y, size.Width, size.Height);

    // Center title
    console->CenterString(coords.Y, coords.X, coords.X + size.Width, title);
}

bool Dialog::HasActiveMask()
{
    return visible;
}

void Dialog::SetParent(AbstractWidget* widget)
{
    AbstractWidget::SetParent(widget);
    colorScheme = "dialog";
}

void Dialog::Invalidate()
{
    AbstractWidget::Invalidate();

    if (parent != nullptr) {
       // center dialog on parent screenspace
        Coords parentCoords = parent->GetPosition();
        Size parentSize = parent->GetSize();

        coords.X = max(0, parentCoords.X + (int) floor(float(parentSize.Width / 2.0f)) - (int) floor(float(size.Width / 2.0f)));
        coords.Y = max(0, parentCoords.Y + (int) floor(float(parentSize.Height / 2.0f)) - (int) floor(float(size.Height / 2.0f)));
    }
}
