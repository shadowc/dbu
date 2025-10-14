#include "widget/StackItem.h"
#include "console/Console.h"
#include "Application.h"
#include <iostream>

int StackItem::GetStackSize() const
{
    return sizeInStack;
}

void StackItem::SetStackSize(int newSize)
{
    sizeInStack = newSize;
    if (parent != nullptr) {
        parent->Invalidate();
    }
}

void StackItem::RenderWidget()
{
    ConsoleTty *console = Application::GetConsole();

    console->setPos(coords.X, coords.Y);
    cout << "xxx";
}
