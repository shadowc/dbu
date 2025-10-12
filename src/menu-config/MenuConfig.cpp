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
    selectedItems = vector<int>();
    selectedItems.push_back(-1);

    MenuEntry connectionsEntry = MenuEntry("Connections");

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
        Menu* horizontalMenu = new Menu();
        horizontalMenu->SetHorizontal();
        horizontalMenu->SetSelectedItem(selectedItems.at(0));
        
        for (MenuEntry entry: entries) {
            MenuItem* item = new MenuItem();

            item->SetLabel(" " + entry.label + " ");
            if (entry.action != nullptr) {
                item->SetAction(entry.action);
            }

            horizontalMenu->AddChild(item);
        }

        screen->AddChild(horizontalMenu);
        initialized = true;
    }
}
