#include "Screen.h"
#include "../console/Console.h"
#include "../console/ConsoleTools.h"
#include "../event/EventQueue.h"
#include <iostream>
#include <string>

using namespace Console;
using namespace std;

void Screen::OnResize()
{
    Size screenSize = EventQueue::GetInstance()->GetScreenSize();

    size.Width = screenSize.Width;
    size.Height= screenSize.Height;

    Invalidate();
}

void Screen::Initialize() 
{
    coords.X = 1;
    coords.Y = 1;

    OnResize();
}

void Screen::RenderWidget()
{
    ConsoleTty* console = ConsoleTty::getTty();
    ColorScheme scheme = console->getColorScheme();

    string titleStr = " DBU - No connection ";
    console->setPos(floor((float)size.Width / 2.0f) - floor((float)titleStr.length() / 2), coords.Y);
    console->setColor(scheme.Heading);

    cout << titleStr;
    
    console->setPos(1, size.Height);
    console->setColor(scheme.Paragraph);
    cout << "Console size: " << size.Width << ", " << size.Height;
}
