#include "menu-manager/MenuActions.h"
#include "Application.h"
#include "menu-manager/MenuManager.h"
#include "widget/Screen.h"
#include "event/EventQueue.h"

void MenuActions::ExitAction()
{
    // Signal the event queue to exit the application
    Application::GetEventQueue()->Exit();
}

void MenuActions::RenderConnectionsSubMenu()
{
    Application::GetMenuManager()->ActivateSubMenu();
}

// Connections SubMenu Actions
void MenuActions::ConnectToServerAction()
{
    Application::GetMenuManager()->DeactivateMenu();
}

void MenuActions::DisconnectAction()
{
    Application::GetMenuManager()->DeactivateMenu();
}

void MenuActions::ManageConnectionsAction()
{
    Application::GetMenuManager()->DeactivateMenu();
}
