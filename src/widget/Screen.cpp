#include "platform.h"
#include "widget/Screen.h"
#include "Application.h"
#include "console/Console.h"
#include "console/ConsoleTools.h"
#include "event/EventQueue.h"
#include "event/KeyCodes.h"
#include "menu-config/MenuConfig.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

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
    Size screenSize = Application::GetEventQueue()->GetScreenSize();

    size.Width = screenSize.Width;
    size.Height = screenSize.Height;

    Invalidate();
}

void Screen::SetLastCharPressed(int keyCode)
{
    lastKeyCode = keyCode;
    Invalidate();
}

void Screen::RenderWidget()
{
    ConsoleTty* console = Application::GetConsole();
    ColorScheme scheme = console->getColorScheme();

    string titleStr = " DBU " + versionMajor + "." + versionMinor + " - " + platformName + " - No connection ";

    // Draw title bar
    console->setColor(scheme.TitleBar);
    console->FillLine(1, coords.X, size.Width, ' ');
    console->CenterString(1, coords.X, size.Width, titleStr);
    
    // Draw status bar
    console->FillLine(size.Height, coords.X, size.Width, ' ');
    console->setPos(2, size.Height);
    console->setColor(ForegroundColors::CYAN);
    printf("F9");
    console->setColor(scheme.TitleBar);
    printf(" Menu │ ");
    console->setColor(ForegroundColors::CYAN);
    printf("Esc");
    console->setColor(scheme.TitleBar);
    printf(" Exit");

    console->setPos(size.Width - 24, size.Height);
    printf("│ Last key pressed: %d ", lastKeyCode);

    console->setColor(scheme.Paragraph);
    for (int y = 2; y < size.Height; y++) {
        console->FillLine(y, coords.X, size.Width, ' ');
    }
}

bool Screen::HasActiveMask()
{
    return false;
}

void Screen::OnEvent(Event& event)
{
    switch (event.Type) {
        case (EventType::Keyboard):
            SetLastCharPressed(event.KeyCode);

            switch (event.KeyCode) {
                case (KEY_ESC):
                    Application::GetEventQueue()->Exit();
                    break;

                case (KEY_F9):
                    Application::GetMenuConfig()->ActivateMenu();
                    break;
            }

            break;

        case (EventType::WindowResize):
            this_thread::sleep_for(chrono::milliseconds(5));
            OnResize();
            break;
    }
}
