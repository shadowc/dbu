#include "widget/StackItem.h"

int StackItem::GetSize() const
{
    return sizeInStack;
}

void StackItem::SetSize(int newSize)
{
    sizeInStack = newSize;
    if (parent != nullptr) {
        parent->Invalidate();
    }
}
