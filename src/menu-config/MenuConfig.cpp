#include "menu-config/MenuConfig.h"
#include "menu-config/MenuActions.h"
#include "Application.h"
#include "widget/Screen.h"
#include "widget/Menu.h"
#include "widget/MenuItem.h"

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

    vector<MenuEntry> curEntries = entries;
    for (int i = 0; i < openSubMenuIndexes.size(); i++) {
        int menuIndex = openSubMenuIndexes.at(i);

        vector<MenuEntry> subMenuEntries = curEntries.at(menuIndex).subEntries;

        if (activeMenus.size() <= i + 1) {
            Menu* subMenu = new Menu();
            subMenu->SetVertical();
            subMenu->SetTopPadding(0);
            subMenu->SetPosition(1, 2);

            for (MenuEntry entry: subMenuEntries) {
                MenuItem* item = new MenuItem();

                item->SetLabel(" " + entry.label + " ");
                if (entry.action != nullptr) {
                    item->SetAction(entry.action);
                }

                subMenu->AddChild(item);
            }

            screen->AddChild(subMenu);
            activeMenus.push_back(subMenu);
        }

        curEntries = subMenuEntries;
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

void MenuConfig::ActivateSubMenu(int index)
{
    openSubMenuIndexes.push_back(index);
    RenderMenu();
}

void MenuConfig::DeactivateSubMenu()
{
    if (!openSubMenuIndexes.empty()) {
        openSubMenuIndexes.pop_back();

        Menu* subMenu = activeMenus.back();

        if (subMenu != nullptr) {
            subMenu->Blur();
            Application::GetScreen()->RemoveChild(subMenu);
            delete subMenu;
        }

        activeMenus.pop_back();

        Menu* parentMenu = activeMenus.back();
        if (parentMenu != nullptr) {
            parentMenu->Focus();
        }
    }

    RenderMenu();
}
