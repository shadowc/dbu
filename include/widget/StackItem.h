#pragma ocne
#include "widget/AbstractWidget.h"

class StackItem : public AbstractWidget
{
public:
    void SetStackSize(int newSize);
    int GetStackSize() const;

private:
    int sizeInStack = 0;
};
