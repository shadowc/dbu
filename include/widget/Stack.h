#pragma once
#include "widget/AbstractWidget.h"
#include "widget/StackDirections.h"
#include "console/ConsoleDef.h"

class Stack : public AbstractWidget
{
public:
    Stack();

    void AddChild(AbstractWidget* child) override;
    void Invalidate() override;
    void SetParent(AbstractWidget* parent) override;
    bool HasActiveMask() override;

protected:
    StackDirections direction = StackDirections::HORIZONTAL;
    Paddings padding;
};
