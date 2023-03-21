#pragma once
#include "EventDef.h"
#include <deque>
#include "../console/ConsoleTools.h"

using namespace std;
using namespace Console;

class EventQueue 
{
public:
    static EventQueue* GetInstance();
    bool UnprocessedEvents();
    void Loop();
    Event GetNextUnprocessedEvent();
    void Shutdown();
    Size GetScreenSize();

private:
    EventQueue();

    static EventQueue* instance;
    deque<Event> queue;

    void PushEvent(Event newEvent);
    Size lastScreenSize;
};
