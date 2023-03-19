#pragma once
#include "EventDef.h"
#include <deque>

using namespace std;

class EventQueue {
public:
    static EventQueue* GetInstance();
    bool UnprocessedEvents();
    void Loop();
    Event GetNextUnprocessedEvent();
    void Shutdown();

private:
    EventQueue();

    static EventQueue* instance;
    deque<Event> queue;

    void PushEvent(Event newEvent);
};
