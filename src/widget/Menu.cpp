#include "widget/Menu.h"
#include "Application.h"
#include "widget/MenuItem.h"
#include "console/Console.h"
#include "event/KeyCodes.h"
#include <cmath>

using namespace Console;

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

void Menu::SetSelectedItem(int index)
{
    for (AbstractWidget* child : children) {
        MenuItem* childMenuItem = dynamic_cast<MenuItem*>(child);

        if (childMenuItem != nullptr && childMenuItem->IsSelected()) {
            childMenuItem->SetSelected(false);
        }
    }

    if (index < 0 || index >= GetChildLength()) {
        return;
    }

    MenuItem* menuItem = dynamic_cast<MenuItem*>(GetChildAt(index));

    if (menuItem != nullptr) {
        menuItem->SetSelected(true);
    }
}

int Menu::GetSelectedItem()
{
    for (int i = 0; i < GetChildLength(); i++) {
        MenuItem* menuItem = dynamic_cast<MenuItem*>(GetChildAt(i));

        if (menuItem != nullptr && menuItem->IsSelected()) {
            return i;
        }
    }

    // No item selected
    return -1;
}

void Menu::OnEvent(Event& event)
{
    if (event.Type != EventType::Keyboard) {
        return;
    }

    event.Bubbling = false;

    if (IsHorizontal()) {
        HandleKeyPressedHorizontal(event);
    } else {
        HandleKeyPressedVertical(event);
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
    ConsoleTty* console = Application::GetConsole();
    ColorScheme scheme = console->getColorScheme();

    console->setColor(scheme.Menu);

    for (int y = coords.Y; y < coords.Y + size.Height; y++) {
        console->FillLine(y, coords.X, coords.X + size.Width, ' ');
    }
}

void Menu::HandleKeyPressedHorizontal(Event& event)
{
    switch (event.KeyCode) {
        case (KEY_LEFT):
            {
                int selectedIndex = GetSelectedItem();
                int newIndex = selectedIndex - 1;

                if (newIndex < 0) {
                    newIndex = GetChildLength() - 1;
                }

                SetSelectedItem(newIndex);
            }
            break;

        case (KEY_RIGHT):
            {
                int selectedIndex = GetSelectedItem();
                int newIndex = selectedIndex + 1;

                if (newIndex >= GetChildLength()) {
                    newIndex = 0;
                }

                SetSelectedItem(newIndex);
            }
            break;

        case (KEY_ENTER):
        case (KEY_DOWN):
            {
                int selectedIndex = GetSelectedItem();

                if (selectedIndex >= 0 && selectedIndex < GetChildLength()) {
                    MenuItem* menuItem = dynamic_cast<MenuItem*>(GetChildAt(selectedIndex));

                    if (menuItem != nullptr) {
                        menuItem->Focus();
                        menuItem->Execute();
                    }
                }
            }
            break;

        case (KEY_ESC):
        case (KEY_UP):
            SetSelectedItem(-1);
            Blur();

            if (onExitMenu != nullptr) {
                onExitMenu();
            }
            break;
    }
}

void Menu::HandleKeyPressedVertical(Event& event)
{
    switch (event.KeyCode) {
        case (KEY_UP):
            {
                int selectedIndex = GetSelectedItem();
                int newIndex = selectedIndex - 1;

                if (newIndex < 0) {
                    newIndex = GetChildLength() - 1;
                }

                SetSelectedItem(newIndex);
            }
            break;

        case (KEY_DOWN):
            {
                int selectedIndex = GetSelectedItem();
                int newIndex = selectedIndex + 1;

                if (newIndex >= GetChildLength()) {
                    newIndex = 0;
                }

                SetSelectedItem(newIndex);
            }
            break;

        case (KEY_ENTER):
            {
                int selectedIndex = GetSelectedItem();

                if (selectedIndex >= 0 && selectedIndex < GetChildLength()) {
                    MenuItem* menuItem = dynamic_cast<MenuItem*>(GetChildAt(selectedIndex));

                    if (menuItem != nullptr) {
                        menuItem->Focus();
                        menuItem->Execute();
                    }
                }
            }
            break;

        case (KEY_ESC):
            SetSelectedItem(-1);
            Blur();

            if (onExitMenu != nullptr) {
                onExitMenu();
            }
            break;
    }
}
