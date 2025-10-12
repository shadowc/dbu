#include "menu-config/actions/ExitAction.h"
#include "Application.h"
#include "event/EventQueue.h"

void ExitAction::Execute()
{
    // Signal the event queue to exit the application
    Application::GetEventQueue()->Exit();
}
