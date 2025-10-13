#include "menu-config/MenuConfig.h"
#include "menu-config/MenuActions.h"
#include "Application.h"
#include "widget/Screen.h"
#include "widget/Menu.h"
#include "widget/MenuItem.h"
#include "console/ConsoleTools.h"

MenuConfig::MenuConfig()
{
    // Initialize with empty menu
    entries = vector<MenuEntry>();
    activeMenus = vector<Menu*>();

    MenuEntry connectionsEntry = MenuEntry("Connections", MenuActions::RenderConnectionsSubMenu);

    connectionsEntry.AddEntry(MenuEntry("Connect to Server..."));
    connectionsEntry.AddEntry(MenuEntry("Disconnect"));
    connectionsEntry.AddEntry(MenuEntry("Manage Connections..."));

    entries.push_back(connectionsEntry);

    entries.push_back(MenuEntry("Exit", MenuActions::ExitAction));
}

void MenuConfig::RenderMenu()
{
    Screen* screen = Application::GetScreen();

    // render horizontal menu
    if (initialized == false) {
        Menu *horizontalMenu = new Menu();
        horizontalMenu->SetHorizontal();
        
        for (MenuEntry entry: entries) {
            MenuItem* item = new MenuItem();

            item->SetLabel(" " + entry.label + " ");
            if (entry.action != nullptr) {
                item->SetAction(entry.action);
            }

            horizontalMenu->AddChild(item);
        }

        screen->AddChild(horizontalMenu);
        activeMenus.push_back(horizontalMenu);

        initialized = true;
    }
}

void MenuConfig::ActivateMenu()
{
    Menu* mainMenu = activeMenus.at(0);

    if (mainMenu != nullptr) {
        mainMenu->SetSelectedItem(0);
        mainMenu->Focus();
    }
}

void MenuConfig::ActivateSubMenu()
{
    Screen* screen = Application::GetScreen();
    Menu* parentMenu = activeMenus.back();
    int selectedIndex = parentMenu->GetSelectedItem();

    if (parentMenu != nullptr && selectedIndex >= 0) {
        vector<MenuEntry> subMenuEntries = FindNextSubEntries();

        if (subMenuEntries.size() == 0) {
            return;
        }

        Menu* subMenu = new Menu();
        subMenu->SetVertical();
        subMenu->SetTopPadding(0);
        subMenu->SetHasBorder(true);

        // TODO: Calculate position based on parent menu item position
        Coords position = GetPositionForSubMenu(parentMenu, selectedIndex);
        subMenu->SetPosition(position.X, position.Y);

        for (MenuEntry entry: subMenuEntries) {
            MenuItem* item = new MenuItem();

            item->SetLabel(" " + entry.label + " ");
            if (entry.action != nullptr) {
                item->SetAction(entry.action);
            }

            subMenu->AddChild(item);
        }

        subMenu->onExitMenu = [this]() { this->DeactivateSubMenu(); };
        subMenu->onMenuCycleRight = [this]() { this->CycleMenuRight(); };
        subMenu->onMenuCycleLeft = [this]() { this->CycleMenuLeft(); };
        screen->AddChild(subMenu);
        activeMenus.push_back(subMenu);
        subMenu->SetSelectedItem(0);
        subMenu->Focus();
    }
}

void MenuConfig::DeactivateSubMenu()
{
    Menu* lastSubMenu = activeMenus.back();

    if (lastSubMenu != nullptr) {
            lastSubMenu->Blur();
            Application::GetScreen()->RemoveChild(lastSubMenu);
            delete lastSubMenu;
    }

    activeMenus.pop_back();

    Menu* parentMenu = activeMenus.back();
    if (parentMenu != nullptr) {
        parentMenu->Focus();
    }
}

vector<MenuEntry> MenuConfig::FindNextSubEntries()
{
    vector<MenuEntry> subEntries = entries;
    
    for (int i = 0; i < activeMenus.size(); i++) {
        Menu* menu = activeMenus.at(i);
        int selectedIndex = menu->GetSelectedItem();

        if (selectedIndex >= 0 && selectedIndex < subEntries.size()) {
            subEntries = subEntries.at(selectedIndex).subEntries;
        } else {
            return vector<MenuEntry>();
        }
    }

    return subEntries;
}

void MenuConfig::CycleMenuRight()
{
    DeactivateSubMenu();
    Menu* mainMenu = activeMenus.at(0);

    if (mainMenu != nullptr) {
        int selectedIndex = mainMenu->GetSelectedItem();
        int newIndex = selectedIndex + 1;

        if (newIndex >= mainMenu->GetChildLength()) {
            newIndex = 0;
        }

        mainMenu->SetSelectedItem(newIndex);
        ActivateSubMenu();
    }
}

void MenuConfig::CycleMenuLeft()
{
    DeactivateSubMenu();
    Menu* mainMenu = activeMenus.at(0);

    if (mainMenu != nullptr) {
        int selectedIndex = mainMenu->GetSelectedItem();
        int newIndex = selectedIndex - 1;

        if (newIndex < 0) {
            newIndex = mainMenu->GetChildLength() - 1;
        }

        mainMenu->SetSelectedItem(newIndex);
        ActivateSubMenu();
    }
}

Coords MenuConfig::GetPositionForSubMenu(Menu* parentMenu, int selectedIndex)
{
    // Get parent menu position and size
    Coords parentPos = parentMenu->GetPosition();
    Size parentSize = parentMenu->GetSize();

    // Get selected menu item position
    AbstractWidget* selectedItem = parentMenu->GetChildAt(selectedIndex);
    Coords itemPos = selectedItem->GetPosition();
    Size itemSize = selectedItem->GetSize();

    int x, y;
    if (parentMenu->IsHorizontal()) {
        x = itemPos.X;
        y = parentPos.Y + parentSize.Height;
    } else {
        x = parentPos.X + parentSize.Width;
        y = itemPos.Y;
    }

    return Coords(x, y);
}
