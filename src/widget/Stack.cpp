#include "widget/Stack.h"
#include "widget/StackItem.h"
#include "widget/StackDirections.h"
#include "widget/Screen.h"
#include "widget/Dialog.h"
#include <stdexcept>
#include <cmath>

Stack::Stack()
{
    padding = Paddings();
}

void Stack::AddChild(AbstractWidget* child)
{
    StackItem* stackChild = dynamic_cast<StackItem*>(child);

    if (stackChild == nullptr) {
        throw std::runtime_error("Stacks only accept Widgets of type StackItem as children.");
    }

    AbstractWidget::AddChild(child);
}

void Stack::Invalidate()
{
    if (parent == nullptr) {
        AbstractWidget::Invalidate();
        return;
    }

    // adjust to parent width and height and then set the width and height of
    // children based on the property StackChild::size
    Size parentSize = parent->GetSize();
    Coords parentCoords = parent->GetPosition();

    coords.X = parentCoords.X + padding.Left;
    coords.Y = parentCoords.Y + padding.Top;
    size.Width = parentSize.Width - padding.Left - padding.Right;
    size.Height = parentSize.Height - padding.Top - padding.Bottom;

    int remainingSize = direction == StackDirections::HORIZONTAL ? size.Width : size.Height;
    int remainingSizeDivisibleBy = 0;

    for (AbstractWidget* child : children) {
        StackItem* stackItemChild = dynamic_cast<StackItem*>(child);

        if (stackItemChild == nullptr) {
            throw new runtime_error("Found a child of Stack Widget that is not a StackItem widget");
        }

        int childSize = stackItemChild->GetStackSize();

        remainingSize -= childSize;
        if (childSize == 0) {
            remainingSizeDivisibleBy++;
        }
    }

    int curPosition = 0;
    for (AbstractWidget* child : children) {
        StackItem* stackItemChild = dynamic_cast<StackItem*>(child);
        int childSize = stackItemChild->GetStackSize();

        if (childSize == 0) {
            childSize = floor(remainingSize / remainingSizeDivisibleBy);
        }

        int calculatedWidth = direction == StackDirections::HORIZONTAL ? childSize : size.Width;
        int calculatedHeight = direction == StackDirections::HORIZONTAL ? size.Height : childSize;

        int calculatedX = direction == StackDirections::HORIZONTAL ? 0 : curPosition;
        int calculatedY = direction == StackDirections::HORIZONTAL ? curPosition : 0;

        child->SetPosition(calculatedX, calculatedY);
        child->SetSize(calculatedWidth, calculatedHeight);  
        
        curPosition += direction == StackDirections::HORIZONTAL ? calculatedY : calculatedX;
    }

    AbstractWidget::Invalidate();
}

void Stack::SetParent(AbstractWidget *parent)
{
    // Try to determine paddings based on parent
    Screen* parentIsScreen = dynamic_cast<Screen*>(parent);

    if (parentIsScreen != nullptr) {
        padding = Paddings(2, 0, 1);
    } else {
        Dialog* parentIsDialog = dynamic_cast<Dialog*>(parent);

        if (parentIsDialog != nullptr) {
            padding = Paddings(1);
        }
    }

    AbstractWidget::SetParent(parent);
}

bool Stack::HasActiveMask()
{
    return false;
}
