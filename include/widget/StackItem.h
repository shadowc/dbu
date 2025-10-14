#pragma ocne
#include "widget/AbstractWidget.h"

class StackItem : public AbstractWidget
{
public:
    void SetStackSize(int newSize);
    int GetStackSize() const;
    void RenderWidget() override;

private:
    int sizeInStack = 0;
};
