#pragma once
#include "EventQueue.h"
#include <deque>
#include <conio.h>

EventQueue* EventQueue::instance = nullptr;

EventQueue::EventQueue()
{
    queue = deque<Event>();
}

EventQueue* EventQueue::GetInstance()
{
    if (instance == nullptr) {
        instance = new EventQueue();
    }

    return instance;
}

void EventQueue::Shutdown()
{
    queue.clear();
}

bool EventQueue::UnprocessedEvents()
{
    return !queue.empty();
}

void EventQueue::Loop()
{
    char lastChar = 0;

    while (_kbhit()) {
        lastChar = _getch();
    }

    if (lastChar != 0) {
        Event event = Event();
        event.Type = EventType::Keyboard;
        event.SpecialKey = false;
        event.KeyCode = lastChar;
        PushEvent(event);
    }
}

void EventQueue::PushEvent(Event newEvent)
{
    queue.push_back(newEvent);
}

Event EventQueue::GetNextUnprocessedEvent()
{
    Event poppedEvent = Event();

    if (!queue.empty()) {
        poppedEvent = queue.front();
        queue.pop_front();
    }

    return poppedEvent;
}
