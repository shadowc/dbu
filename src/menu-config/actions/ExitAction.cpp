#include "menu-config/actions/ExitAction.h"
#include "event/EventQueue.h"

void ExitAction::Execute()
{
    // Signal the event queue to exit the application
    EventQueue::GetInstance()->Exit();
}
