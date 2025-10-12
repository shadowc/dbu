#include "menu-config/actions/ExitAction.h"
#include "event/EventQueue.h"
#include "Application.h"

void ExitAction::Execute()
{
    // Signal the event queue to exit the application
    Application::GetEventQueue()->Exit();
}
