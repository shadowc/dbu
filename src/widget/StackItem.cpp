#include "widget/StackItem.h"

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
