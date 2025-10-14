#include "widget/Stack.h"
#include "widget/StackItem.h"
#include "widget/StackDirections.h"
#include "widget/Screen.h"
#include "widget/Dialog.h"
#include <stdexcept>

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
