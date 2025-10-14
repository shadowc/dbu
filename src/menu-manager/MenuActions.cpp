#include "menu-manager/MenuActions.h"
#include "Application.h"
#include "menu-manager/MenuManager.h"
#include "dialog-manager/DialogManager.h"
#include "dialog-manager/DialogDef.h"
#include "widget/Dialog.h"
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
    Application::GetDialogManager()->ShowDialog(Dialogs::CONNECTION);
}

void MenuActions::DisconnectAction()
{
    Application::GetMenuManager()->DeactivateMenu();
    Application::GetDialogManager()->CloseDialogs();
}

void MenuActions::ManageConnectionsAction()
{
    Application::GetMenuManager()->DeactivateMenu();
    Application::GetDialogManager()->CloseDialogs();
}
