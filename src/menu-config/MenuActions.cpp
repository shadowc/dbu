#include "menu-config/MenuActions.h"
#include "Application.h"
#include "event/EventQueue.h"

void MenuActions::ExitAction()
{
    // Signal the event queue to exit the application
    Application::GetEventQueue()->Exit();
}
