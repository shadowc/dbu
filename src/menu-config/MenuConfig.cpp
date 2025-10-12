#include "menu-config/MenuConfig.h"
#include "menu-config/actions/ExitAction.h"

MenuConfig::MenuConfig()
{
    // Initialize with empty menu
    entries = vector<MenuEntry>();

    MenuEntry connectionsEntry = MenuEntry("Connections");

    connectionsEntry.AddEntry(MenuEntry("Connect to Server..."));
    connectionsEntry.AddEntry(MenuEntry("Disconnect"));
    connectionsEntry.AddEntry(MenuEntry("Manage Connections..."));

    entries.push_back(connectionsEntry);
    ExitAction* exitAction = new ExitAction();

    entries.push_back(MenuEntry("Exit", exitAction));
}
