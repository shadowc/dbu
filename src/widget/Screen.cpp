#include "platform.h"
#include "widget/Screen.h"
#include "console/Console.h"
#include "console/ConsoleTools.h"
#include "event/EventQueue.h"
#include <iostream>
#include <string>

using namespace Console;
using namespace std;

Screen::Screen() 
    : AbstractWidget() 
{
    coords.X = 1;
    coords.Y = 1;
    lastKeyCode = 0;
    platformName = __PLATFORM;
    versionMajor = to_string(APP_VERSION_MAJOR);
    versionMinor = to_string(APP_VERSION_MINOR);
    OnResize();
}

void Screen::OnResize()
{
    Size screenSize = EventQueue::GetInstance()->GetScreenSize();

    size.Width = screenSize.Width;
    size.Height= screenSize.Height;

    Invalidate();
}

void Screen::SetLastCharPressed(char keyCode)
{
    lastKeyCode = keyCode;
    Invalidate();
}

void Screen::RenderWidget()
{
    ConsoleTty* console = ConsoleTty::getTty();
    ColorScheme scheme = console->getColorScheme();

    string titleStr = " DBU " + versionMajor + "." + versionMinor + " - " + platformName + " - No connection ";

    // Draw title bar
    console->setColor(scheme.TitleBar);
    console->FillLine(1, coords.X, size.Width, ' ');
    console->CenterString(1, coords.X, size.Width, titleStr);
    
    // Draw status bar
    console->FillLine(size.Height, coords.X, size.Width, ' ');
    console->setPos(2, size.Height);
    printf("Console size: %dx%d \u00B3", size.Width, size.Height);

    console->setPos(size.Width - 24, size.Height);
    printf("\u00B3 Last key pressed: %d ", lastKeyCode);

    console->setColor(scheme.Paragraph);
    for (int y = 2; y < size.Height - 1; y++) {
        console->FillLine(y, coords.X, size.Width, ' ');
    }
}
