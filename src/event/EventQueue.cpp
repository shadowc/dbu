#include "console/Console.h"
#include "console/ConsoleTools.h"
#include "event/EventQueue.h"
#include "event/KeyboardTools.h"
#include "widget/AbstractWidget.h"
#include <deque>

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

void EventQueue::Loop(AbstractWidget* root)
{
    // TODO: Poll mouse events

    // Poll Keyboard Events
    int lastChar = _getKeyboardInput();

#ifdef __LINUX
    if (firstPoll) {
        root->Invalidate();
        root->Draw();
        firstPoll = false;
    }
#endif

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

Size EventQueue::GetScreenSize()
{
    return lastScreenSize;
}

void EventQueue::ProcessNextEvent(AbstractWidget* root)
{
    Event event = GetNextUnprocessedEvent();

    // focus on the root widget if no widget has focus
    if (currentFocusedWidget == nullptr) {
        root->Focus();
    }

    if (currentFocusedWidget != nullptr) {
        currentFocusedWidget->OnEvent(event);

        if (currentFocusedWidget == nullptr) {
            root->Focus(); // refocus on root if the focused widget was blurred during event processing
        }

        if (event.Bubbling && currentFocusedWidget != nullptr) {
            AbstractWidget* parent = currentFocusedWidget->GetParent();

            while (parent != nullptr && event.Bubbling) {
                parent->OnEvent(event);
                parent = parent->GetParent();
            }
        }
    }
}

void EventQueue::SetCurrentFocusedWidget(AbstractWidget *widget)
{
    // If we are setting focus to null, this means we are comming from AbstractWidget::Blur
    // So don't generate an endless recursive call to Blur
    if (widget == nullptr) {
        currentFocusedWidget = nullptr;
        return;
    }

    if (currentFocusedWidget != nullptr) {
        if (currentFocusedWidget->GetUniqueId() == widget->GetUniqueId()) {
            return;
        }

        currentFocusedWidget->Blur();
    }

    currentFocusedWidget = widget;
}

void EventQueue::Exit()
{
    exiting = true;
}

bool EventQueue::IsExiting()
{
    return exiting;
}
