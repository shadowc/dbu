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

    console->DrawBox(coords.X, coords.Y, size.Width - 1, size.Height - 1);
    console->setPos(coords.X + 1, coords.Y + 1);
    cout << "xxx";
}
