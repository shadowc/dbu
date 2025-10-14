#include "menu-config/MenuActions.h"
#include "Application.h"
#include "menu-config/MenuConfig.h"
#include "widget/Screen.h"
#include "event/EventQueue.h"

void MenuActions::ExitAction()
{
    // Signal the event queue to exit the application
    Application::GetEventQueue()->Exit();
}

void MenuActions::RenderConnectionsSubMenu()
{
    Application::GetMenuConfig()->ActivateSubMenu();
}

// Connections SubMenu Actions
void MenuActions::ConnectToServerAction()
{
    Application::GetMenuConfig()->DeactivateMenu();
}

void MenuActions::DisconnectAction()
{
    Application::GetMenuConfig()->DeactivateMenu();
}

void MenuActions::ManageConnectionsAction()
{
    Application::GetMenuConfig()->DeactivateMenu();
}
