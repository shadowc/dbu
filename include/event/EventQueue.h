#pragma once
#include "EventDef.h"
#include <deque>
#include "console/ConsoleTools.h"

using namespace std;
using namespace Console;

class AbstractWidget;

class EventQueue 
{
public:
    static EventQueue* GetInstance();
    bool UnprocessedEvents();
    void Loop(AbstractWidget* root);
    Event GetNextUnprocessedEvent();
    void Shutdown();
    Size GetScreenSize();
    void ProcessNextEvent(AbstractWidget* root);

    void SetCurrentFocusedWidget(AbstractWidget* widget);

    void Exit();
    bool IsExiting();

private:
    EventQueue();

    static EventQueue* instance;
    deque<Event> queue;

    void PushEvent(Event newEvent);
    Size lastScreenSize;

    bool firstPoll = true;

    AbstractWidget* currentFocusedWidget = nullptr;

    bool exiting = false;
};
