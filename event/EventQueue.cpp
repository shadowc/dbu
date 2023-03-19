#pragma once
#include "EventQueue.h"
#include <deque>
#include <conio.h>
#include "../console/Console.h"
#include "../console/ConsoleTools.h"

using namespace std;
using namespace Console;

EventQueue* EventQueue::instance = nullptr;

EventQueue::EventQueue()
{
    queue = deque<Event>();
    lastScreenSize = ConsoleTty::getTty()->getConsoleSize();
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
    // Poll Keyboard Events
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

    // Poll Screen resize
    Size screenSize = ConsoleTty::getTty()->getConsoleSize();

    if (screenSize.Width != lastScreenSize.Width || screenSize.Height != lastScreenSize.Height) {
        lastScreenSize.Width = screenSize.Width;
        lastScreenSize.Height = screenSize.Height;

        Event event = Event();
        event.Type = EventType::WindowResize;
        event.NewScreenSize = Size(lastScreenSize.Width, lastScreenSize.Height);
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
