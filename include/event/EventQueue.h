#pragma once
#include "EventDef.h"
#include <deque>
#include "console/ConsoleDef.h"

using namespace std;
using namespace Console;

class AbstractWidget;

class EventQueue 
{
public:
    EventQueue();
    ~EventQueue();

    bool UnprocessedEvents();
    void Loop();
    Event GetNextUnprocessedEvent();
    Size GetScreenSize();
    void ProcessNextEvent();

    void SetCurrentFocusedWidget(AbstractWidget* widget);

    void Exit();
    bool IsExiting();

private:
    deque<Event> queue;

    void PushEvent(Event newEvent);
    Size lastScreenSize;

    bool firstPoll = true;

    AbstractWidget* currentFocusedWidget = nullptr;

    bool exiting = false;
};
