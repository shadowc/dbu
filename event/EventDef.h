#pragma once

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
    }

    EventType Type;

    // Keyboard Data
    char KeyCode;
    bool SpecialKey;
};
