#pragma once
#include "../console/ConsoleTools.h"

using namespace Console;

enum class EventType {
    None,
    Keyboard,
    Mouse,
    WindowResize
};

struct Event {
    Event() {
        Type = EventType::None;
        KeyCode = 0;
        SpecialKey = false;
        NewScreenSize = Size();
        Bubbling = true;
    }

    EventType Type;
    bool Bubbling;

    // Keyboard Data
    int KeyCode;
    bool SpecialKey;

    // Window Resize Data
    Size NewScreenSize;
};
